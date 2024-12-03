from socket import *
s = socket(AF_INET, SOCK_STREAM)
s.connect(("localhost", 9000))
s.send(b"Hello server\n")
data = s.recv(10000)
print(data)
s.close()
