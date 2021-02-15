import serial
import socket
import time

ser = serial.Serial("COM1", 20833)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('25.39.69.249', 9600)
sock.connect(server_address)
sock.settimeout(1)

while True:

    read = ser.read()
    value = read.decode("UTF-8")

    try:

        # Send Data
        sock.sendall(value.encode('utf-8', errors="ignore"))
        print('İletiliyor.. "%s"' % value)

        # Response Data
        data = sock.recv(1024)
        data = data.decode("utf-8")
        print('Alınıyor.. "%s"' % data)
        
        print()

    except socket.timeout:
        pass

    time.sleep(1)