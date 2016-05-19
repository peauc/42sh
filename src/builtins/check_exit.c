/*
** check_exit.c for check_exit in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Wed May 18 15:44:57 2016 marel_m
** Last update Wed May 18 20:45:46 2016 marel_m
*/

#include <stdlib.h>
#include "42s.h"

int	my_exit(t_sh *sh)
{
  if (sh->exec->arg[1] != NULL)
    sh->exec->exit = atoi(sh->exec->arg[1]);
  else
    sh->exec->exit = 0;
  free_tab(sh->env->env);
  free(sh->env);
  return (1);
}
