from socket import *
import time 

HOST = "127.0.0.1"
PORT = 5555
client_time = "0" #client time 


print('Connected to server: (press exit to quit)')
serversock = socket(AF_INET, SOCK_STREAM)
serversock.connect((HOST, PORT))
data = ""
while data!="exit":
    input_String = client_time
    serversock.sendall(bytes(input_String, encoding='utf8'))
    data = serversock.recv(1024)
    data = data.decode()
    if(client_time == data):
        print("Client time is synchronized with Server")
    else:
        client_time = data
        print(f"Client time set to : {data}")
    time.sleep(4)
serversock.close()



