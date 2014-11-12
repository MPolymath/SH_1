/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*     setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 16:33:38 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/12 18:26:03 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

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
				break;
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

void		remove_var(t_main **vars)
{
	int		posy;
	int		cnt_env;
	int		i;

	i = 0;
	posy = 0;
	cnt_env = 0;
	while (((*vars)->env)[i] != NULL)
	{
		i++;
		cnt_env++;
	}
	if ((posy = find_var(vars)) == -1)
		ft_putstr_fd("Variable not found\n", 2);
	else if (ft_strcmp((*vars)->split_args[1], "PATH=") == 0 || ft_strcmp((*vars)->split_args[1], "PWD=") == 0 || ft_strcmp((*vars)->split_args[1], "OLDPWD=") == 0)
	{
		ft_putstr_fd("This variable cannot be altered\n", 2);
	}
	else
	{
		free(((*vars)->env)[posy]);
		(*vars)->env[posy] = NULL;
		(*vars)->env[posy] = ft_strjoin((*vars)->split_args[1], (*vars)->split_args[2]);
	}
}
