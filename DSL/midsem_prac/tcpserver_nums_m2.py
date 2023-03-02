import socket
import numpy as np

sock = socket.socket()

my_ip = socket.gethostname()
my_port = 2021
sock.bind((my_ip, my_port))

sock.listen(5)
client_conn, client_addr = sock.accept()

while True:
    nums = np.array(client_conn.recv(1024).decode().split(","), dtype=int)
    print(f"Numbers recieved: {nums}")
    avg = str(np.mean(nums))
    print(f"Average calculated: {avg}")
    client_conn.sendall(avg.encode())
