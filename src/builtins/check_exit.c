/*
** check_exit.c for check_exit in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Wed May 18 15:44:57 2016 marel_m
** Last update Tue May 31 14:13:51 2016 marel_m
*/

#include <stdlib.h>
#include "42s.h"

void		free_aliases(t_conf *conf)
{
  t_aliases	*tmp;

  while (conf->head)
    {
      free(conf->head->alias);
      free(conf->head->original);
      tmp = conf->head;
      conf->head = conf->head->next;
      free(tmp);
    }
  free(conf->head);
}

int		my_exit(t_sh *sh)
{
  if (sh->exec->arg[1] != NULL)
    sh->exit = atoi(sh->exec->arg[1]);
  else
    sh->exit = 0;
  free_env(sh->env);
  free_aliases(&sh->conf);
  exit(sh->exit);
}
