CXX=g++
DIR=/home/lapphan/Project1/src/client
CFLAGS=-g -I$(DIR) -I. -c
LFLAGS=-g
main:	main.o socket.o
	$(CXX)	$(LFLAGS)	-o	main	main.o	socket.o
main.o:	$(DIR)/main.cpp $(DIR)/socket.h	
	$(CXX)	$(CFLAGS)	$(DIR)/main.cpp
socket.o: $(DIR)/socket.cpp $(DIR)/socket.h
	$(CXX)	$(CFLAGS)	$(DIR)/socket.cpp
clean:
	rm	-rf	*.o	main
