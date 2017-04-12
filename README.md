# os-experiment-3
Three ways of the process interaction:shared memory, pipe and socket.

 share.c//The code of shared memory implementation
 
 To run this program: 
 
 g++ share.c -o share

./share

The output is the address of the shared memory to be attached and to be reattached.

pipe.c//The code of pipe

To run this program: 

g++ pipe.c -o pipe

./pipe

The output is "Hello world" for 5 times from child process to parent process by pipe.

socket-server.c//server of socket

socket-client.c//server of client

To run this program: 

g++ socket-server.c -o socket-server

g++ socket-client.c -o socket-client

./socket-server

Open another terminal and change to the same directory,then input:

./socket-client "Hello[or something else you want to send to server]"

./socket-client "quit[to end the socket]"

The output is the message server get by socket.

