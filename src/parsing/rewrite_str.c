/*
** rewrite_str.c for rewrite_str in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Tue May 31 23:47:51 2016 marel_m
** Last update Sun Jun  5 01:59:15 2016 Mathieu Sauvau
*/

#include <string.h>
#include <stdlib.h>
#include "42s.h"

int	init_rewrite(char *str, int *i)
{
  int	j;

  j = 0;
  while (str[j] != '\0' && str && str[j] != ' ' && str[j] != '|'
	 && str[j] != '>')
    j++;
  if (str[j] == '\0' && str)
    return (-1);
  j++;
  *i = j;
  while (str && str[j] != '\0' && str[j] != '|' && str[j] != '>')
    j++;
  return (j);
}

int	do_some(char *str, char **tmp, char **tmp2, char **tmp3)
{
  int	j;

  j = 0;
  while (str && str[j] != '\0' && str[j] != ' ')
    j++;
  if ((*tmp2 = strndup(str, j)) == NULL)
    return (0);
  if (*tmp3 == NULL)
    {
      if ((*tmp = realloc(*tmp, strlen(*tmp) + strlen(*tmp2) + 1)) == NULL)
	return (0);
    }
  else if ((*tmp = realloc(*tmp, strlen(*tmp) + strlen(*tmp2) + strlen(*tmp3)
			  + 1)) == NULL)
    return (0);
  return (1);
}


char	*rewrite_str(char *str)
{
  char	*tmp;
  char	*tmp2;
  char	*tmp3;
  int	i;
  int	j;

  if ((j = init_rewrite(str, &i)) == -1)
    return (str);
  if ((tmp = my_strdup_bt(str, i, j)) == NULL)
    return (NULL);
  tmp3 = NULL;
  if (str[j] != '\0')
    if ((tmp3 = my_strdup_e(str, j)) == NULL)
      return (NULL);
  if (!do_some(str, &tmp, &tmp2, &tmp3))
      return (NULL);
  tmp = strcat(tmp, tmp2);
  if (tmp3)
    {
      tmp = strcat(tmp, tmp3);
      my_free((void **)&tmp3);
    }
  printf("tmp %s\n", tmp);
  my_free((void **)&tmp2);
  return (tmp);
}
