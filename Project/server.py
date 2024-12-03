from socket import *
s = socket(AF_INET, SOCK_STREAM)
s.bind(("", 9000))
s.listen(5)
while True: 
    c,a = s.accept()
    print("Received connection from", a)
    c.send(b"Hello client\n")
    data = c.recv(10000)
    print(data)
    c.close()