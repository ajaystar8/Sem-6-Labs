import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

udp_host = socket.gethostname()
udp_port = 12347

sock.sendto("Send Time.".encode(), (udp_host, udp_port))

print("Waiting for server...")
data, addr = sock.recvfrom(1024)
print("Current time is: ", data.decode())

