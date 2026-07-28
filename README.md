# Networking
A small asynchronous networking library written in C++, written up from the sockets level .

I undertook this task for educational purposes. More specifically, to:

1. Increase my proficiency at C++
2. Understand the low level workings of networking
3. Implement threading and parallelism in a project

I was inspired by a live-coding talk by Bloomberg on our campus which utilised a library called stdnet to build something similar. 

---

## Developer Diary

I decided to keep track of my progress on this project, notating my design decisions down here.

### Getting Started/Project structure 

This is my first large C++ project. I decided to go for the following project structure:

#### src/

Main application logic.

#### include/ 

Header files.

#### examples/

To contain examples that I build with my networking library.




### Socket level

I first learned the basics of the TCP protocol and the processes happening under the hood, before getting my hands dirty by building client server logic for a single user.
I didn't like the functional interface that I had to use, and thus I wanted to abstract a lot of the low level details away, leaving a more object oriented interface at the surface.

I created `net::acceptor` as a wrapper around a socket which listens on a port and accepts connection requests. A programmer would only need to specify what port its listening on, and call `acceptor.blockingAccept()` to establish a connection with a client.
A connection is encapsulated by `net::connection`. It maintains a connection handle, and allows us to send and receive data easily. I package the received data from a connection handle in a `struct RecvData` which stores lots of useful information.
Through creating these classes, I learnt a lot about concepts like RAII, dynamic allocation, smart pointers and so on. 

With this we can start to build some synchronous networking systems, like servers which handle a single client at a time. I created `plainBlockingServer.cpp`, which waits for a connection with some client and exchanges messages.

### Async

Right now, functions like `accept()` and `recv()` are blocking. This is fixed with a simple call to `fcntl()` to stop the sockets from blocking. From here, I can begin to investigate different asynchronous programming techniques.

#### poll()
The first technique I wanted to try was the `poll()` system call. We pass it an array `pollfd[]`, which is an array objects which encapsulate polling information about file descriptors. The function blocks until one or more events are detected. This information is written to the `pollfd.revents` field in each object, and we can iterate through the array, handling the events appropriately. 

I established my main event loop and delegated handling to specific functions, and I found it was more difficult than expected to integrate my object oriented interface. I ran into several problems, most notably to do with maintaining some collection of all open connections. My `acceptor.acceptConnection()` function returned a connection object, which owns its corresponding socket and closes it once the object goes out of scope.  
