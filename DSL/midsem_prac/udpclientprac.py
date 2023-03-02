import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_ip = socket.gethostname()
server_port = 1567

while True:
    msg = input("Enter a message to client: ")
    sock.sendto(msg.encode(), (server_ip, server_port))
    msg_from_server, server_addr = sock.recvfrom(1024)
    print(f"server replies: {msg_from_server.decode()}")
