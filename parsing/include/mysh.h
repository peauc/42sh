/*
** mysh.h for mysh in /home/marel_m/Rendu/Semestre_2/PSU/42sh
**
** Made by marel_m
** Login   <marel_m@epitech.net>
**
** Started on  Wed Apr 27 18:01:43 2016 marel_m
** Last update Sat Apr 30 22:42:41 2016 marel_m
*/

#ifndef MYSH_H_
# define MYSH_H_

typedef struct	s_node
{
  int		power;
  struct s_node	*left;
  struct s_node	*right;
}		t_node;

typedef struct	s_env
{
  char		**env;
  char		*pwd;
  char		*oldpwd;
  char		*home;
}		t_env;

typedef struct	s_sh
{
  t_node	*tree;
  t_env		*env;
}		t_sh;

char		*get_next_line(int);

#endif /* MYSH_H_ */
