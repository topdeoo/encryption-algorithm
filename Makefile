CC = g++
OBJ = md5.o rsa.o main.o
DIR = src
EXE = main

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(DIR)/*

md5.o:
	$(CC) -c $(DIR)/md5.cpp

main.o:
	$(CC) -c $(DIR)/main.cpp

rsa.o:
	$(CC) -c $(DIR)/RSA.cpp

clean:
	rm -f *.o
