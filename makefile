CC = g++ -std=c++11
.cpp.o:
	$(CC) -c -o $@ $*.cpp

OBJS_MAIN = life.o

all: tran
tran: life

life: $(OBJS_MAIN)
	$(CC) -o ./life $(OBJS_MAIN)

clean:
	-rm -f *.o ./life
