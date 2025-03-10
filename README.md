## Simple Socket Program

### Introduction

In this activity, a client and a server program were developed. These programs communicate with
each other using TCP/IP sockets. The client receives a name and a number from the user and sends
this information to the server. The server processes the incoming information and sends its own name
and a number back to the client. In addition, the server and the client calculate the sum of the numbers
and print them on the screen. The server side was developed to process the responses of more than
one client.

### Project Structure and Working Logic

The program consists of three main files:

**server.c:** Contains the server program. The server listens to a specific port and accepts incoming
client connections. It creates a new process for each client connection and manages communication
with the client through this process. At this point, the server is configured with fork to process
messages from multiple clients.

The server program performs the following operations:

- *Creating a Socket:* A TCP socket is created with the createTCPIpv4Socket() function.
- *Configuring the Address:* The IP address and port of the server are configured with the
createIPv4Address() function.
- *Listening for Connections:* The server starts listening to the specified port with the bind()
and listen() functions.
- *Accepting Client Connections:* Incoming client connections are accepted with the accept()
function.
- *Synchronous Process:* A new process is created with the fork() function for each new client
connection. This process manages communication with the client.
- *Processing the Client Message:* The message from the client is received, and a response is
sent with the server's name and a number. In addition, the sum of the client and server
numbers is calculated and printed on the screen.


**client.c:** Contains the client program. The client receives a name and a number from the user, sends
this information to the server, and prints the response from the server to the screen.
The client program performs the following operations:

- *Creating a Socket:* A TCP socket is created with the createTCPIpv4Socket() function.
- *Connecting to the Server:* A connection is established to the server with the connect()
function.
- *Getting Information from the User:* A name and a number are received from the user.
- *Sending a Message:* The information received is sent to the server.
- *Getting a Response from the Server:* The response from the server is received and printed
on the screen.

**socketUtilize.c and socketUtilize.h:** Contains the socket functions that perform socket creation and
address configuration operations.

- *createTCPIpv4Socket():* Creates a TCP/IPv4 socket.
- *createIPv4Address():* Creates an IPv4 address structure. If no IP address is specified (""),
INADDR_ANY is used.

#### Using the program with a single client:

![Screenshot from 2025-03-09 22-36-03](https://github.com/user-attachments/assets/6ccecbac-420d-47dc-aad8-e338a821deb6)

#### Using the program with multiple clients:

![Screenshot from 2025-03-09 22-53-15](https://github.com/user-attachments/assets/1e256dd9-e402-4cae-9a72-8fc00f9791f8)

![Screenshot from 2025-03-09 23-07-29](https://github.com/user-attachments/assets/d2ae2138-a7a9-4be8-a3d6-d2dca3465813)

