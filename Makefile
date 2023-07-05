CC = gcc
CFLAGS = -Wall -Wno-return-type -Wno-error=return-type -pedantic -g
EXEC = cq
OBJ = cq.o generate_c_file.o c_queue.o customer.o teller.o log.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -pthread -o $(EXEC)

cq.o: cq.c generate_c_file.h c_queue.h customer.h teller.h shared.h
	$(CC) $(CFLAGS) -pthread -c cq.c

customer.o: customer.c customer.h c_queue.h shared.h log.h
	$(CC) $(CFLAGS) -pthread -c customer.c

c_queue.o: c_queue.c c_queue.h 
	$(CC) $(CFLAGS) -pthread -c c_queue.c

generate_c_file.o: generate_c_file.c generate_c_file.h 
	$(CC) $(CFLAGS) -pthread -c generate_c_file.c

teller.o: teller.c teller.h c_queue.h shared.h log.h
	$(CC) $(CFLAGS) -pthread -c teller.c 

log.o: log.c log.h
	$(CC) $(CFLAGS) -pthread -c log.c 

clean:
	del -f *.exe
	del -f *.o

	