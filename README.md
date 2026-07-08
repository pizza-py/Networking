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

Files to be compiled with the application

#### examples/

To contain examples that I build with my networking library




### Socket level

I first learned the basics of the TCP protocol and the processes happening under the hood, before getting my hands dirty by building client server logic for a single user.
I didn't like the C-esque functional interface that I had to use, and thus I wanted to abstract a lot of the low level details away, leaving a more object oriented interface at the surface.

