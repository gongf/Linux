.PHONY:all
all:client server

client:client.c
	gcc -o $@ $^
server:server.c
	gcc -o $@ $^ -static
.PHONY:clean
clean:
	rm -rf client server
