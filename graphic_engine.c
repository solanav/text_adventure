#include <stdlib.h>
#include <stdio.h>

#include "screen.h"
#include "graphic_engine.h"
#include "set.h"

/*This is the definition of graphic engine for the object functions*/
struct _Graphic_engine
{
  Area *map,
  *descript,
  *banner,
  *help,
  *feedback;
};

/*Creates the engine and returns it with default values*/
Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  /* Check if already created */
  if (ge)
    return ge;

  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));

/*Default values*/
  ge->map      = screen_area_init( 1, 1, 48, 13);
  ge->descript = screen_area_init(50, 1, 29, 13);
  ge->banner   = screen_area_init(28,15, 23,  1);
  ge->help     = screen_area_init( 1,16, 78,  2);
  ge->feedback = screen_area_init( 1,19, 78,  3);

  return ge;
}


void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  int i, j;
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space* space_act = NULL;
  char obj[5]="\0";
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];


  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);

	/* TODO : Aqui hay que hacer un for que dibuje mas de un objeto, esto es un test para que compile*/
  for (i=1, j=0; i<5; i++)
  {
    if(game_get_object_location(game, i) == id_back)
    {
      obj[j]='o';
      obj[j+1]= 48+i;
      j=j+2;
    }
    else
    {
      obj[j]=' ';
      obj[j+1]=' ';
    }
  }
    if (id_back != NO_ID)
    {
      sprintf(str, "  |        %2d|",(int) id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %s  |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    for (i=1, j=0; i<5; i++)
    {
      if(game_get_object_location(game, i) == id_act)
      {
        obj[j]='o';
        obj[j+1]= 48+i;
        j=j+2;
      }
      else
      {
        obj[j]=' ';
        obj[j+1]=' ';
      }
    }
    /*if (game_get_object_location(game, 1) == id_act)
      obj='*';
    else
      obj=' ';*/

    if (id_act != NO_ID)
    {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | 8D      %2d|",(int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %s  |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    for (i=1, j=0; i<5; i++)
    {
      if(game_get_object_location(game, i) == id_next)
      {
        obj[j]='o';
        obj[j+1]= 48+i;
        j=j+2;
      }
      else
      {
        obj[j]=' ';
        obj[j+1]=' ';
      }
    }

    if (id_next != NO_ID)
    {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|",(int) id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %s  |",obj);
      screen_area_puts(ge->map, str);
    }
  }

  /* Paint the in the description area */
  screen_area_clear(ge->descript);
  for(i=1; i<5; i++)
  {
    if ((obj_loc = game_get_object_location(game, i)) != NO_ID)
    {
      sprintf(str, "  Object o%d location:%d", i, (int)obj_loc);
      screen_area_puts(ge->descript, str);
    }
  }

  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     Following or f, Previous or p, Pickup or u, Drop or d, or Exit or e, Roll or r");
  screen_area_puts(ge->help, str);

  /* Paint the in the feedback area */
  last_cmd = game_get_last_command_text(game);
  sprintf(str, " %s", cmd_to_str[last_cmd-NO_CMD]);
  screen_area_puts(ge->feedback, str);
  if(last_cmd == ROLL)
  {
    sprintf(str, "   You rolled: %d", game_get_last_roll(game));
    screen_area_puts(ge->feedback, str);
  }


  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
