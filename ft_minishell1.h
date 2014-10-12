/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell1.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:18:36 by mdiouf            #+#    #+#             */
/*   Updated: 2014/10/12 18:04:12 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>

typedef struct	s_main
{
	int			fd;
	int			args_nbr;
	char		**env;
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
	int 		j;
}				t_args;

char			**ft_split_path(char **envp, char ***env);
void			execute(t_main *vars);
void			ft_fork(t_main *vars);
