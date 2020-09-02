#include "MessageNetwork.h"
#include "msgpackDefinitions.h"
#include <string>
#include <cstring>
#include <uv.h>

// libuv functionality
static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
  static char slab[65536]; // Because libuv said so (this is what they always request)
  assert(suggested_size <= sizeof(slab));
  buf->base = slab;
  // buf->base = (char*) malloc(suggested_size); 
  buf->len = suggested_size;
}

void on_send(uv_udp_send_t *req, int status)
{
  if (status < 0) {
    cout << "Send failed: " << uv_strerror(status) << " " << uv_err_name(status) << endl;
    sockaddr_in addr; 
    int addr_len = sizeof(addr);
    uv_udp_getpeername(req->handle, reinterpret_cast<sockaddr*>(&addr), &addr_len);
    char addr_str[50];
    uv_ip4_name(&addr, addr_str, 50);
    cout << "Addr: " << addr_str << endl;
    exit(-2);
  }

  sbuffer* sbuf = reinterpret_cast<sbuffer*>(req->data);
  delete sbuf;
  delete req;
}

void send_to_all(vector<Subscriber*> &subs, const uv_buf_t *buf, sbuffer* sbuf) 
{
  for (const auto& subscriber : subs) {
    uv_udp_send_t* send_req = new uv_udp_send_t;
    send_req->data = reinterpret_cast<void*>(sbuf);
    uv_udp_send(send_req, &subscriber->socket, buf, 1, nullptr, on_send);
  }
}

void on_read(uv_udp_t *req, ssize_t nread, const uv_buf_t *buf, 
    const sockaddr *addr, unsigned int flags)
{
  if (nread == 0) {
    return;
  }

  if (nread < 0) {
    cout << "Oh nooooo" << endl;
    return;
  }

  MessageNetwork *network = static_cast<MessageNetwork *>(req->data);
  object_handle oh = unpack(buf->base, nread);
  auto obj_map = oh->as<std::unordered_map<std::string, object>>();
  auto header = obj_map.at("header").as<MSG_HEADER>();
  header.msg_num = network->getMsgNum();
  header.timestamp = network->getTimestamp();

  zone z;
  obj_map["header"] = object(header, z);

  switch(static_cast<MessageTypeID>(header.msg_type)) {
    case MessageTypeID::MODULE_ADD:
      {
        auto msg = oh->as<M_MODULE_ADD>();
        string& moduleName = msg.moduleName;
        string& ipAddr = msg.ipAddr;
        int port = msg.port;
        cout << "MODULE_ADD received with " << moduleName << ipAddr << port << endl;
        const auto& [sub_it, _] = network->moduleSocketMap.emplace(moduleName, std::make_unique<Subscriber>());
        Subscriber* sub = sub_it->second.get();
        uv_ip4_addr(msg.ipAddr.c_str(), msg.port, &sub->address);
        uv_udp_init(network->loop, &sub->socket);
        uv_udp_connect(&sub->socket, reinterpret_cast<sockaddr *>(&sub->address));
        break;
      }
    case MessageTypeID::MODULE_SUBSCRIBE:
      {
        auto sub_msg = oh->as<M_MODULE_SUBSCRIBE>();
        string moduleName = sub_msg.moduleName;
        int subscribeIdx = sub_msg.msgType;
        cout << "MODULE_SUBSCRIBE received with " << moduleName << subscribeIdx << endl;
        network->subscriberMap[subscribeIdx].push_back(network->moduleSocketMap[moduleName].get());
        break;
      }
    default:
      {
        sbuffer* sbuf = new sbuffer;
        pack(*sbuf, obj_map);
        uv_buf_t updated_msg = uv_buf_init(sbuf->data(), sbuf->size()); //sbuf.size());
        //char* buf_data_copy = new char[nread
        cout << "Message received with message type " << header.msg_type << " and size " << updated_msg.len << ", originally " << nread << endl;
        // NOTE: This doesn't check that the sending module is known
        send_to_all(network->subscriberMap[header.msg_type], &updated_msg, sbuf);
        break;
      }
  }
}

MessageNetwork::MessageNetwork(string ipAddr, unsigned int port)
{
  startTime = high_resolution_clock::now();
  loop = uv_default_loop();
  uv_udp_init(loop, &recv_socket);
  uv_ip4_addr(ipAddr.c_str(), port, &recv_addr);
  recv_socket.data = this;
  uv_udp_bind(&recv_socket, reinterpret_cast<const sockaddr *>(&recv_addr), 0);
  //pack(messageBufs, MessageTypeID); 
}

int MessageNetwork::getMsgNum()
{
  return msgNum++;
}

double MessageNetwork::getTimestamp()
{
  high_resolution_clock::time_point currTime = high_resolution_clock::now();
  duration<double, milli> timeNow = duration_cast<duration<double, milli>> (currTime-startTime);
  return timeNow.count();
}

void MessageNetwork::startListening()
{
  uv_udp_recv_start(&recv_socket, alloc_buffer, on_read); 
  uv_run(loop, UV_RUN_DEFAULT);
}

int main(int argc, char **argv) {
  string ipAddress(argv[1]);
  unsigned int port = stoi(argv[2]);
  MessageNetwork network(ipAddress, port);
  network.startListening();
}
