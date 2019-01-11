CFLAGS += -Wall -Wextra -Wpedantic -Waggregat-return -Wwrite-strings -Wvla -Wfloat-equal

CFLAGS += -std=c11

bin/signaler: src/signaler.o 
	$(CC) $(CFLAGS) $^ -o bin/signaler

debug: CFLAGS += -g
debug: src/signaler.o 
	$(CC) $(CFLAGS) $^ -o bin/signaler

profile: CFLAGS += -pg
profile: src/signaler.o 
	$(CC) $(CFLAGS) $^ -o bin/signaler

.PHONY: clean

clean:
	rm -f *.o *.out ./src/*.o 

