import socket
import os

HOST = "0.0.0.0"
PORT = 5000


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)

print(f"Server listening on port {PORT}...")

while True:
    conn, addr = server_socket.accept()
    print(f"Connected by {addr}")

    
    filename = conn.recv(1024).decode()

    print(f"Client requested: {filename}")

   
    if os.path.isfile(filename):
        with open(filename, "r") as f:
            data = f.read()
        conn.sendall(data.encode())
    else:
        conn.sendall(b"ERROR: File not found")

    conn.close()
