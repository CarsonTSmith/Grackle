# Grackle

Grackle Server is written for BSD Sockets only.

To build the project follow the steps below.

First clone the git repository.

To build this project you will need a C++ 17 Compiler (I use GNU Compilers) a C++ Linker (I use GNU) a shell script language (I use Bash), and GNU Make.

After you have the toolchain, open a terminal to the top of the project (/dir/where/you/cloned/..../Grackle/server

Then type "bash build.sh" or "sh build.sh"

After the project is built the resulting binary executable can be found in /Grackle/server/bin

Then you can start the server. By default it will listen on port 42125.
