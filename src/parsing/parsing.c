/*
** parsing.c for parsing in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Wed May 11 16:02:55 2016 marel_m
** Last update Tue May 31 23:45:04 2016 marel_m
*/

#include <stdio.h>
#include <stdlib.h>
#include "42s.h"

int	check_prior(char *str)
{
  int	i;
  int	prior;

  i = 0;
  prior = 0;
  while (str && str[i] != '\0')
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

  if (str == NULL)
    return (1);
  prior = check_prior(str);
  elem->nb++;
  if (prior == 0)
    return (0);
  else if (prior == 1)
    {
      if ((str = pars_pipe(elem, str)) == NULL)
	return (1);
    }
  else if (prior == 2)
    {
      if ((str = pars_redir(elem, str)) == NULL)
	return (1);
    }
  if (check_prior(str) != 0)
    if (pars_tree(elem, str))
      return (1);
  free(str);
  return (0);
}

int		stock_elem(t_sh *sh, char *str, int st, int end)
{
  t_list_sh	*elem;

  if ((elem = add_list_after(sh)) == NULL
      || (elem->arg = my_strdup_bt(str, st, end)) == NULL)
    return (1);
  elem->node = NULL;
  elem->nb = 1;
  if (check_prior(elem->arg) == 0)
    {
      if (insert_node(&elem->node, elem->arg, elem->arg, NO_ONE) == NULL)
	return (1);
      return (0);
    }
  if (pars_tree(elem, elem->arg))
    return (1);
  return (0);
}

int	which_separator(t_sh *sh, char *str, int *i, int *j)
{
  if (str[(*i)] == ';')
    {
      if (stock_elem(sh, str, *j, *i))
	return (1);
      sh->root->prev->type = SEMICOLON;
      return ((*i)++, *j = *i, 0);
    }
  else if (str[(*i)] == '&' && str[(*i) + 1] == '&')
    {
      if (stock_elem(sh, str, *j, *i))
	return (1);
      sh->root->prev->type = DOUBLE_AND;
      return (*i += 2, *j = *i, 0);
    }
  else if (str[(*i)] == '|' && str[(*i) + 1] == '|')
    {
      if (stock_elem(sh, str, *j, *i))
	return (1);
      sh->root->prev->type = DOUBLE_PIPE;
      return (*i += 2, *j = *i, 0);
    }
  return (-1);
}

int	parsing(t_sh *sh, char *str)
{
  int	i;
  int	j;
  int	ret;

  if (str == NULL)
    return (1);
  if (create_list(sh))
    return (1);
  i = 0;
  j = 0;
  while (str && str[i] != '\0')
    {
      if ((ret = which_separator(sh, str, &i, &j)) == -1)
	i++;
      else if (ret == 1)
	return (1);
    }
  if (stock_elem(sh, str, j, i))
    return (1);
  sh->root->prev->type = 0;
  free(str);
  return (0);
}
