CC= g++
BIN = bin
SRC = src
OBJ = obj
CFLAGS = -std=c++11 -O3 -g -Wall 
OUT = $(BIN)/mm_convert_snap_file

# where to find source codes
vpath %.cc $(SRC)

all: $(OUT) Makefile

$(BIN)/mm_convert_snap_file: $(OBJ)/mm_convert_snap_file.o $(OBJ)/mmio.o
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $(OBJ)/mmio.o $(OBJ)/mm_convert_snap_file.o -o $@	

$(OBJ)/%.o: %.cc
	if [ ! -d obj ]; then mkdir obj; fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)/*.o $(OUT) 
