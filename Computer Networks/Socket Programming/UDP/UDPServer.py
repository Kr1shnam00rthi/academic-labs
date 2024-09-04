import socket 

server_socket=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server_address=("localhost",12345)

server_socket.bind(server_address)

while True:
	data, client_address=server_socket.recvfrom(1024)
	print("Message {data.decode()} from {client address}")
	
	response="Message received"
	server_socket.sendto(response.encode(),client_address)
	
