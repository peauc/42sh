/*
** 42rc_alias_checker.c for check alias in /home/peau_c/rendu/PSU_2015_42sh
**
** Made by Poc
** Login   <peau_c@epitech.net>
**
** Started on  Wed May 18 12:37:44 2016 Poc
** Last update Sun Jun  5 15:06:08 2016 bougon_p
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "42s.h"

void	concat_new(char **str, char *concat)
{
  if (!(*str =
	realloc(*str,
		strlen(*str) +
		strlen(concat) + 2)))
      exit(1);
  strcat(*str, concat);
  strcat(*str, " ");
}

int	jump_next_word(char *str, int i)
{
  if (i == 0)
    return (0);
  while (str && str[i] && str[i] != ' ')
    {
      i++;
    }
  if (str[i] && str[i + 1])
    return (i + 1);
  else
    return (-1);
}

bool	match_aliases(t_aliases *alias, char **str, int i, char **new)
{
  while (alias)
    {
      if (aliascmp(alias->original, &(*str)[i]) == 0)
	{
	  concat_new(new, alias->alias);
	  return (true);
	}
      alias = alias->next;
    }
  return (false);
}

char	*next_word(char *str)
{
  char	*next;
  int	i;

  if (!(next = malloc(strlen(str) + 1)))
    exit(1);
  bzero(next, strlen(str));
  i = 0;
  while (str && str[i] && str[i] != ' ')
    {
      next[i] = str[i];
      i++;
    }
  next[i] = 0;
  return (next);
}

int		check_alias(t_aliases *head, char **str)
{
  int		i;
  int		n;
  char		*new;
  char		*next;
  t_aliases	*alias;

  if (!(new = malloc(1)))
    exit(1);
  new[0] = 0, n = 0, i = n;
  while ((i = jump_next_word(*str, i)) != -1)
    {
      alias = head;
      if (!match_aliases(alias, str, i, &new))
	{
	  next = next_word(&(*str)[i]);
	  concat_new(&new, next);
	  free(next);
	}
     i++;
    }
  if (new[strlen(new) - 1] == ' ')
    new[strlen(new) - 1] = 0;
  if (*str)
    return (free(*str), *str = new, 0);
  return (0);
}
