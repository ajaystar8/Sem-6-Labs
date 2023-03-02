import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

udp_host = "172.16.58.108"
udp_port = 31621

sock.bind((udp_host, udp_port))

while True: 
    data, addr = sock.recvfrom(1024)
    print("Client says: ", data.decode())
    data = input("Enter message to client: ")
    sock.sendto(data.encode(), addr)
    