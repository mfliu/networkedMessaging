import msgpack
import socket 
import numpy as np 
import time 

listenerSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
listenerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listenerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
listenerSocket.settimeout(10)
listenerSocket.bind(("127.0.0.1", 9000))
addModulePacket = {"header":{"msg_type":1}, "moduleName":"pythonListener", "ipAddr":"127.0.0.1", "port":9000}
addMsg = msgpack.packb(addModulePacket, use_bin_type=True)
listenerSocket.sendto(addMsg, ("127.0.0.1", 8080))

subscribeMsg = {"header":{"msg_type":2}, "msgType":3, "moduleName":"pythonListener"} 
subscribeData = msgpack.packb(subscribeMsg, use_bin_type=True)
listenerSocket.sendto(subscribeData, ("127.0.0.1", 8080))

running = True
buffer = []
numPackets = 0
unpacker = msgpack.Unpacker()
#period = 1/10000
#t = time.time()
while running:
    try:
        data, addr = listenerSocket.recvfrom(8192)
        if not data:
            break
        unpacker.feed(data)
        more_objects = True
        while more_objects:
            try:
                map_bound = unpacker.read_map_header()
                #print(map_bound)
                o = {}
                for _ in range(0, 2*map_bound, 2):
                    k = unpacker.unpack()
                    v = unpacker.unpack()
                    o[k] = v
                numPackets = numPackets + 1
                print('o', o)
                print("Packets received: ", numPackets)
            except msgpack.OutOfData:
                more_objects = False
            # except msgpack.exceptions.UnpackValueError:
            #     print('Unexpected type header')
    except socket.timeout:
        print('Timeout')
        break
"""
print('Starting to unpack')
more_objects = True
while more_objects:
    try:
        map_bound = unpacker.read_map_header()
        #print(map_bound)
        o = {}
        for _ in range(0, 2*map_bound, 2):
            k = unpacker.unpack()
            v = unpacker.unpack()
            o[k] = v
        numPackets = numPackets + 1
        print('o', o)
        print("Packets received: ", numPackets)
    except msgpack.OutOfData:
        more_objects = False
    #except Exception as e:
    #    print(e)
    #    #more_objects = False
"""
