import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

my_ip = socket.gethostname()
my_port = 1567
sock.bind((my_ip, my_port))

while True:
    print("Waiting for client.")
    msg_from_client, client_addr = sock.recvfrom(1024)
    print(f"Client says: {msg_from_client.decode()}")
    msg_to_client = input("Reply to client: ")
    sock.sendto(msg_to_client.encode(), client_addr)
