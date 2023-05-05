#!/usr/bin/env python3
import socket
import time
from datetime import datetime

def start_client():
    client_clock = 0
    while True:
        client_socket = socket.socket()
        client_socket.connect(('127.0.0.1', 8011))
        current_time = int(time.time() * 1000)
        client_clock = max(client_clock, current_time) + 1
        message = 'sync'
        message_with_timestamp = f'{message}:{client_clock}'
        client_socket.sendall(message_with_timestamp.encode())
        ack = client_socket.recv(1024).decode()
        print(f'\nSent message "{message}" to server.\n'
            f'Updated client clock to {client_clock}.\n'
            f'Received acknowledgement: {ack}\n')
        client_socket.close()
        time.sleep(5)
    
if __name__ == '__main__':
    	start_client()
