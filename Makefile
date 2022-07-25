CC = g++
OBJ = md5.o
DIR = src
EXE = md5

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ)

md5.o:
	$(CC) -c $(DIR)/md5.cpp

clean:
	rm -f *.o
