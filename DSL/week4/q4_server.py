import socket

serverIP = '127.0.0.1'
serverPort = 16003

serverSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSock.bind((serverIP, serverPort))
serverSock.listen(1)

print("TCP server has started and is ready to receive")
connection, addr = serverSock.accept()

while 1:
    data = connection.recv(1024).decode()
    if not data: 
        break

    temp = [float(x) for x in data.split(' ')]
    print("Received data:", temp)

    length = len(temp)
    maximum = max(temp)
    minimum = min(temp)
    total = sum(temp)
    mean = total/length

    msg = str(total) + " " + str(minimum) + " " + str(maximum) + " " + str(mean)
    connection.send(bytearray(msg, "utf-8"))
