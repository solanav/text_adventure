CC=gcc
CFLAGS=-Wall -g

game_exec: game_loop.o command.o game_reader.o graphic_engine.o screen.o space.o object.o game.o player.o
	$(CC) $(CFLAGS) -o $@ $^

die_test: die_test.o die.o
	$(CC) $(CFLAGS) -o $@ $^

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

space.o: space.c space.h types.h
	$(CC) $(CFLAGS) -c space.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

game.o: game.c game.h game_reader.h object.h player.h space.h
	$(CC) $(CFLAGS) -c game.c

die_test.o: die_test.c die.h types.h
	$(CC) $(CFLAGS) -c die_test.c

die.o: die.c die.h types.h
	$(CC) $(CFLAGS) -c die.c

clean:
	rm -rf *.o game_exec
