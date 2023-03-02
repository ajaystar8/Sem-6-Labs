import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_ip = socket.gethostname()
server_port = 1234
server_addr = (server_ip, server_port)


msg = "Hello from client."

print(f"UDP server IP: {server_ip}")
print(f"UDP server port: {server_port}")

sock.sendto(msg.encode(), server_addr)

msgFromServer = sock.recvfrom(1024)

print(f"Message recieved from server: {msgFromServer[0].decode()}")
