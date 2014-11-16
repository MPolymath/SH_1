/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 20:44:11 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 20:46:31 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int			find_var_env(t_main **vars, char **vars_value)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*vars)->env[j] != '\0')
	{
		while (vars_value[0][i] != '\0')
		{
			if (vars_value[0][i] != ((*vars)->env)[j][i])
			{
				i = 0;
				break ;
			}
			else
				i++;
		}
		if (vars_value[0][i] == '\0')
			return (j);
		j++;
	}
	return (-1);
}

int			find_var(t_main **vars)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*vars)->env[j] != '\0')
	{
		while (((*vars)->split_args)[1][i] != '\0')
		{
			if (((*vars)->split_args)[1][i] != ((*vars)->env)[j][i])
			{
				i = 0;
				break ;
			}
			else
				i++;
		}
		if (((*vars)->split_args)[1][i] == '\0')
			return (j);
		j++;
	}
	return (-1);
}

void		init_var_val(char ***var_value, t_main **vars, int *limit)
{
	int		i;

	i = 0;
	while ((*vars)->split_args[1][i] != '=')
		i++;
	*limit = i + 1;
	(*var_value)[0] = (char*)malloc(sizeof(char) * ((*limit) + 1));
	(*var_value)[1] = (char*)malloc(sizeof(char) *
	(ft_strlen((*vars)->split_args[1]) - ((*limit) - 1)));
}

void		get_var_value(char ***var_value, t_main **vars)
{
	int		i;
	int		j;
	int		limit;

	j = 0;
	i = 0;
	init_var_val(var_value, vars, &limit);
	while (i != limit)
	{
		(*var_value)[0][i] = (*vars)->split_args[1][i];
		i++;
	}
	(*var_value)[0][i] = '\0';
	while ((*vars)->split_args[1][i] != '\0')
	{
		(*var_value)[1][j] = (*vars)->split_args[1][i];
		i++;
		j++;
	}
	(*var_value)[1][j] = '\0';
}

void		cpy_envp(t_main **vars, char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if ((*vars)->temp_env == NULL)
		(*vars)->temp_env = (char **)malloc(sizeof(char*) * (i + 1));
	else
		return ;
	i = 0;
	while (env[i] != NULL)
	{
		(*vars)->temp_env[i] = ft_strdup(env[i]);
		i++;
	}
	(*vars)->temp_env[i] = NULL;
}
