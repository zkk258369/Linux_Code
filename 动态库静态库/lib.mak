SHELL = /bin/sh
AR = ar
cc = g++

CFLAG = -02 -W -Wall

LIB_PATH = ./
LIB_TARGET = ./libfun.a

MAX_OBJ = ./max.o
MAX_SRC = ./max.cpp

ADD_OBJ = ./add.o
ADD_SRC = ./add.cpp

all : $(LIB_TARGET)
$(MAX_OBJ) : $(MAX_SRC)
	$(cc) -c $(MAX_SRC)
	
$(ADD_OBJ) : $(ADD_SRC)
	$(cc) -c $(ADD_SRC)
	
$(LIB_TARGET) : $(MAX_OBJ) $(ADD_OBJ)
	$(AR) crv $@ $^
	mv $(MAX_OBJ) ./bin/$(MAX_OBJ)
	mv $(ADD_OBJ) ./bin/$(ADD_OBJ)
	mv $(LIB_TARGET) ./bin/$(LIB_TARGET)
	
clean:
	rm -f $(ADD_OBJ)
	rm -f $(MAX_OBJ)
	rm -f $(LIB_TARGET)