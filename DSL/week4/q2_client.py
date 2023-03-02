import socket

client_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

host = socket.gethostname()
port = 12321

while True: 
    data = input("Enter message to server: ")
    client_sock.sendto(data.encode(), (host, port))
    data, _ = client_sock.recvfrom(1024)
    print("Server says: ", data.decode())