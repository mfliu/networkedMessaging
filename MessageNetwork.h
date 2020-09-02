#pragma once 

#include <unordered_map>
#ifndef _MESSAGENETWORK_H_
#define _MESSAGENETWORK_H_

#include <msgpack.hpp>
#include <ctime>
#include <chrono>
#include <atomic>
#include <iostream>
#include <uv.h>
#include "msgpackDefinitions.h"

using namespace std::chrono;
using namespace std;
using namespace msgpack;

struct Subscriber {
  sockaddr_in address;
  uv_udp_t socket;
};

class MessageNetwork
{
  private:
    atomic_int msgNum{0};
    high_resolution_clock::time_point startTime;
    bool running;

  public:
    MessageNetwork(string ipAddr, unsigned int port);
    unordered_map<int, vector<Subscriber*>> subscriberMap;
    unordered_map<string, std::unique_ptr<Subscriber>> moduleSocketMap;
    uv_udp_t recv_socket;
    sockaddr_in recv_addr;
    //sbuffer messageBufs;

    // libuv functions 
    uv_loop_t *loop;

    // Message sending and receiving functions
    void startListening();
    
    // Message annotating functions
    int getMsgNum();
    double getTimestamp();
    //int addModule(int moduleID, string ipAddr, int port);
    //int subscribe(int moduleID, int subscribeID);
};

// libuv functionality
static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf); 
void on_send(uv_udp_send_t *req, int status);
void send_to_all(const vector<Subscriber*> & subs, const uv_buf_t *buf, sbuffer* sbuf);
void on_read(uv_udp_t *rea, ssize_t nread, const uv_buf_t *buf, 
    const sockaddr *addr, unsigned int flags);


#endif
