/*
** loop_ncurses.c for loop_ncurses in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Fri Jun  3 19:55:04 2016 marel_m
** Last update Fri Jun  3 20:01:30 2016 marel_m
*/

#include <sys/ioctl.h>
#include <stropts.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "42s.h"

void            change_read_mode(int i, int time, int nb_char)
{
  static struct termios old;
  static struct termios new;

  if (i == 0)
    {
      ioctl(0, TCGETS, &old);
      ioctl(0, TCGETS, &new);
      new.c_lflag &= ~(ICANON);
      new.c_lflag &= ~(ECHO);
      new.c_cc[VMIN] = nb_char;
      new.c_cc[VTIME] = time;
      ioctl(0, TCSETS, &new);
    }
  if (i == 1)
    ioctl(0, TCSETS, &old);
}

int		cpy_to_pos(char **str, char *buff, int *curs_pos, char *prompt)
{
  char		*start;
  char		*end;

  if ((start = strdup(*str)) == NULL)
    return (1);
  start[*curs_pos] = 0;
  if ((end = strdup(*str + *curs_pos)) == NULL ||
      (*str = realloc(*str, strlen(*str) + strlen(buff) + 1)) == NULL)
    return (1);
  strcpy(*str, start);
  strcat(*str, buff);
  strcat(*str, end);
  *curs_pos += 1;
  cursor_forward(1);
  cursor_save();
  fflush(stdout);
  write(1, "\r", 1);
  write(1, prompt, strlen(prompt));
  write(1, *str, strlen(*str));
  cursor_restore();
  fflush(stdout);
  free(end);
  return (0);
}

int		do_action(t_key_act actions[18], char **str,
			  t_sh *sh, char *prompt)
{
  static int	cur_pos;
  static int	index_history;
  char		buff[11];
  int		i;
  t_head	*history;

  history = sh->history;
  i = -1;
  memset(buff, 0, 11);
  read(0, buff, 10);
  history->prompt = prompt;

  if (sh->reset_curs)
    {
      cur_pos = 0;
      sh->reset_curs = false;
    }
  /* int j = -1; */
  /* while (++j < 10) */
  /*   printf("\n%d %c\n", buff[j], buff[j]); */

  while (++i < 18)
    {
      if (strcmp(buff, actions[i].key) == 0)
	{
	  actions[i].fct(str, &cur_pos, history, &index_history);
	  return (1);
	}
    }
  if (check_exit(buff))
    do_shortcut_exit(sh);
  i = -1;
  while (buff[++i])
    {
      if (buff[i] == '\n')
	{
	  printf("\n");
	  cur_pos = 0;
	  return (3);
	}
    }
  cpy_to_pos(str, buff, &cur_pos, prompt);
  return (0);
}