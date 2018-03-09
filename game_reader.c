#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_reader.h"

STATUS game_load_spaces(Game* game, char* filename)
{
  /*
   * Loads game spaces from specified file.
   *
   * game: the main game structure
   * filename: .dat file you want to use
   *
   * returns: ERROR or OK
   */

  FILE* file = NULL;

  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";

  char* toks = NULL;

  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;

  Space* space = NULL;
  STATUS status = OK;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      /* Read ID */
      toks = strtok(line + 3, "|");
      id = atol(toks);

      /* Read NAME */
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      /* Read North/East/South/West */
      toks = strtok(NULL, "|");
      north = atol(toks);

      toks = strtok(NULL, "|");
      east = atol(toks);

      toks = strtok(NULL, "|");
      south = atol(toks);

      toks = strtok(NULL, "|");
      west = atol(toks);

      /* Debug info */
      #ifdef DEBUG
        printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
      #endif

      /* Create space (only assigns id for now) */
      space = space_create(id);

      /* Save what we just read */
      if (space != NULL)
      {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);

        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}
