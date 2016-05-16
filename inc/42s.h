/*
** 42s.h for 42.sh in /home/peau_c/rendu/PSU/PSU_2015_42sh
**
** Made by Poc
** Login   <peau_c@epitech.net>
**
** Started on  Mon Apr 18 00:15:01 2016 Poc
** Last update Mon May 16 18:53:33 2016 marel_m
*/

#ifndef _42s_H_
# define _42s_H_

typedef enum		e_dir
  {
    LEFT,
    RIGHT,
    RIGHT_LEFT
  }			t_dir;

typedef enum		e_type
  {
    SEMICOLON,
    DOUBLE_PIPE,
    DOUBLE_AND,
    PIPE,
    REDIR_RIGHT,
    REDIR_LEFT,
    DOUBLE_REDIR_RIGHT,
    DOUBLE_REDIR_LEFT
  }			t_type;

typedef struct		s_node
{
  char			*arg;
  t_type		type;
  struct s_node		*left;
  struct s_node		*right;
}			t_node;

typedef struct		s_list_sh
{
  t_node		*node;
  t_type		type;
  char			*arg;
  struct s_list_sh	*next;
  struct s_list_sh	*prev;
}			t_list_sh;

typedef struct		s_env
{
  char			**env;
  char			*pwd;
  char			*oldpwd;
  char			*home;
  char			**path;
  char			pst_pwd;
  char			pst_home;
  char			pst_oldpwd;
  char			pst_path;
}			t_env;

typedef struct		s_sh
{
  t_list_sh		*root;
  int			lenght;
  t_env			*env;
}			t_sh;

char		*epur(char *);
int		parsing(t_sh *, char *);
t_node		**insert_node(t_node **, char *, char *, t_type);
char            **my_str_to_word_tab(char *, char);
char            *my_strdup_e(char *, int);
char		*epur_str(char *);
int             check_env(t_sh *, char **);
int             check_path(t_sh *);
int             check_home(t_sh *);
int             check_pwd(t_sh *);
int             check_oldpwd(t_sh *);
char            *get_next_line(int);
t_list_sh	*add_list_after(t_sh *);
char		*my_strdup_bt(char *, int, int);
int		create_list(t_sh *);
void		print_tree(t_node *);

#endif /* _42s_H_ */
