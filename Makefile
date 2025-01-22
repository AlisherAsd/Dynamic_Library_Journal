CC=gcc

all: build

build: main.o lib.so Message.o Journal.o app.o
	mkdir build
	$(CC) main.o app.o lib.so -lstdc++  -o app
	mv main.o lib.so Message.o Journal.o app app.o ./build


main.o: main.cpp
	$(CC) -c main.cpp -o main.o

app.o: lib/include/app.cpp
	$(CC) -c lib/include/app.cpp -o app.o

Journal.o: lib/include/Journal.cpp
	$(CC) -c -fPIC lib/include/Journal.cpp -o Journal.o


Message.o: lib/include/Message.cpp
	$(CC) -c -fPIC lib/include/Message.cpp -o Message.o


lib.so: Message.o Journal.o
	$(CC) -shared Message.o Journal.o -o lib.so


clean:
	rm -rf ./build