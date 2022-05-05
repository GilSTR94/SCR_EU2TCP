
import socket
import time
import serial

serialcomm = serial.Serial('COM4',9600)
serialcomm.timeout = 1 
btn = '0'
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((socket.gethostname(), 8894))
print("Server addr: ",socket.gethostname(),8894)
while True:
    msg = s.recv(100)
    print(msg.decode("utf-8"))
    if msg[0] == '1':
        serialcomm.write(msg[0])
    elif msg[0] == '0':
        serialcomm.write(msg[0])
    #s.send(msg)
