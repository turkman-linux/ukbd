import socket
import os

# Set the path for the Unix socket
socket_path = '/dev/amogus'

# Create the Unix socket client
client = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)

# Connect to the server
client.connect(socket_path)

# Send a message to the server
while True:
    msg = input()
    if msg == "":
        exit(0)
    try:
        message = chr(int(msg))
        client.sendall(message.encode())
    except:
        pass


# Close the connection
client.close()
