/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:23:43 by mdiouf            #+#    #+#             */
/*   Updated: 2014/10/12 17:19:01 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	cpy_env(char **envp, t_main *vars)
{
	int	i;

	i = 0;
	vars->split_args = NULL;
	vars->paths = NULL;
	while (envp[i] != '\0')
		i++;
	vars->env = (char**)malloc(sizeof(char*) * i);
	i = 0;
	while (envp[i] != '\0')
	{
		vars->env[i] = ft_strdup(envp[i]);
		i++;
	}
}
