/*
** my_put_in_word_tab.c for my_put_in_word_tab in /home/marel_m/Rendu/Systeme_Unix/PSU_2015_minishell1/lib/my
**
** Made by maud marel
** Login   <marel_m@epitech.net>
**
** Started on  Wed Jan  6 14:52:17 2016 maud marel
** Last update Fri Jun  3 22:46:53 2016 marel_m
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"

int	check_nb(char *str, char sign)
{
  int	i;
  int	nb;

  nb = 1;
  i = 0;
  while (str && str[i] != '\0')
    {
      if (str[i] == sign)
	nb++;
      while (str[i] != '\0' && str && str[i] == ' ')
      	i++;
      if (str[i] != '\0' && str)
	i++;
    }
  return (nb);
}

static int	check_first(t_tab *tab, char *str, char sign)
{
  int		i;

  tab->nb = check_nb(str, sign);
  tab->size = strlen(str);
  i = 0;
  if (tab->nb < 1)
    return (-1);
  while (str && str[i] == sign)
    i++;
  return (i);
}

char	**my_str_to_word_tab(char *str, char sign)
{
  int	i;
  int	j;
  int	l;
  char	**tab;
  t_tab	tb;

  if ((i = check_first(&tb, str, sign)) == -1
      || (tab = malloc(sizeof(char*) * (tb.nb + 2))) == NULL)
    return (NULL);
  l = 0;
  while (str[i] != '\0' && str[i])
    {
      j = 0;
      if ((tab[l] = malloc(sizeof(char) * (tb.size + 2))) == NULL)
	return (NULL);
      if (str[i] == '"')
      	{
      	  i++;
      	  while (str && str[i] != '\0' && str[i] != '"')
      	    tab[l][j++] = str[i++];
      	}
      else
	while (str[i] != sign && str[i] != '\0' && str[i])
	  tab[l][j++] = str[i++];
      if (str[i])
	i++;
      while (str[i] == sign)
	i++;
      tab[l++][j] = '\0';
    }
  tab[l] = NULL;
  return (tab);
}