from socket import *
import time
import struct

address = ('10.0.0.100', 5000)  # define who im talking too
client_socket = socket(AF_INET, SOCK_DGRAM)  # UDP
client_socket.settimeout(1)# wait one second to response


while True:
    data = "Blue" # Set data to aduino
    data = data.encode('ASCII')
    client_socket.sendto(data, address) # send command to arduino
    try:
        rec_data, addr = client_socket.recvfrom(2048) # Reading response from arduino
        print(rec_data) # Print the response from arduino
        
    except:
        pass
    
    time.sleep(2) # delay before sending next command
    
    data = "Red" # Set data to aduino
    data = data.encode('ASCII')
    client_socket.sendto(data, address) # send command to arduino
    try:
        rec_data, addr = client_socket.recvfrom(2048) # Reading response from arduino
        print(rec_data) # Print the response from arduino
        
    except:
        pass
    
    time.sleep(2)
    
    data = "Green" # Set data to aduino
    data = data.encode('ASCII')
    client_socket.sendto(data, address) # send command to arduino
    try:
        rec_data, addr = client_socket.recvfrom(2048) # Reading response from arduino
        print(rec_data) # Print the response from arduino
        
    except:
        pass
    
    time.sleep(2)
    
