import socket

sock = socket.socket()

my_ip = socket.gethostname()
my_port = 2023
sock.bind((my_ip, my_port))

sock.listen(5)
client_conn, client_addr = sock.accept()

while True:
    rcvd_msg = client_conn.recv(1024).decode()
    print(f"Message recieved from client: {rcvd_msg}")
    client_conn.sendall(rcvd_msg.encode())
