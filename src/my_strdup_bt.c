/*
** my_strdup.c for my_strdup in /home/marel_m/Rendu/Semestre_2/Systeme_Unix/PSU_2015_tetris/lib/my
**
** Made by maud marel
** Login   <marel_m@epitech.net>
**
** Started on  Tue Mar  8 09:15:03 2016 maud marel
** Last update Tue May 17 10:24:40 2016 marel_m
*/

#include <stdlib.h>
#include "my.h"

char	*my_strdup_bt(char *str, int st, int end)
{
  char	*new;
  int	j;

  j = 0;
  if ((new = malloc(sizeof(char) * (end - st + 2))) == NULL)
    return (NULL);
  while (st < end && str[st] != '\0' && str)
    {
      printf("%c", str[st]);
      new[j] = str[st];
      st++;
      j++;
    }
  printf("\n");
  new[j] = '\0';
  return (new);
}
