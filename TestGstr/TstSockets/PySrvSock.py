import socket
import time

timer = 0
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((socket.gethostname(),8894))
s.listen(5)
msg =  "Welcome to the server"
Rx = '0'
print("Server addr: ",socket.gethostname(),8894)

clientsocket, address = s.accept()
while timer <100:
    print(f"Connection from {address} has been established!")
    clientsocket.send(bytes(msg, "utf-8"))
    Rx = clientsocket.recv(100)
    print(Rx.decode("utf-8"))
    time.sleep(0.2)
    timer += timer
clientsocket.close()