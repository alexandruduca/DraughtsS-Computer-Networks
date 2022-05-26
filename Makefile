
s:
	gcc server.c -o server
	./server
	
c:
	gcc client.c -o client
	./client 127.0.0.1 2103