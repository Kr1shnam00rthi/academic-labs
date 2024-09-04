import socket

# Set up the server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ("localhost", 12345)

# Bind the socket to the server address and listen for incoming connections
server_socket.bind(server_address)
server_socket.listen(1)

print(f"Server is listening on {server_address}")

while True:
    # Wait for a connection
    connection, client_address = server_socket.accept()
    try:
        print(f"Connection from {client_address}")

        # Receive data in small chunks and retransmit it
        while True:
            data = connection.recv(1024)
            if data:
                print(f"Received: {data.decode()}")
                response = "Message received"
                connection.sendall(response.encode())
            else:
                break
    finally:
        # Clean up the connection
        connection.close()

