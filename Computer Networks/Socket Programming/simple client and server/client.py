import socket
import rsa
import hashlib
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


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 65535))

client_public_key, client_private_key = generate_rsa_keys()

client_socket.send(client_public_key.save_pkcs1())

server_public_key_data = client_socket.recv(1024)
server_public_key = rsa.PublicKey.load_pkcs1(server_public_key_data)

encrypted_symmetric_key = client_socket.recv(1024)
symmetric_key = decrypt_symmetric_key(encrypted_symmetric_key, client_private_key)

while True:
    
    message = input("Client: ")
    encrypted_message = encrypt_message(message, symmetric_key)
    print("Encrypted message to server: ", encrypted_message)
    message_hash = compute_hash(encrypted_message)
    print("Hash of encrypted message to server: ", message_hash)

    if message.upper() == "EXIT":
        break

    client_socket.send(message_hash.encode() + encrypted_message)

    
    response = client_socket.recv(1024)
    if not response:
        break

    
    received_hash, ciphertext = response[:64], response[64:]
    print("Encrypted message from server: ", ciphertext)
    print("Hash of encrypted message from server: ", received_hash.decode())

    if compute_hash(ciphertext) != received_hash.decode():
        print("Hash verification failed.")
        continue

    reply = decrypt_message(ciphertext, symmetric_key)
    print(f"Server: {reply}")

    if reply.upper() == "EXIT":
        break

client_socket.close()
