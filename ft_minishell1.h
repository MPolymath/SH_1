/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell1.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:18:36 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/14 16:47:59 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL1_H
# define FT_MINISHELL1_H
# include "libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>

typedef struct	s_main
{
	int			fd;
	int			args_nbr;
	int			i;
	char		**env;
	char		**temp_env;
	char		*line;
	char		*tmp;
	char		*command;
	char		*test_path;
	char		**paths;
	char		**split_args;
}				t_main;

typedef struct	s_args
{
	int			size;
	int			tmp_start;
	int			i;
	int			j;
}				t_args;

typedef struct	s_paths
{
	char		*cur_path;
	char		*cur_home;
	char		*old_path;
}				t_paths;

typedef struct	s_make
{
	int			length_path;
	int			i;
	int			k;
	int			j;
	char		*path;
}				t_make;

void			cpy_env(char **envp, t_main *vars);
void			exec_others_cmd(t_main **vars);
void			execute(t_main *vars, t_paths **var);
void			ft_fork(t_main **vars, t_paths *var);
void			cd_cmd(t_main **vars, t_paths **var);
void			setenv_cmd(t_main **vars);
void			unsetenv_cmd(t_main **vars);
void			env_cmd(t_main **vars);
int				test_space_tab(char *str, int i);
void			ft_split_to_space(t_main **vars, int *start, int *size);
int				count_args(t_main **vars, int start);
void			get_size_str(t_main **vars, int i, int *size);
void			fill_malloc_char(t_main **vars, int **start, int *i, int *j);
void			init_var(t_args *var);
void			args_cpy(t_main **vars, int *start);
void			ft_split_args(t_main **vars);
int				test_for_path(char *str);
void			cpy_path(char **cpy_path, char **env);
void			rmv_path(char **path);
char			**ft_split_path(char **envp, char ***env);
void			init_main(t_main *vars, int argc, char **argv);
void			while_funcs(t_main *vars);
void			main_body(t_main *vars);
int				find_var(t_main **vars);
void			set_var(t_main **vars);
void			set_var_env(t_main **vars);
void			get_var_value(char ***var_value, t_main **vars);
void			ft_env(t_main **vars);
void			free_temp(char **temp);
#endif
