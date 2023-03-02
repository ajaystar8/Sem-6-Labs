import socket

sock = socket.socket()

server_ip = socket.gethostname()
server_port = 1234
sock.connect((server_ip, server_port))

while True:
    msg_to_server = input("Enter message to server: ")
    sock.sendall(msg_to_server.encode())
    msg_from_server = sock.recv(1024).decode()
    print(f"Message from server: {msg_from_server}")
