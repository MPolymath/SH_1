/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 13:40:44 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 18:41:15 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int				find_sign(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

void			ft_env_a(t_main **vars, int *i)
{
	*i = 2;
	if ((*vars)->split_args[2] != NULL)
	{
		while ((*vars)->split_args[*i] != NULL)
		{
			ft_putstr_fd((*vars)->split_args[*i], 2);
			(*i)++;
			ft_putstr_fd(" ", 2);
		}
		ft_putstr_fd("cannot be executed, env missing.\n", 2);
	}
}

void			ft_env(t_main **vars, t_paths **var)
{
	int			i;

	i = 0;
	if (((*vars)->split_args)[1] == '\0')
		while ((*vars)->env[i] != '\0')
		{
			ft_putstr((*vars)->env[i]);
			ft_putstr("\n");
			i++;
		}
	else if (ft_strcmp(((*vars)->split_args)[1], "-i") == 0)
		ft_env_a(vars, &i);
	else if (find_sign((*vars)->split_args[1]) == 1)
		set_var_env(vars, var);
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(((*vars)->split_args)[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
