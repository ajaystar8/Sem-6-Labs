import socket
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

udp_host = socket.gethostname()
udp_port = 12347

sock.bind((udp_host, udp_port))

while True: 
    data, addr = sock.recvfrom(1024)
    print("Client says: ", data.decode())
    currentTime = time.ctime(time.time())
    sock.sendto(currentTime.encode('ascii'), addr)
    