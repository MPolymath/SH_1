/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 16:33:38 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 21:09:00 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		unset_var(t_main **vars)
{
	int		posy;
	int		i;

	i = 0;
	posy = 0;
	while (((*vars)->env)[i] != NULL)
		i++;
	i = 0;
	if ((posy = find_var(vars)) == -1)
		ft_putstr_fd("Variable not found\n", 2);
	else if (ft_strcmp((*vars)->split_args[1], "PATH") == 0 ||
			ft_strcmp((*vars)->split_args[1], "PWD") == 0 ||
			ft_strcmp((*vars)->split_args[1], "OLDPWD") == 0 ||
			ft_strcmp((*vars)->split_args[1], "HOME") == 0)
		ft_putstr_fd("This variable cannot be altered\n", 2);
	else
	{
		free(((*vars)->env)[posy]);
		(*vars)->env[posy] = NULL;
	}
}
