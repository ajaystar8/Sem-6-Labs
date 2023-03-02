import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_ip = socket.gethostname()
server_port = 1972

while True:
    num1 = input("Enter the first number: ")
    sock.sendto(num1.encode(), (server_ip, server_port))
    num2 = input("Enter the second number: ")
    sock.sendto(num2.encode(), (server_ip, server_port))
    avg, _ = sock.recvfrom(1024)
    print(
        f"The average of the two numbers recieved from server is: {avg.decode()}")
