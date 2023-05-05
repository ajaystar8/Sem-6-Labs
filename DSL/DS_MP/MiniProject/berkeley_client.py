#!/usr/bin/env python3
import socket
import time

HOST = 'localhost'
PORT = 12345

def calculate_offset(times):
    time_diffs = [server_time - client_time for client_time, server_time in times]
    avg_time_diff = sum(time_diffs) / len(time_diffs)
    return avg_time_diff

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        print('Connected to server')
        server_time = float(s.recv(1024).decode('utf-8'))
        client_time = time.time()
        offset = server_time - client_time
        s.sendall(str(offset).encode('utf-8'))
        adjusted_time = float(s.recv(1024).decode('utf-8'))
        time_diff = adjusted_time - client_time
        print(f'Time difference: {time_diff} seconds')
