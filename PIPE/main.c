/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 00:23:53 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/16 02:18:44 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		main(int argc, char **argv, char **envp)
{
	int	pid;
	int	fd[2];
	int	step;
	char	**ls_lst;
	char	**wc_lst;

	fd[0] = -1;
	fd[1] = -1;
	step = 0;
	ls_lst = (char**)malloc(sizeof(char*) * 2);
	ls_lst[0] = (char*)malloc(sizeof(char) * 3);
	ls_lst[0][0] = 'l';
	ls_lst[0][1] = 's';
	ls_lst[0][2] = '\0';
	ls_lst[1] = NULL;
	wc_lst = (char**)malloc(sizeof(char*) * 3);
	wc_lst[0] = (char*)malloc(sizeof(char) * 3);
	wc_lst[1] = (char*)malloc(sizeof(char) * 3);
	wc_lst[0][0] = 'w';
	wc_lst[0][1] = 'c';
	wc_lst[0][2] = '\0';
	wc_lst[1][0] = '-';
	wc_lst[1][1] = 'l';
	wc_lst[1][2] = '\0';
	wc_lst[2] = NULL;
	pipe(fd);
	pid = fork();
	if ((pid == 0 && step == 0))
	{
		printf("Son\n");
		dup2(fd[1], 1);
		close(fd[0]);
		execve("/bin/ls", ls_lst, envp);
	}
	else if (pid != 0)
	{
		wait(NULL);
		dup2(fd[0], 0);
		close(fd[1]);
		pid = fork();
		if ((pid == 0))
		{
			printf("Son2\n");
			dup2(fd[1], 1);
			close(fd[0]);
			execve("/usr/bin/wc", wc_lst, envp);
		}
		else if (pid != 0)
		{
			wait(NULL);
		}
		while (1);
//		execve("/usr/bin/wc", wc_lst, envp);
		printf("Father\n");
	}
}
