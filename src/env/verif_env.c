/*
** verif_enc.c for verif_env in /home/marel_m/Rendu/Semestre_2/PSU/PSU_2015_42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Mon May 16 22:50:52 2016 marel_m
** Last update Mon May 16 22:53:29 2016 marel_m
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "fptrtab.h"
#include "42s.h"

int	check_if_present_in_env(t_sh *sh)
{
  char  *pwd;

  if ((sh->env->pst_path == 0 &&
       (sh->env->path
	= my_str_to_word_tab("~/bin:/bin:/sbin:/usr/bin:/usr/sbin", ':'))
       == NULL)
      || (sh->env->pst_pwd == 0 && ((pwd = getcwd(NULL, 0)) == NULL
				|| (sh->env->pwd = strdup(pwd)) == NULL))
      || (sh->env->pst_oldpwd == 0 &&
	  (sh->env->oldpwd = strdup(sh->env->pwd)) == NULL))
    return (-1);
  if (sh->env->pst_home == 0)
    sh->env->home = NULL;
  return (0);
}

t_env_elem	*init_tab_env_elem()
{
  t_env_elem    *tab;

  if ((tab = malloc(sizeof(t_env_elem) * MAX_ELEM_ENV)) == NULL)
    return (NULL);
  tab[PATH].env_elem = "PATH=";
  tab[PATH].ft_env_elem = &check_path;
  tab[HOME].env_elem = "HOME=";
  tab[HOME].ft_env_elem = &check_home;
  tab[PWD].env_elem = "PWD=";
  tab[PWD].ft_env_elem = &check_pwd;
  tab[OLDPWD].env_elem = "OLDPWD=";
  tab[OLDPWD].ft_env_elem = &check_oldpwd;
  return (tab);
}

int		check_if_present_env(t_sh *sh)
{
  int		i;
  int		l;
  t_env_elem	*fptrtab;

  if ((fptrtab = init_tab_env_elem()) == NULL)
    return (1);
  l = 0;
  while (sh->env->env[l] != NULL && sh->env->env)
    {
      i = -1;
      while (++i < MAX_ELEM_ENV)
	if (strncmp(sh->env->env[l], fptrtab[i].env_elem,
		    strlen(fptrtab[i].env_elem)) == 0)
	  if (fptrtab[i].ft_env_elem(sh))
	    return (1);
      l++;
    }
  free(fptrtab);
  if (check_if_present_in_env(sh))
    return (1);
  return (0);
}
