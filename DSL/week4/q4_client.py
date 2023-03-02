import socket
serverIP = "127.0.0.1"
serverPort = 16003

clientSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSock.connect((serverIP, serverPort))

message = input("Input integers with space in between: ")
message2 = input("Enter the length of the set: ")

clientSock.send(bytearray(message, "utf-8"))
clientSock.send(bytearray(message2, "utf-8"))

data = clientSock.recv(1024).decode()
temp = [float(x) for x in data.split(' ')]

print("The total of all numbers is: " + str(temp[0]))
print("The lowest number is: " + str(temp[1]))
print("The highest number is: " + str(temp[2]))
print("The mean is: " + str(temp[3]))

clientSock.close()