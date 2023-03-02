import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# setting up address of server
my_ip = socket.gethostname()
my_port = 1234
sock.bind((my_ip, my_port))

while True:
    print("Waiting for client.")
    data, client_addr = sock.recvfrom(1024)
    print(
        f"Received message from client: {data.decode()}")

    # Sending a reply to client
    msg = "Hello from server."

    sock.sendto(msg.encode(), client_addr)
