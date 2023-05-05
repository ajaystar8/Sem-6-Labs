import multiprocessing
import subprocess
import time

num_clocks = int(input("Enter the number of clocks to be synchronized: "))
algorithm = input("Enter the algorithm to be used (Lamport, Cristian, or Berkeley): ")

p = subprocess.Popen(["open", "-a", "Terminal", "--new", "", algorithm.lower() + "_server.py"])
time.sleep(5)
processes = []
for i in range(num_clocks-1):
        p = subprocess.Popen(["open", "-a", "Terminal", "--new", "", algorithm.lower() + "_client.py"])
        processes.append(p)
        
for p in processes:
    p.wait()
