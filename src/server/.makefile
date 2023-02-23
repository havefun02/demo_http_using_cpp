CPP=g++
server:	server.o
	$(CPP)	-o	server	server.o
server.o:	server.cpp
	$(CPP)	-c	server.cpp
clean:
	rm	-f	*.o
