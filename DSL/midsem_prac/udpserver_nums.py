import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

my_ip = socket.gethostname()
my_port = 1972
sock.bind((my_ip, my_port))

while True:
    num1, client_addr = sock.recvfrom(1024)
    print(f"First number recieved from client: {num1.decode()}")

    num2, client_addr = sock.recvfrom(1024)
    print(f"Second number recieved from client: {num2.decode()}")

    avg = str((int(num1.decode()) + int(num2.decode()))/2)

    print(f"Average of the two numbers is: {avg}")
    sock.sendto(avg.encode(), client_addr)
