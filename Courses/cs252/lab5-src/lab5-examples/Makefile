CXX = g++ -fPIC
NETLIBS= -lnsl

all: tls daytime-server use-dlopen hello.so

tls: tls_server.c
	$(CC) `pkg-config --cflags openssl` -o $@ $^ `pkg-config --libs openssl`
	@echo "Don't forget to create cert.pem and key.pem"

daytime-server : daytime-server.cc
	$(CXX) -o $@ $< $(NETLIBS)

use-dlopen: use-dlopen.cc
	$(CXX) -o $@ $< $(NETLIBS) -ldl

hello.so: hello.o
	ld -G -o hello.so hello.o

clean:
	rm -f tls daytime-server use-dlopen hello.so hello.o
