/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 13:38:02 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/04 18:13:19 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"
#include <stdio.h>

void		exec_others_cmd(t_main **vars)
{
	int		i;

	i = 0;
	if ((*vars)->paths != NULL)
	{
		if (execve((*vars)->command, (*vars)->split_args, (*vars)->env) == -1)
		{
			while ((*vars)->paths[i] != '\0')
			{
				if ((*vars)->test_path != NULL)
				{
					free((*vars)->test_path);
					(*vars)->test_path = NULL;
				}
				(*vars)->test_path =
							ft_strjoin((*vars)->paths[i], (*vars)->command);
				printf("test_path: %s\n", (*vars)->test_path);
				execve((*vars)->test_path, (*vars)->split_args, (*vars)->env);
				i++;
			}
			ft_putstr((*vars)->command);
			ft_putstr(": command not found\n");
			exit(0);
		}
	}
}

void		execute(t_main **vars, t_paths **var)
{
	if ((*vars)->type == 2)
	{
		dup2(((*vars)->pipe_fd)[1], 1);
		close(((*vars)->pipe_fd)[0]);
	}
	if (ft_strcmp((*vars)->command, "cd") == 0)
		cd_cmd(vars, var);
	else if (ft_strcmp((*vars)->command, "setenv") == 0)
		setenv_cmd(vars);
	else if (ft_strcmp((*vars)->command, "unsetenv") == 0)
		unsetenv_cmd(vars);
	else if (ft_strcmp((*vars)->command, "env") == 0)
		env_cmd(vars, var);
	else
		exec_others_cmd(vars);
}
