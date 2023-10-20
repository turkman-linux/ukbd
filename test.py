import socket
import os

# Set the path for the Unix socket
socket_path = '/dev/input/amogus'

# Create the Unix socket client
client = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)

# Connect to the server
client.connect(socket_path)

# Send a message to the server
while True:
    message = chr(int(input()))
    client.sendall(message.encode())


# Close the connection
client.close()
