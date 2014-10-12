/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/12 16:52:19 by mdiouf            #+#    #+#             */
/*   Updated: 2014/10/12 20:26:58 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	ft_fork(t_main *vars)
{
	int	pid;

	if (ft_strcmp(vars->command, "exit") == 0)
		exit(0);
	pid = fork();
	if (pid == 0)
		execute(vars);
	else if (pid > 0)
		wait(NULL);
	else
		ft_putstr("Fork Error\n");
}
