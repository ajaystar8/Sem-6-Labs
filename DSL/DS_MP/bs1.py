# Python3 program imitating a server process

import socket
import threading
from datetime import datetime

# lock to synchronize access to variable
lock = threading.Lock()

# list of times received from the clients
times = []


# thread function for handling a client connection
def handle_client(client_socket):
    while True:
        # receive time from the client
        hour = int(client_socket.recv(1024).decode())
        minute = int(client_socket.recv(1024).decode())

        # acquire lock to update the list of times
        with lock:
            times.append((hour, minute))

            # calculate average time
            total_hours = 0
            total_minutes = 0
            for time in times:
                total_hours += time[0]
                total_minutes += time[1]

            avg_hours = total_hours // len(times)
            avg_minutes = total_minutes // len(times)

        # send the synchronized time back to the client
        client_socket.send(str(avg_hours).encode())
        client_socket.send(str(avg_minutes).encode())


# function to start the server process
def start_server(port=8080):
    server_socket = socket.socket()

    # bind the socket to a public host and port
    server_socket.bind(('0.0.0.0', port))

    # become a server socket
    server_socket.listen()

    print("Server is listening on port", port)

    while True:
        # accept connections from outside
        client_socket, address = server_socket.accept()

        print("Accepted connection from", address)

        # start a new thread to handle the client connection
        client_thread = threading.Thread(
            target=handle_client,
            args=(client_socket,)
        )
        client_thread.start()


# driver function
if __name__ == '__main__':
    # start the server
    start_server()
