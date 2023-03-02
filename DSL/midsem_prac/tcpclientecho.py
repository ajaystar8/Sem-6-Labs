import socket

sock = socket.socket()

server_ip = socket.gethostname()
server_port = 2023
sock.connect((server_ip, server_port))

while True:
    msg = input("Enter message to be echoed by server: ")
    sock.sendall(msg.encode())
    rcvd_msg = sock.recv(1024).decode()
    print(f"Echoed message: {rcvd_msg}")
