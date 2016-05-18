/*
** check_builtins.c for check_builtins in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Wed May 18 16:28:38 2016 marel_m
** Last update Wed May 18 18:31:52 2016 marel_m
*/

#include <string.h>
#include <stdlib.h>
#include "fptrtab.h"
#include "42s.h"

t_blt	*init_tab_builtins()
{
  t_blt	*tab;

  if ((tab = malloc(sizeof(t_blt) * MAX_BLT)) == NULL)
    return (NULL);
  tab[SETENV].blt = "setenv";
  tab[SETENV].ft_blt = &my_setenv;
  tab[UNSETENV].blt = "unsetenv";
  tab[UNSETENV].ft_blt = &my_unsetenv;
  tab[ENV].blt = "env";
  tab[ENV].ft_blt = &my_env;
  tab[CD].blt = "cd";
  tab[CD].ft_blt = &my_cd;
  tab[EXIT].blt = "exit";
  tab[EXIT].ft_blt = &my_exit;
  return (tab);
}

int	check_builtin(t_sh *sh)
{
  t_blt	*fptrtab;
  int	i;
  int	ret;

  i = -1;
  if ((fptrtab = init_tab_builtins()) == NULL)
    return (1);
  while (++i < MAX_BLT)
    if (strncmp(sh->exec->arg[0], fptrtab[i].blt, strlen(fptrtab[i].blt)) == 0)
      {
	ret = fptrtab[i].ft_blt(sh);
	return (free(fptrtab), ret);
      }
  free(fptrtab);
  return (-3);
}
