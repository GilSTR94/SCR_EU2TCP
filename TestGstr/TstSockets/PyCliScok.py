
import socket
import time
import serial

serialcomm = serial.Serial('COM3',9600)
serialcomm.timeout = 1 
btn = '0'
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((socket.gethostname(), 8894))
print("Server addr: ",socket.gethostname(),8894)
while True:
    msg = s.recv(100)
    print(msg.decode("utf-8"))
    print("Presiona el boton")
    while True:
        btn = serialcomm.readline()
        if btn:
            break
    print(btn.decode("ascii"))
    if btn[0] == '1':
        print("Led Prendido")
    elif btn[0] == '0':
        print("Led Apagado")
    s.send(btn)