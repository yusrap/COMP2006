CC = gcc
CFLAGS = -Wall -Wno-return-type -Wno-error=return-type -pedantic -g
EXEC = cq
OBJ = src/cq.o src/generate_c_file.o src/c_queue.o src/customer.o src/teller.o src/log.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -pthread -o $(EXEC)

src/cq.o: src/cq.c include/generate_c_file.h include/c_queue.h include/customer.h include/teller.h include/shared.h
	$(CC) $(CFLAGS) -pthread -c src/cq.c -o src/cq.o

src/customer.o: src/customer.c include/customer.h include/c_queue.h include/shared.h include/log.h
	$(CC) $(CFLAGS) -pthread -c src/customer.c -o src/customer.o

src/c_queue.o: src/c_queue.c include/c_queue.h 
	$(CC) $(CFLAGS) -pthread -c src/c_queue.c -o src/c_queue.o

src/generate_c_file.o: src/generate_c_file.c include/generate_c_file.h 
	$(CC) $(CFLAGS) -pthread -c src/generate_c_file.c -o src/generate_c_file.o

src/teller.o: src/teller.c include/teller.h include/c_queue.h include/shared.h include/log.h
	$(CC) $(CFLAGS) -pthread -c src/teller.c -o src/teller.o 

src/log.o: src/log.c include/log.h
	$(CC) $(CFLAGS) -pthread -c src/log.c -o src/log.o

clean:
	@for %%i in (src\*.o) do @del %%i
	@del /Q *.exe