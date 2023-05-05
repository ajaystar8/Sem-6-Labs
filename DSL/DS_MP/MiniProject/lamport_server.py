#!/usr/bin/env python3
import socket
import time
import random
def start_server():
    s = socket.socket()
    print("Socket successfully created")
    port = 8011
    s.bind(('', port))
    s.listen(5)
    lamport_clock = 0
    print(f'Server is listening.')
    while True:
        conn, addr = s.accept()
        print(f'Server connected to: {addr}')
        data = conn.recv(1024)
        if not data:
            break
        message = data.decode()
        message_timestamp = int(message.split(':')[1])
        lamport_clock = max(lamport_clock, message_timestamp) + 1
        current_time = ((time.time() * 1000))
        time_difference = current_time - message_timestamp
        print(f'\nReceived message "{message}" from {addr}.\n'
              f'Updated Lamport clock to {lamport_clock}.\n'
              f'Time difference: {time_difference} ms\n')
        conn.sendall('ack'.encode())
        conn.close()


if __name__ == '__main__':
    start_server()
