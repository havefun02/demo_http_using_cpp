CXX ?= g++
  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS= -g  -Wall
  # The build target 
  # TARGET 
server: server.o
  $(CXX) $(CFLAGS) -o server server.o
server.o: sever.cpp
  $(CXX) $(CFLAGS)  -pthread -I/sw/include/root -c server.cpp.
clean:  rm -f *.o rm server