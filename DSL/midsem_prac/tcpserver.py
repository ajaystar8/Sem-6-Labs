import socket

s = socket.socket()

my_IP = socket.gethostname()
my_port = 3002
s.bind((my_IP, my_port))

s.listen(5)
client_conn, client_addr = s.accept()

print(f"Client connection: {client_conn}")
print(f"Client address: {client_addr}")

while True:
    data = client_conn.recv(1024)
    print("The sender sent : ", data.decode())
    msg = input("Enter a message to send : ")
    client_conn.sendall(msg.encode())
