CXX=g++
LFLAGS=-g
SRC_PATH:=src/
CFLAGS=-g  $(SRC_PATH) -c
OUT=exe/
.PHONY : cleanall cleanobj
CPPFILES = src/main.cpp src/socket.cpp 
CPP_FILENAMES += $(notdir $(CPPFILES))
OBJ_FILES += $(patsubst %.cpp, $(SRC_PATH)%.o, $(CPP_FILENAMES) )
$(OUT)20127547_20127261:$(OBJ_FILES)
	$(CXX)	$(LFLAGS) -ggdb3 -O0 -pedantic-errors -std=c++11 -Wall -Wextra -o	$@ $^
$(SRC_PATH)%.o:$(SRC_PATH)%.cpp $(SRC_PATH)%.h
	$(CXX)	$(CFLAGS) $< -o $@
# clean:
# 	rm edit	src/main.o
# 	rm edit	src/socket.o
# 	rm edit -fr $(OUTPUT)20127547_20127261
cleanall: cleanobj
	rm edit $(OUTPUT)20127547_20127261

cleanobj:
	rm edit $(SRC_PATH)*.o
