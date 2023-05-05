#!/usr/bin/env python3
import socket
import datetime
from dateutil import parser
from timeit import default_timer as timer
import time

def synchronizeTime():
	
    port = 8004
	
    while True:
        s = socket.socket()		
        s.connect(('127.0.0.1', port))
        
        request_time = timer()
        server_time = parser.parse(s.recv(1024).decode())
        response_time = timer()
        actual_time = datetime.datetime.now()

        print("Time returned by server: " + str(server_time))

        process_delay_latency = response_time - request_time

        print("Process Delay latency: " \
            + str(process_delay_latency) \
            + " seconds")

        print("Actual clock time at client side: " \
            + str(actual_time))

        client_time = server_time \
                        + datetime.timedelta(seconds = \
                                (process_delay_latency) / 2)

        print("Synchronized process client time: " \
                                            + str(client_time))

        error = actual_time - client_time
        print("Synchronization error : "
                    + str(error.total_seconds()) + " seconds" + "\n\n")
        s.close()	
        time.sleep(5)



if __name__ == '__main__':
	synchronizeTime()
