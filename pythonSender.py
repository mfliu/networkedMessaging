import msgpack
import random
import socket
import time

listenerSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
listenerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listenerSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
listenerSocket.bind(("127.0.0.1", 7000))
addModulePacket = {"header":{"msg_type":1}, "moduleName":"pythonSender", "ipAddr":"127.0.0.1", "port":7000}
addMsg = msgpack.packb(addModulePacket, use_bin_type=True)
listenerSocket.sendto(addMsg, ("127.0.0.1", 8080))
running = True
period = 1/30000
t = time.time()
#startTime = time.time()
sent = 0
while running and sent > -10000: #time.time() - startTime < 5:
    if time.time() - t >= period:
        header = {"msg_type":3, "timestamp":float(1), "msg_num":1, "reserved":1}
        data = [random.randint(-100, 100) for x in range(0, 64)]
        testData = {"header":header, "data":data}
        test = msgpack.packb(testData, use_bin_type=False)
        listenerSocket.sendto(test, ("127.0.0.1", 8080))
        sent += 1
        t = time.time()
        #thing = input("press any key to continue")
