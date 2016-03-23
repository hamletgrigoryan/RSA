CC = gcc 
CFLAGS = -Wall 
LIBS=-lcrypto 
INCLUDES=-I./headers 
TARGET=./bin/rsa 

SRC=rsa.c src/rsa_encrypt_decrypt.c 


build : $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(CFLAGS) $(LIBS) $(INCLUDES) $(SRC)

clean : 
	rm -rf ./bin/*

