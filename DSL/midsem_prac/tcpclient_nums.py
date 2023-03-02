import socket

sock = socket.socket()

server_ip = socket.gethostname()
server_port = 2021
sock.connect((server_ip, server_port))

while True:
    num1 = input("Enter the first number: ")
    sock.sendall(num1.encode())
    num2 = input("Enter second number: ")
    sock.sendall(num2.encode())
    avg = sock.recv(1024).decode()
    print(f"Average of the two numbers are: {avg}")
