default: 
	gcc -o mysemaphore mysemaphore.c -lpthread
	make block
compile :
	gcc -o mysemaphore mysemaphore.c -lpthread
	gcc -o non_blocking non_blocking.c -lpthread
nonblock :
	./non_blocking
block :
	./mysemaphore