/*
** glob_dep2.c for azd in /home/debrau_c/Documents/cours/PSU/glob_easy
**
** Made by debrau_c
** Login   <debrau_c@epitech.net>
**
** Started on  Thu May 26 23:08:49 2016 debrau_c
** Last update Fri Jun  3 22:27:36 2016 debrau_c
*/

#include <stdlib.h>
#include "my_glob.h"

int	glob_strlen(char *str)
{
  int	i;

  if (str == NULL)
    return (0);
  i = 0;
  while (str && str[i])
    i++;
  return (i);
}

char	*glob_realloc(char *str, int size)
{
  char	*newer;
  int	i;

  if (str == NULL)
    {
      if ((newer = malloc(sizeof(char) * size + 1)) == NULL)
	return (NULL);
      newer[0] = '\0';
      return (newer);
    }
  if ((newer = malloc(sizeof(char) * (glob_strlen(str) + size))) == NULL)
    return (NULL);
  i = 0;
  while (str && str[i])
    {
      newer[i] = str[i];
      i++;
    }
  newer[i] = '\0';
  free(str);
  return (newer);
}

void	glob_strcat(char *dest, char *src)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (dest && dest[i])
    ++i;
  while (src && src[j])
    {
      dest[i] = src[j];
      ++i;
      ++j;
    }
  dest[i] = '\0';
}

void	glob_clean_tab(char **recup)
{
  int		i;

  i = 0;
  while (recup && recup[i])
    {
      free(recup[i]);
      i++;
    }
  free(recup);
}

char	**glob_str_tab(char *str)
{
  char		**newer;
  int		nb;
  int		i;
  int		j;

  nb = glob_count_occur(str, ' ');
  if (!(newer = malloc(sizeof(char *) * (nb + 1))))
    return (NULL);
  i = -1;
  j = 0;
  while (++i < nb)
    {
      if ((newer[i] = glob_strcdup(&str[j], ' ')) == NULL)
	return (NULL);
      j += glob_strclen(&str[j], ' ') + 1;
    }
  newer[i] = NULL;
  return (newer);
}
