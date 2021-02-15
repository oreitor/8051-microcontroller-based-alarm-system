import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('25.39.69.249', 9600)
sock.bind(server_address)
sock.listen(1)
print('starting up on %s port %s' % server_address)

count = 0

while True:
    print('waiting for a connection')
    connection, client_address = sock.accept()
    try:
        print('connection from', client_address)
        while True:
            data = connection.recv(1024)
            print('received "%s"' % data)
            count += 1
            if count % 3 == 0:
                print('sending data back to the client')
                connection.sendall("155 Polis! İhbarınız Ulaştı.".encode('utf-8', errors="ignore"))
            else:
                pass
    finally:
        connection.close()
