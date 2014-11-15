/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 16:52:19 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/15 19:34:26 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	ft_fork(t_main **vars, t_paths **var)
{
	int	pid;

	if (ft_strcmp((*vars)->command, "exit") == 0)
		exit(0);
	pid = fork();
	if (pid == 0)
		execute(vars, var);
	else if (pid > 0)
	{
		wait(NULL);
		if ((*vars)->temp_env != NULL)
		{
			if ((*vars)->env != NULL)
			{
				free((*vars)->env);
				(*vars)->env = NULL;
			}
			(*vars)->env = (*vars)->temp_env;
			(*vars)->temp_env = NULL;
		}
	}
	else
		ft_putstr("Fork Error\n");
}
