/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 20:50:44 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/14 21:05:05 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		unsetenv_cmd(t_main **vars)
{
	vars = vars;
	unset_var(vars);
	ft_putstr(" unsetenv is not done\n");
}

void		setenv_cmd(t_main **vars)
{
	vars = vars;
	if (((*vars)->split_args)[0] != NULL &&
		((*vars)->split_args)[1] != NULL && ((*vars)->split_args)[2] != NULL
		&& ((*vars)->split_args)[3] == NULL)
		set_var(vars);
}

void		env_cmd(t_main **vars)
{
	vars = vars;
	ft_env(vars);
}
