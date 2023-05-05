#!/usr/bin/env python3
import socket
import time
import threading

HOST = 'localhost'
PORT = 12345

def handle_client(conn, addr):
    print(f'Connected by {addr}')

    while True:
        data = str(time.time()).encode('utf-8')
        conn.sendall(data)
        time.sleep(1)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print('Server started')

    while True:
        conn, addr = s.accept()
        t = threading.Thread(target=handle_client, args=(conn, addr))
        t.start()