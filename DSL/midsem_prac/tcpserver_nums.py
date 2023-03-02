import socket

sock = socket.socket()

my_ip = socket.gethostname()
my_port = 2021
sock.bind((my_ip, my_port))

sock.listen(5)
client_conn, client_addr = sock.accept()

while True:
    num1 = int(client_conn.recv(1024).decode())
    print(f"First number recieved: {num1}")
    num2 = int(client_conn.recv(1024).decode())
    print(f"Second number recieved: {num2}")
    avg = str((num1 + num2)/2)
    print(f"Average calculated: {avg}")
    client_conn.sendall(avg.encode())
