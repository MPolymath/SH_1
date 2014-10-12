/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/06 17:17:43 by mdiouf            #+#    #+#             */
/*   Updated: 2014/10/12 18:12:20 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int			main(int argc, char **argv, char **envp)
{
	t_main	vars;
	int		i;

	cpy_env(envp, &vars);
	vars.fd = 0;
	i = 0;
	ft_putstr("$> ");
	vars.paths = ft_split_path(envp, &(vars.env)); // new
	while (get_next_line(vars.fd, &(vars.line)))
	{
		ft_split_args(&vars);
		ft_fork(&vars);
		ft_putstr("$> ");
/*		if (vars.split_args != NULL)
		{
			while (vars.split_args[i] != NULL)
			{
				free(vars.split_args[i]);
				vars.split_args[i] = NULL;
				i++;
			}
			free(vars.split_args);
			vars.split_args = NULL;
		}
		if (vars.command != NULL)
		{
			free(vars.command);
			vars.command = NULL;
		}*/
	}
	return (0);
}
