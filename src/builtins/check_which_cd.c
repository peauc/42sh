/*
** check_which_cd.c for check_which_cd in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Wed May 18 14:12:02 2016 marel_m
** Last update Sat Jun  4 23:45:23 2016 marel_m
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "42s.h"

int	check_cd_home(t_sh *sh)
{
  if (sh->exec->arg[1] != NULL && strcmp(sh->exec->arg[1], "~") != 0)
    return (-1);
  if (sh->env->pst_home == 1)
    {
      if (chdir(sh->env->home) == -1
	  || cd_action(sh))
	return (1);
    }
  else if (sh->exec->arg[1] == NULL)
    {
      write(2, "cd : No home directory\n", 23);
      sh->exit = 1;
    }
  else
    {
      write(2, "No $home variable set.\n", 23);
      sh->exit = 1;
    }
  return (0);
}

int	check_cd_dash(t_sh *sh)
{
  if (strcmp(sh->exec->arg[1], "-") != 0)
    return (-1);
  if (chdir(sh->env->oldpwd) == -1
      || cd_action(sh))
    return (1);
  return (0);
}

char	*path_find(char *str)
{
  char	*path;

  if ((path = getcwd(NULL, 0)) == NULL
      || (path = realloc(path, strlen(path) + strlen(str) + 3)) == NULL
      || (path = strcat(path, "/")) == NULL
      || (path = strcat(path, str)) == NULL)
    return (NULL);
  return (path);
}

int	check_cd_good(t_sh *sh)
{
  char	*path;

  if (sh->exec->arg[2] != NULL)
    return (-1);
  if (chdir(sh->exec->arg[1]) == -1)
    {
      if ((path = path_find(sh->exec->arg[1])) == NULL)
	return (1);
      if (access(path, F_OK) == 0)
	{
	  write(2, sh->exec->arg[1], strlen(sh->exec->arg[1]));
	  write(2, ": Permission denied.", 20);
	}
      else
	{
	  write(2, sh->exec->arg[1], strlen(sh->exec->arg[1]));
	  write(2, ": No such file or directory.", 28);
	}
      sh->exit = 1;
      write(2, "\n", 1);
      return (free(path), 0);
    }
  if (cd_action(sh))
    return (1);
  return (0);
}

int	check_cd_else(t_sh *sh)
{
  if (sh->exec->arg[2] != '\0')
    write(2, "Too much arguments\n", 19);
  sh->exit = 1;
  return (0);
}
