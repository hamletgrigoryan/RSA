CC = gcc 
CFLAGS = -Wall 
LIBS=-lcrypto 
INCLUDES=-I./headers 
TARGET=./bin/rsa 

SRC=rsa.c src/rsa_encrypt_decrypt.c src/blocking.c


build : $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(LIBS) $(INCLUDES) $(SRC)

clean : 
	rm -rf ./bin/*

