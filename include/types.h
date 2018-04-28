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

typedef long Id;

typedef enum {
  FALSE, TRUE
} BOOL;

typedef enum {
  ERROR, OK
} STATUS;

typedef enum {
  N, S, E, W
} DIRECTION;

typedef enum
{
	OPEN, CLOSED, NO_LINK
} LinkStatus;

typedef enum
{
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  PICK_UP,
  DROP,
  ROLL,
  MOVE,
  CHECK,
  SAVE,
  LOAD
} T_Command;

#endif
