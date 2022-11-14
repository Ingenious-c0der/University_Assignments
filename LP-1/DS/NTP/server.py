from socket import *
import threading
import time
import random
server_time = "" # server time
time_list = ["12345","23456","34567"]
def handler(clientsock, addr):
    while 1:
        print("------------------------------------")
        server_time = random.choice(time_list)
        time.sleep(4)
        data = clientsock.recv(1024)
        if not data:
            break
        client_time = data.decode()
        print(client_time + " is the client time of client on : ", addr)
        if(client_time!= f"{server_time}"):
            print(f"Client time: {client_time}")
            print(f"Server time: {server_time}")
            print("Time is not synced")
            clientsock.send(bytes(f"{server_time}", encoding='utf8'))
        else: 
            print(f"Client time is synchronized with Server: {client_time}")
            clientsock.send(bytes(f"{server_time}", encoding='utf8'))
        
        print("------------------------------------ \n")
    
    clientsock.close()


HOST = ''
PORT = 5555
ADDR = (HOST, PORT)

serversock = socket(AF_INET, SOCK_STREAM)
serversock.bind(ADDR)
serversock.listen(5)

print('Server Live at port ' + str(PORT))
while 1:
    server_time = random.choice(time_list) #selecting a random server time to be updated with client
   
    clientsock, addr = serversock.accept()
    print('Connection from: ', addr)
    threading.Thread(target=handler, args=(clientsock, addr)).start()