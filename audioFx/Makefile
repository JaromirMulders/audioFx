CC = g++
CFLAGS =  -g -Wall
LDFLAGS = -L /usr/local/lib -ljack -lpthread
OBJ= main.o effect.o emptyFx.o delay.o tremolo.o distortion.o filter.o

main: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)


.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
