/*
** bultin_or_exec.c for builtin_or_exec in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Wed May 18 17:16:18 2016 marel_m
** Last update Thu May 26 11:41:09 2016 marel_m
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "42s.h"

int	action_redir(t_sh *sh)
{
  if (sh->exec->fd != 1 && (sh->exec->type == REDIR_RIGHT
			    || sh->exec->type == DOUBLE_REDIR_RIGHT))
    {
      if (dup2(sh->exec->fd, 1) == -1)
	return (1);
    }
  else if (sh->exec->fd != 1 && sh->exec->type == REDIR_LEFT)
    {
      if (dup2(sh->exec->fd, 0) == -1)
	return (1);
    }
  return (0);
}

int	action(t_sh *sh)
{
  pid_t	pid;
  int	status;

   if ((pid = fork()) == -1)
    return (1);
  if (pid == 0)
    {
      if (action_redir(sh)
	  || execve(sh->exec->good_path, sh->exec->arg, sh->env->env) == -1)
	return (1);
    }
  else if (pid != 0 && sh->exec->fd == 1)
    {
      if (wait(&status) == -1)
	return (1);
      if (WIFSIGNALED(status))
	write(2, "Segmentation fault\n", 19);
    }
  if (sh->exec->fd != 1)
    {
      if (close(sh->exec->fd) == -1
  	  || waitpid(pid, &status, 0) == -1)
  	{
  	  return (1);
  	}
    }
  return (0);
}

int	exec(t_sh *sh)
{
  int	i;

  sh->exec->good_path = NULL;
  if ((i = check_good_path(sh)) == 1)
    return (1);
  if (action(sh))
    return (1);
  return (0);
}

int	builtin_or_exec(t_sh *sh)
{
  int	ret;

  if ((ret = check_builtin(sh)) == -3)
    {
      if ((ret = exec(sh)) != 0)
	return (ret);
    }
  else
    return (ret);
  return (0);
}