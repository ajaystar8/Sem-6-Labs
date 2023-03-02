import socket

server_ip = socket.gethostname()
server_port = 3002

s = socket.socket()
s.connect((server_ip, server_port))

while True:
    msg = input("Enter a message to send : ")
    s.sendall(msg.encode())
    data = s.recv(1024)
    print("The sender sent : ", data.decode())
