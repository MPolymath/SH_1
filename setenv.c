/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 18:33:56 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 21:11:44 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		set_var_env(t_main **vars, t_paths **var)
{
	t_var_env	bod;

	init_set_var_env(&bod);
	get_var_value(&(bod.var_value), vars);
	cpy_envp(vars, (*vars)->env);
	bod.temp = ft_strjoin((bod.var_value)[0], (bod.var_value)[1]);
	handle_temp_env(vars, &bod);
	bod.i = 0;
	while ((*vars)->line[bod.i] != '\0')
	{
		if (exec_temp_command(vars, &bod) == 1)
			break ;
	}
	bod.size_new_line = ft_strlen((*vars)->line) - bod.i;
	bod.temp = (*vars)->line;
	if (bod.size_new_line != 0)
		if_temp_command(vars, var, &bod);
	else
	{
		free((*vars)->line);
		(*vars)->line = NULL;
	}
}

void		if_var_not_found(t_main **vars, int *cnt_env, int *i)
{
	char	**temp_env;

	temp_env = (char**)malloc(sizeof(char*) * (*cnt_env + 2));
	while ((*vars)->env[*i] != NULL)
	{
		temp_env[*i] = ft_strdup((*vars)->env[*i]);
		(*i)++;
	}
	temp_env[*i] = ft_strjoin((*vars)->split_args[1], "=");
	temp_env[*i] = ft_strjoin(temp_env[*i], (*vars)->split_args[2]);
	temp_env[(*i) + 1] = NULL;
	*i = 0;
	if ((*vars)->env != NULL)
	{
		free((*vars)->env);
		(*vars)->env = NULL;
	}
	(*vars)->env = temp_env;
}

void		init_set_var(int *i, int *posy, int *cnt_env)
{
	*i = 0;
	*posy = 0;
	*cnt_env = 0;
}

void		set_var(t_main **vars)
{
	int		posy;
	int		cnt_env;
	int		i;

	init_set_var(&i, &posy, &cnt_env);
	while (((*vars)->env)[i] != NULL)
		i++;
	cnt_env = i;
	i = 0;
	if ((posy = find_var(vars)) == -1)
		if_var_not_found(vars, &cnt_env, &i);
	else if (ft_strcmp((*vars)->split_args[1], "PATH") == 0 ||
			ft_strcmp((*vars)->split_args[1], "PWD") == 0 ||
			ft_strcmp((*vars)->split_args[1], "OLDPWD") == 0 ||
			ft_strcmp((*vars)->split_args[1], "HOME") == 0)
		ft_putstr_fd("This variable cannot be altered\n", 2);
	else
	{
		free(((*vars)->env)[posy]);
		(*vars)->env[posy] = NULL;
		(*vars)->env[posy] = ft_strjoin((*vars)->split_args[1], "=");
		(*vars)->env[posy] =
				ft_strjoin((*vars)->env[posy], (*vars)->split_args[2]);
	}
}
