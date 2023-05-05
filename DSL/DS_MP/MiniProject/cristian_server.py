#!/usr/bin/env python3
import socket
import datetime
def initiateClockServer():
    s = socket.socket()
    print("Socket successfully created")
    port = 8004
    s.bind(('', port))
    s.listen(5)	
    print("Server is listening.")

    while True:
        connection, address = s.accept()	
        print('Server connected to', address)
        connection.send(str(datetime.datetime.now()).encode())
        connection.close()
        
if __name__ == '__main__':
	initiateClockServer()
