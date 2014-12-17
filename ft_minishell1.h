/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell1.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:18:36 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/17 14:45:19 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL1_H
# define FT_MINISHELL1_H
# include "libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>

typedef struct		s_tree
{
	int				child;
	char			*cmd;
	struct s_tree	*left;
	struct s_tree	*left_two;
	struct s_tree	*right;
	struct s_tree	*right_next;;
	struct s_tree	*right_two;
}					t_tree;

typedef struct		s_ptr
{
	t_tree			*root;
	t_tree			*start_child;
	t_tree			*temp;
	t_tree			*temp2;
}					t_ptr;

typedef struct		s_main
{
	int				fd;
	int				args_nbr;
	int				i;
	int				type;
	int				pipe_fd[2];
	int				pipe_fd2[2];
	int				zero_backup;
	int				one_backup;
	int				next_pipe;
	int				previous_pipe;
	int				last_command;
	char			**env;
	char			**temp_env;
	char			*line;
	char			*line2;
	char			*tmp;
	char			*tmp2;
	char			*command;
	char			*command2;
	char			*test_path;
	char			**paths;
	char			**split_args;
	char			**split_args2;
	char			**list;
	char			**cmd_list;
	char			**cmd_list2;
	t_tree			*temp;
	t_ptr			var;
}					t_main;

typedef struct		s_splt
{
	int				i;
	int				j;
	int				splits;
	int				start;
	char			**split_str;
}					t_splt;

typedef struct		s_args
{
	int				size;
	int				tmp_start;
	int				i;
	int				j;
}					t_args;

typedef struct		s_paths
{
	char			*cur_path;
	char			*cur_home;
	char			*old_path;
}					t_paths;

typedef struct		s_make
{
	int				length_path;
	int				i;
	int				k;
	int				j;
	char			*path;
}					t_make;

typedef struct		s_var_env
{
	int				posy;
	int				cnt_env;
	int				i;
	int				j;
	int				alpha;
	int				size_new_line;
	char			**var_value;
	char			**new_env;
	char			*temp;
}					t_var_env;

typedef struct		s_mn
{
	t_main			vars;
	t_main			*temp2;
	t_paths			var;
	t_paths			*temp;
}					t_mn;

typedef struct		s_splt_var
{
	int				i;
	int				j;
	int				start;
	int				count;
	char			**split_args;
}					t_splt_var;

void				cpy_env(char **envp, t_main *vars);
void				exec_others_cmd(t_main **vars);
void				execute(t_main **vars, t_paths **var);
void				ft_fork(t_main **vars, t_paths **var);
void				cd_cmd(t_main **vars, t_paths **var);
void				setenv_cmd(t_main **vars);
void				unsetenv_cmd(t_main **vars);
void				env_cmd(t_main **vars, t_paths **var);
int					test_space_tab(char *str, int i);
void				ft_split_to_space(t_main **vars, int *start, int *size);
void				ft_split_to_space2(t_main **vars, int *start, int *size);
int					count_args(t_main **vars, int start);
void				get_size_str(t_main **vars, int i, int *size);
void				fill_malloc_char(t_main **vars, int **start, int *i, int *j);
void				init_var(t_args *var);
void				args_cpy(t_main **vars, int *start);
void				args_cpy2(t_main **vars, int *start);
void				ft_split_args(t_main **vars);
void				ft_split_args2(t_main **vars);
int					test_for_path(char *str);
void				cpy_path(char **cpy_path, char **env);
void				rmv_path(char **path);
char				**ft_split_path(char **envp, char ***env);
void				init_main(t_main *vars, int argc, char **argv);
void				while_funcs(t_main **vars, t_paths **var);
void				main_body(t_main *vars);
int					find_var(t_main **vars);
void				set_var(t_main **vars);
void				unset_var(t_main **vars);
void				set_var_env(t_main **vars, t_paths **var);
void				get_var_value(char ***var_value, t_main **vars);
void				ft_env(t_main **vars, t_paths **var);
void				make_path_init(t_make *var);
void				get_home_init(t_make *var);
void				get_old_init(t_make *var);
void				prev_folder(char **cur_folder);
char				*make_path(t_main **vars);
void				end_str(char **path, int k);
char				*get_home(t_main **vars);
char				*get_old_pwd(t_main **vars);
void				free_temp(char **temp);
void				change_pwd(char **new_path, t_main **vars, t_paths **var);
void				change_old_pwd(t_main **vars, t_paths **var);
void				change_env_pwd(char **new_pwd, t_paths **var, t_main **vars);
void				path_constr(t_paths **var, t_main **vars, char **split_path);
void				handle_cd(t_main **vars, t_paths **var);
void				change_old_pwd(t_main **vars, t_paths **var);
void				change_pwd(char **new_path, t_main **vars, t_paths **var);
void				free_temp(char **temp);
char				*get_home(t_main **vars);
char				*get_old_pwd(t_main **vars);
char				*make_path(t_main **vars);
void				init_set_var_env(t_var_env *bod);
void				cpy_envp(t_main **vars, char **env);
void				handle_temp_env(t_main **vars, t_var_env *bod);
int					exec_temp_command(t_main **vars, t_var_env *bod);
void				if_temp_command(t_main **vars, t_paths **var, t_var_env *bod);
int					find_var_env(t_main **vars, char **vars_value);
int					check_valid_a(char *full_str);
int					check_valid_b(char *full_str);
int					check_valid_c(char *full_str);
int					check_valid(char *full_str);
int					count_and_pipe(char *full_str);
char				**split_pipe_and(char *full_str);
char				*ft_element(char *str, int start, int end);
int					split_counts(char *str);
char				**str_split_pipes(char *str);
t_tree				*ft_new_node(char **command);
void				create_tree(char ***split_commands, t_ptr *var);
void				set_line_args_cmd(t_main **vars, t_tree **temp);
void				set_line2_args2_cmd2(t_main **vars, t_tree **temp);
void				ft_next(t_main **vars);
#endif
