import socket
import rsa
import hashlib
import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend


def generate_rsa_keys():
    public_key, private_key = rsa.newkeys(512)
    return public_key, private_key

def encrypt_symmetric_key(symmetric_key, rsa_public_key):
    encrypted_key = rsa.encrypt(symmetric_key, rsa_public_key)
    return encrypted_key

def decrypt_symmetric_key(encrypted_key, rsa_private_key):
    symmetric_key = rsa.decrypt(encrypted_key, rsa_private_key)
    return symmetric_key

def encrypt_message(message, symmetric_key):
    cipher = Cipher(algorithms.AES(symmetric_key), modes.ECB(), backend=default_backend())
    encryptor = cipher.encryptor()
    padded_message = message + (16 - len(message) % 16) * chr(16 - len(message) % 16)
    ciphertext = encryptor.update(padded_message.encode()) + encryptor.finalize()
    return ciphertext

def decrypt_message(ciphertext, symmetric_key):
    cipher = Cipher(algorithms.AES(symmetric_key), modes.ECB(), backend=default_backend())
    decryptor = cipher.decryptor()
    padded_message = decryptor.update(ciphertext) + decryptor.finalize()
    padding_length = padded_message[-1]
    return padded_message[:-padding_length].decode()


def compute_hash(data):
    return hashlib.sha256(data).hexdigest()


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 65535))
server_socket.listen(1)

print("Server is listening...")

client_socket, client_address = server_socket.accept()
print(f"Connected to {client_address}")


server_public_key, server_private_key = generate_rsa_keys()


client_socket.send(server_public_key.save_pkcs1())

client_public_key_data = client_socket.recv(1024)
client_public_key = rsa.PublicKey.load_pkcs1(client_public_key_data)


symmetric_key = os.urandom(16)  

encrypted_symmetric_key = encrypt_symmetric_key(symmetric_key, client_public_key)
client_socket.send(encrypted_symmetric_key)



while True:
    
    encrypted_message = client_socket.recv(1024)
    if not encrypted_message:
        break

    received_hash, ciphertext = encrypted_message[:64], encrypted_message[64:]
    print("Encrypted message from client: ", ciphertext)
    print("Hash of encrypted message from client: ", received_hash.decode())

    computed_hash = compute_hash(ciphertext)
    if computed_hash != received_hash.decode():
        print("Hash verification failed.")
        continue

    message = decrypt_message(ciphertext, symmetric_key)
    print(f"Client: {message}")

    if message.upper() == "EXIT":
        break

    reply = input("Server: ")
    encrypted_reply = encrypt_message(reply, symmetric_key)
    reply_hash = compute_hash(encrypted_reply)
    print("Encrypted message to client: ", encrypted_reply)
    print("Hash of encrypted message to client: ", reply_hash)
    client_socket.send(reply_hash.encode() + encrypted_reply)

    if reply.upper() == "EXIT":
        break

client_socket.close()
server_socket.close()
