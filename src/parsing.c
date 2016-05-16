/*
** parsing.c for parsing in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Wed May 11 16:02:55 2016 marel_m
** Last update Mon May 16 19:07:11 2016 marel_m
*/

#include <stdio.h>
#include "42s.h"

int	check_prior(char *str)
{
  int	i;
  int	prior;

  i = 0;
  if (str == NULL)
    return (0);
  prior = 0;
  while (str[i] != '\0' && str)
    {
      if (str[i] == '|' && prior < 1)
	prior = 1;
      else if (str[i] == '>' || str[i] == '<')
	prior = 2;
      i++;
    }
  return (prior);
}

int		pars_tree(t_list_sh *elem, char *str)
{
  int		prior;

  prior = check_prior(str);
  if (prior == 0)
    {
      insert_node(&elem->node, str, NULL, 3);
      str = NULL;
    }
  else if (prior == 1)
    str = pars_pipe(elem, str);
  if (check_prior(str) != 0)
    pars_tree(elem, str);
  return (0);
}

int		stock_elem(t_sh *sh, char *str, int st, int end)
{
  t_list_sh	*elem;

  if ((elem = add_list_after(sh)) == NULL
      || (elem->arg = my_strdup_bt(str, st, end)) == NULL)
    return (1);
  elem->node = NULL;
  if (pars_tree(elem, str))
    return (1);
  print_tree(elem->node);
  return (0);
}

int	parsing(t_sh *sh, char *str)
{
  int	i;
  int	j;

  if (str == NULL)
    return (0);
  if (create_list(sh))
    return (-1);
  i = 0;
  j = 0;
  while (str[i] != '\0' && str)
    {
      if (str[i] == ';')
	{
	  stock_elem(sh, str, j, i);
	  i++;
	  j = i;
	  sh->root->prev->type = SEMICOLON;
	}
      else if (str[i] == '&' && str[i + 1] == '&')
	{
	  stock_elem(sh, str, j, i);
	  i += 2;
	  j = i;
	  sh->root->prev->type = DOUBLE_AND;
	}
      else if (str[i] == '|' && str[i + 1] == '|')
	{
	  stock_elem(sh, str, j, i);
	  i += 2;
	  j = i;
	  sh->root->prev->type = DOUBLE_PIPE;
	}
      else
	i++;
    }
  stock_elem(sh, str, j, i);
  return (0);
}
