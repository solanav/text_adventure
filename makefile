EXEC=game_exec die_test set_test
CC=gcc
CFLAGS=-Wall -g -pedantic

################ ALL

all: clean game_exec


################ EXEC CREATION

game_exec: game_loop.o command.o game_reader.o graphic_engine.o screen.o space.o object.o game.o player.o die.o
	$(CC) $(CFLAGS) -o $@ $^

die_test: die_test.o die.o
	$(CC) $(CFLAGS) -o $@ $^

set_test: set_test.o set.o object.o
	$(CC) $(CFLAGS) -o $@ $^

################ FILE COMPILATION 

player.o: player.c types.h player.h
	$(CC) $(CFLAGS) -c player.c

game_loop.o: game_loop.c graphic_engine.h
	$(CC) $(CFLAGS) -c game_loop.c

game_reader.o: game_reader.c game.h types.h
	$(CC) $(CFLAGS) -c game_reader.c

graphic_engine.o: graphic_engine.c graphic_engine.h screen.h
	$(CC) $(CFLAGS) -c graphic_engine.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

space.o: space.c space.h types.h set.h
	$(CC) $(CFLAGS) -c space.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

game.o: game.c game.h game_reader.h object.h player.h space.h set.h
	$(CC) $(CFLAGS) -c game.c

die_test.o: die_test.c die.h types.h
	$(CC) $(CFLAGS) -c die_test.c

die.o: die.c die.h types.h
	$(CC) $(CFLAGS) -c die.c

set_test.o: set_test.c set.h object.h
	$(CC) $(CFLAGS) -c set_test.c

set.o: set.c set.h types.h game.h
	$(CC) $(CFLAGS) -c set.c

################ OTHER COMMANDS

clean:
	rm -rf *.o $i(EXEC)

tar:
	tar -czf PPROG_2163_I2_P11.tar.gz *
