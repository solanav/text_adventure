################ COMPILER AND FLAGS

CC=gcc
CFLAGS=-Wall -g -pedantic -ansi

################ OTHER VAR

m="Automatic Commit"

################ FILES

ALL_EXEC=game_exec die_test set_test link_test

################ PATHS

SRCPATH = ./src/
HDRPATH = ./hdr/
OBJPATH = ./obj/
DOCPATH = ./doc/

################ EXEC CREATION

game_exec: game_loop.o game_reader.o graphic_engine.o screen.o command.o space.o object.o player.o set.o die.o link.o game.o inventory.o
	$(CC) $(CFLAGS) -o $@ $(OBJPATH)game_loop.o $(OBJPATH)game_reader.o $(OBJPATH)graphic_engine.o $(OBJPATH)screen.o $(OBJPATH)command.o $(OBJPATH)space.o $(OBJPATH)object.o $(OBJPATH)player.o $(OBJPATH)set.o $(OBJPATH)die.o $(OBJPATH)link.o $(OBJPATH)game.o $(OBJPATH)inventory.o

die_test: die_test.o die.o
	$(CC) $(CFLAGS) -o $@ $(OBJPATH)die_test.o $(OBJPATH)die.o

set_test: set_test.o set.o object.o
	$(CC) $(CFLAGS) -o $@ $(OBJPATH)set_test.o $(OBJPATH)set.o $(OBJPATH)object.o

link_test: link_test.o link.o
	$(CC) $(CFLAGS) -o $@ $(OBJPATH)link_test.o $(OBJPATH)link.o

################ OBJECT CREATION

player.o: $(SRCPATH)player.c $(HDRPATH)types.h $(HDRPATH)player.h $(HDRPATH)set.h $(HDRPATH)inventory.h
	$(CC) $(CFLAGS) -c $(SRCPATH)player.c -o $(OBJPATH)player.o

game_loop.o: $(SRCPATH)game_loop.c $(HDRPATH)graphic_engine.h
	$(CC) $(CFLAGS) -c $(SRCPATH)game_loop.c -o $(OBJPATH)game_loop.o

game_reader.o: $(SRCPATH)game_reader.c $(HDRPATH)game.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)game_reader.c -o $(OBJPATH)game_reader.o

graphic_engine.o: $(SRCPATH)graphic_engine.c $(HDRPATH)graphic_engine.h $(HDRPATH)screen.h $(HDRPATH)game.h
	$(CC) $(CFLAGS) -c $(SRCPATH)graphic_engine.c -o $(OBJPATH)graphic_engine.o

screen.o: $(SRCPATH)screen.c $(HDRPATH)screen.h
	$(CC) $(CFLAGS) -c $(SRCPATH)screen.c -o $(OBJPATH)screen.o

space.o: $(SRCPATH)space.c $(HDRPATH)space.h $(HDRPATH)types.h $(HDRPATH)set.h
	$(CC) $(CFLAGS) -c $(SRCPATH)space.c -o $(OBJPATH)space.o

object.o: $(SRCPATH)object.c $(HDRPATH)object.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)object.c -o $(OBJPATH)object.o

command.o: $(SRCPATH)command.c $(HDRPATH)command.h $(HDRPATH)types.h $(HDRPATH)game.h
	$(CC) $(CFLAGS) -c $(SRCPATH)command.c -o $(OBJPATH)command.o

game.o: $(SRCPATH)game.c $(HDRPATH)game.h $(HDRPATH)game_reader.h $(HDRPATH)object.h $(HDRPATH)player.h $(HDRPATH)space.h $(HDRPATH)command.h $(HDRPATH)die.h $(HDRPATH)link.h $(HDRPATH)inventory.h
	$(CC) $(CFLAGS) -c $(SRCPATH)game.c -o $(OBJPATH)game.o

die.o: $(SRCPATH)die.c $(HDRPATH)die.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)die.c -o $(OBJPATH)die.o

set.o: $(SRCPATH)set.c $(HDRPATH)set.h $(HDRPATH)types.h $(HDRPATH)game.h
	$(CC) $(CFLAGS) -c $(SRCPATH)set.c -o $(OBJPATH)set.o

link.o: $(SRCPATH)link.c $(HDRPATH)link.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)link.c -o $(OBJPATH)link.o

inventory.o: $(SRCPATH)inventory.c $(HDRPATH)set.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)inventory.c -o $(OBJPATH)inventory.o

################ OBJECTS FOR TESTS

die_test.o: $(SRCPATH)die_test.c $(HDRPATH)die.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)die_test.c -o $(OBJPATH)die_test.o

link_test.o: $(SRCPATH)link_test.c $(HDRPATH)link.h $(HDRPATH)types.h $(HDRPATH)game.h
	$(CC) $(CFLAGS) -c $(SRCPATH)link_test.c -o $(OBJPATH)link_test.o

set_test.o: $(SRCPATH)set_test.c $(HDRPATH)set.h $(HDRPATH)object.h
	$(CC) $(CFLAGS) -c $(SRCPATH)set_test.c -o $(OBJPATH)set_test.o

################ ALL

all: clean $(ALL_EXEC)

################ OTHER COMMANDS

val:
	valgrind --leak-check=full ./game_exec data.dat

val_die:
	valgrind --leak-check=full ./die_test

val_set:
	valgrind --leak-check=full ./set_test

clean:
	rm -rf *.o $(ALL_EXEC)

tar:
	tar -czf PPROG_2163_I3_P11.tar.gz *

git:
	git add -A
	git commit -m "$m"
