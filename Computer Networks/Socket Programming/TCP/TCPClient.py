import socket

# Set up the client
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ("localhost", 12345)

# Connect to the server
client_socket.connect(server_address)

try:
    # Send a message to the server
    message = "Hello, Server!"
    client_socket.sendall(message.encode())

    # Wait for the response
    data = client_socket.recv(1024)
    print(f"Received response from server: {data.decode()}")
finally:
    # Close the socket
    client_socket.close()

