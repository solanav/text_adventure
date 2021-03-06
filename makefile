################ COMPILER AND FLAGS

CC=gcc
CFLAGS=-Wall -g -pedantic -ansi

################ OTHER VAR

m="Automatic Commit"

################ FILES

ALL_EXEC=game_exec player_test space_test die_test set_test link_test object_test command_test inventory_test
ALL_TEST=die_test set_test link_test object_test command_test inventory_test player_test space_test sprite_test

################ PATHS

SRCPATH = ./src/
HDRPATH = ./include/
OBJPATH = ./build/
TESTPATH  = ./test/
TESTOBJPATH = ./build/
DOCPATH = ./doc/
BINPATH = ./bin/

################ EXEC CREATION

game_exec: game_loop.o game_reader.o graphic_engine.o screen.o command.o space.o object.o player.o set.o die.o link.o game.o inventory.o sprite_loader.o sprite.o game_rules.o dialogue.o
	$(CC) $(CFLAGS) -o $(BINPATH)game_exec $(OBJPATH)game_loop.o $(OBJPATH)game_reader.o $(OBJPATH)graphic_engine.o $(OBJPATH)screen.o $(OBJPATH)command.o $(OBJPATH)space.o $(OBJPATH)object.o $(OBJPATH)player.o $(OBJPATH)set.o $(OBJPATH)die.o $(OBJPATH)link.o $(OBJPATH)game.o $(OBJPATH)inventory.o $(OBJPATH)sprite_loader.o $(OBJPATH)sprite.o $(OBJPATH)game_rules.o $(OBJPATH)dialogue.o

################ TESTS

space_test: space.o set.o space_test.o
	$(CC) $(CFLAGS) -o $(BINPATH)space_test $(OBJPATH)space.o $(OBJPATH)set.o $(TESTOBJPATH)space_test.o

object_test: object.o object_test.o
	$(CC) $(CFLAGS) -o $(BINPATH)object_test $(OBJPATH)object.o $(TESTOBJPATH)object_test.o

link_test: link.o link_test.o
	$(CC) $(CFLAGS) -o $(BINPATH)link_test $(OBJPATH)link.o $(TESTOBJPATH)link_test.o

die_test: die_test.o die.o
	$(CC) $(CFLAGS) -o $(BINPATH)die_test $(OBJPATH)die.o $(TESTOBJPATH)die_test.o

command_test: command_test.o command.o
	$(CC) $(CFLAGS) -o $(BINPATH)command_test $(OBJPATH)command.o $(TESTOBJPATH)command_test.o

inventory_test: inventory_test.o inventory.o set.o
	$(CC) $(CFLAGS) -o $(BINPATH)inventory_test $(OBJPATH)inventory.o $(OBJPATH)set.o $(TESTOBJPATH)inventory_test.o

player_test: player_test.o player.o inventory.o set.o
	$(CC) $(CFLAGS) -o $(BINPATH)player_test $(OBJPATH)player.o $(OBJPATH)inventory.o $(OBJPATH)set.o $(TESTOBJPATH)player_test.o

set_test: set_test.o set.o
	$(CC) $(CFLAGS) -o $(BINPATH)set_test $(OBJPATH)set.o $(TESTOBJPATH)set_test.o

sprite_test: sprite.o sprite_test.o
	$(CC) $(CFLAGS) -o $(BINPATH)sprite_test $(OBJPATH)sprite.o $(TESTOBJPATH)sprite_test.o

################ OBJECT CREATION

player.o: $(SRCPATH)player.c $(HDRPATH)types.h $(HDRPATH)player.h $(HDRPATH)set.h $(HDRPATH)inventory.h
	$(CC) $(CFLAGS) -c $(SRCPATH)player.c -o $(OBJPATH)player.o

game_loop.o: $(SRCPATH)game_loop.c $(HDRPATH)graphic_engine.h
	$(CC) $(CFLAGS) -c $(SRCPATH)game_loop.c -o $(OBJPATH)game_loop.o

game_reader.o: $(SRCPATH)game_reader.c $(HDRPATH)game.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)game_reader.c -o $(OBJPATH)game_reader.o

graphic_engine.o: $(SRCPATH)graphic_engine.c $(HDRPATH)graphic_engine.h $(HDRPATH)screen.h $(HDRPATH)game.h $(HDRPATH)dialogue.h
	$(CC) $(CFLAGS) -c $(SRCPATH)graphic_engine.c -o $(OBJPATH)graphic_engine.o

screen.o: $(SRCPATH)screen.c $(HDRPATH)screen.h
	$(CC) $(CFLAGS) -c $(SRCPATH)screen.c -o $(OBJPATH)screen.o

space.o: $(SRCPATH)space.c $(HDRPATH)space.h $(HDRPATH)types.h $(HDRPATH)set.h
	$(CC) $(CFLAGS) -c $(SRCPATH)space.c -o $(OBJPATH)space.o

object.o: $(SRCPATH)object.c $(HDRPATH)object.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)object.c -o $(OBJPATH)object.o

command.o: $(SRCPATH)command.c $(HDRPATH)command.h $(HDRPATH)types.h $(HDRPATH)game.h
	$(CC) $(CFLAGS) -c $(SRCPATH)command.c -o $(OBJPATH)command.o

game.o: $(SRCPATH)game.c $(HDRPATH)game.h $(HDRPATH)game_reader.h $(HDRPATH)object.h $(HDRPATH)player.h $(HDRPATH)space.h $(HDRPATH)command.h $(HDRPATH)die.h $(HDRPATH)link.h $(HDRPATH)inventory.h $(HDRPATH)game_rules.h
	$(CC) $(CFLAGS) -c $(SRCPATH)game.c -o $(OBJPATH)game.o

die.o: $(SRCPATH)die.c $(HDRPATH)die.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)die.c -o $(OBJPATH)die.o

set.o: $(SRCPATH)set.c $(HDRPATH)set.h $(HDRPATH)types.h $(HDRPATH)game.h
	$(CC) $(CFLAGS) -c $(SRCPATH)set.c -o $(OBJPATH)set.o

link.o: $(SRCPATH)link.c $(HDRPATH)link.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)link.c -o $(OBJPATH)link.o

dialogue.o: $(SRCPATH)dialogue.c  $(HDRPATH)die.h $(HDRPATH)dialogue.h $(HDRPATH)game.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)dialogue.c -o $(OBJPATH)dialogue.o

inventory.o: $(SRCPATH)inventory.c $(HDRPATH)set.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)inventory.c -o $(OBJPATH)inventory.o

sprite_loader.o: $(SRCPATH)sprite_loader.c $(HDRPATH)game.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)sprite_loader.c -o $(OBJPATH)sprite_loader.o

sprite.o: $(SRCPATH)sprite.c $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)sprite.c -o $(OBJPATH)sprite.o

game_rules.o: $(SRCPATH)game_rules.c $(HDRPATH)game_rules.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)game_rules.c -o $(OBJPATH)game_rules.o

################ OBJECTS FOR TESTS

space_test.o: $(TESTPATH)space_test.c $(HDRPATH)space_test.h $(HDRPATH)space.h $(HDRPATH)test.h
	$(CC) $(CFLAGS) -c $(TESTPATH)space_test.c -o $(TESTOBJPATH)space_test.o

object_test.o: $(TESTPATH)object_test.c $(HDRPATH)object_test.h $(HDRPATH)object.h $(HDRPATH)test.h
	$(CC) $(CFLAGS) -c $(TESTPATH)object_test.c -o $(TESTOBJPATH)object_test.o

die_test.o: $(TESTPATH)die_test.c $(HDRPATH)die.h $(HDRPATH)test.h $(HDRPATH)die_test.h
	$(CC) $(CFLAGS) -c $(TESTPATH)die_test.c -o $(TESTOBJPATH)die_test.o

link_test.o: $(TESTPATH)link_test.c $(HDRPATH)link.h $(HDRPATH)test.h $(HDRPATH)link_test.h
	$(CC) $(CFLAGS) -c $(TESTPATH)link_test.c -o $(TESTOBJPATH)link_test.o

command_test.o: $(TESTPATH)command_test.c $(HDRPATH)command.h $(HDRPATH)test.h $(HDRPATH)command_test.h
	$(CC) $(CFLAGS) -c $(TESTPATH)command_test.c -o $(TESTOBJPATH)command_test.o

inventory_test.o: $(TESTPATH)inventory_test.c $(HDRPATH)inventory.h $(HDRPATH)test.h $(HDRPATH)inventory_test.h $(HDRPATH)set.h
	$(CC) $(CFLAGS) -c $(TESTPATH)inventory_test.c -o $(TESTOBJPATH)inventory_test.o

player_test.o: $(TESTPATH)player_test.c $(HDRPATH)player.h $(HDRPATH)player_test.h $(HDRPATH)test.h
	$(CC) $(CFLAGS) -c $(TESTPATH)player_test.c -o $(TESTOBJPATH)player_test.o

set_test.o: $(TESTPATH)set_test.c $(HDRPATH)set.h $(HDRPATH)test.h $(HDRPATH)set_test.h
	$(CC) $(CFLAGS) -c $(TESTPATH)set_test.c -o $(TESTOBJPATH)set_test.o

sprite_test.o: $(TESTPATH)sprite_test.c $(HDRPATH)sprite.h $(HDRPATH)test.h $(HDRPATH)sprite_test.h
	$(CC) $(CFLAGS) -c $(TESTPATH)sprite_test.c -o $(TESTOBJPATH)sprite_test.o

################ ALL

all: clean $(ALL_EXEC)

all_test: clean $(ALL_TEST)

################ OTHER COMMANDS

run_test: all_test
	$(BINPATH)space_test ; $(BINPATH)object_test ; $(BINPATH)die_test ; $(BINPATH)link_test ; $(BINPATH)command_test ; $(BINPATH)inventory_test ; $(BINPATH)player_test ; $(BINPATH)set_test ; $(BINPATH)sprite_test

val:
	valgrind -v --leak-check=full $(BINPATH)game_exec data/data.dat

test_game:
	$(BINPATH)game_exec data/data.dat < ./log/partida_prueba.oca

doxygen:
	doxygen -g doxyconfig && doxygen doxyconfig

clean:
	rm -rf $(ALL_EXEC) $(ALL_TEST) $(TESTOBJPATH)*

tar:
	tar -czf PPROG_2163_I3_G3.tar.gz *

git:
	git add -A
	git commit -m "$m"
