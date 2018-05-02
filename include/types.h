/**
 * @brief Global typedefs
 *
 * @file types.h
 * @author NONAME
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1
#define STDSIZE 1024
#define MAX_SPRITES 1000
#define MAX_STRING 20

typedef long Id;

typedef enum {
  FALSE, TRUE
} BOOL;

typedef enum {
  ERROR, OK
} STATUS;

typedef enum {
  NORTH, EAST, SOUTH, WEST
} DIRECTION;

typedef enum
{
	OPENED, CLOSED, NO_LINK
} LinkStatus;

typedef enum enum_Command {
	NO_CMD = -1,
	UNKNOWN,
	EXIT,
	PICK_UP,
	DROP,
	ROLL,
	MOVE,
	CHECK,
	TURNON,
	TURNOFF,
	OPEN
} T_Command;

#endif
