import socket

cs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
cs.connect(('localhost', 9001))
print('[PYTHON CLIENT] Connection established.')

n1 = input("[PYTHON CLIENT] Enter 1st number to be sent to the server: ")
cs.send(n1.encode())
n2 = input("[PYTHON CLIENT] Enter 2nd number to be sent to the server: ")
cs.send(n2.encode())

data = cs.recv(1024)
sum = data.decode()
print("[PYTHON CLIENT] Sum received from server: " + sum)

cs.close()

#import socket

#s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#s.connect((socket.gethostname(), 9001))

#full_msg = ''
#while True:
#    msg = s.recv(1024)
#    if len(msg) <= 0:
#        break
#    full_msg += msg.decode("utf-8")
#print(full_msg)

