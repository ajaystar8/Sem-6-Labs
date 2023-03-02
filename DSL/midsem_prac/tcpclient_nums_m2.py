import socket

sock = socket.socket()

server_ip = socket.gethostname()
server_port = 2021
sock.connect((server_ip, server_port))

while True:
    nums = input("Enter numbers seperated by ',': ")
    sock.sendall(nums.encode())
    avg = sock.recv(1024).decode()
    print(f"Average of the two numbers are: {avg}")
