EXEC=game_exec die_test set_test link_test
CC=gcc
CFLAGS=-Wall -g -pedantic
m="Automatic Commit"

ALL_FILES=game.o game_reader.o graphic_engine.o screen.o command.o space.o object.o player.o set.o die.o link.o

################ EXEC CREATION

game_exec: game_loop.o $(ALL_FILES)
	$(CC) $(CFLAGS) -o $@ $^

die_test: die_test.o die.o
	$(CC) $(CFLAGS) -o $@ $^

set_test: set_test.o set.o object.o
	$(CC) $(CFLAGS) -o $@ $^

link_test: link_test.o link.o
	$(CC) $(CFLAGS) -o $@ $^

################ FILE COMPILATION

player.o: player.c types.h player.h set.h
	$(CC) $(CFLAGS) -c player.c

game_loop.o: game_loop.c graphic_engine.h
	$(CC) $(CFLAGS) -c game_loop.c

game_reader.o: game_reader.c game.h types.h
	$(CC) $(CFLAGS) -c game_reader.c

graphic_engine.o: graphic_engine.c graphic_engine.h screen.h game.h
	$(CC) $(CFLAGS) -c graphic_engine.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

space.o: space.c space.h types.h set.h
	$(CC) $(CFLAGS) -c space.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

command.o: command.c command.h types.h game.h
	$(CC) $(CFLAGS) -c command.c

game.o: game.c game.h game_reader.h object.h player.h space.h command.h die.h link.h
	$(CC) $(CFLAGS) -c game.c

die_test.o: die_test.c die.h types.h
	$(CC) $(CFLAGS) -c die_test.c

die.o: die.c die.h types.h
	$(CC) $(CFLAGS) -c die.c

set_test.o: set_test.c set.h object.h
	$(CC) $(CFLAGS) -c set_test.c

set.o: set.c set.h types.h game.h
	$(CC) $(CFLAGS) -c set.c

link_test.o: link_test.c link.h types.h game.h
	$(CC) $(CFLAGS) -c link_test.c

link.o: link.c link.h types.h
	$(CC) $(CFLAGS) -c link.c

################ ALL

all: clean game_exec die_test set_test


################ OTHER COMMANDS
val:
	valgrind --leak-check=full ./game_exec data.dat

val_die:
	valgrind --leak-check=full ./die_test

val_set:
	valgrind --leak-check=full ./set_test

clean:
	rm -rf *.o $(EXEC)

tar:
	tar -czf PPROG_2163_I3_P11.tar.gz *

git:
	git add -A
	git commit -m "$m"
