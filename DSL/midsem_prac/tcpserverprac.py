import socket

sock = socket.socket()

my_ip = socket.gethostname()
my_port = 1234
sock.bind((my_ip, my_port))

sock.listen(5)
client_conn, client_addr = sock.accept()

while True:
    print("Waiting for client.")
    msg_from_client = client_conn.recv(1024).decode()
    print(f"Message from client: {msg_from_client}")
    msg_to_client = input("Enter message to client: ")
    client_conn.sendall(msg_to_client.encode())
