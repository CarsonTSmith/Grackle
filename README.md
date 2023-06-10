# Grackle

Grackle Server is written for BSD Sockets only.

To build the project follow the steps below.

First clone the git repository.

To build this project you will need a C++ 17 Compiler (I use GNU Compilers) a C++ Linker (I use GNU) a shell script language (I use Bash), and GNU Make.

After you have the toolchain, open a terminal to the top of the project (/dir/where/you/cloned/..../Grackle/server

Then type "bash build.sh" or "sh build.sh"

After the project is built the resulting binary executable can be found in /Grackle/bin

Then you can start the server by running the executable. By default it will listen on port 42125.


# Basics of what Grackle is
Grackle is a TCP server that is similar to http. Grackle "messages" have the form

00000070{"path":"/request/path","jsonkey":"jsonvalue","jsonkey1":"jsonvalue1"}

where the first 8 bytes are the length of the json body as a string.

# Navigating the Code
Under the src/ folder is where the all of the code is. The main section of the code and the main entry point can be found under  src/core/
The path "endpoints" code can be found under src/core/request_router.hpp(cpp).
This maps request endpoints to actions.

