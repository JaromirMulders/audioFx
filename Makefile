CC = g++
CFLAGS =  -g -Wall
LDFLAGS = -L /usr/local/lib -lportaudio -lpthread
OBJ= main.o distortion.o tremolo.o delay.o filter.o emptyFx.o effect.o audio_io.o osc_server.o osc.o

main: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) -llo


.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
