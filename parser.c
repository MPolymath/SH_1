/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 14:50:17 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/08 22:33:33 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int				check_valid_a(char *full_str)
{
	int			i;

	i = 0;
	while (full_str[i] != '\0')
	{
		if (full_str[i] == ';' || full_str[i] == '|')
		{
			if (full_str[i + 1] == ';' || full_str[i + 1] == '|' ||
				full_str[i + 1] == '>' || full_str[i + 1] == '<')
			{
				ft_putstr_fd("Erreur , Invalid string\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int				check_valid_b(char *full_str)
{
	int			i;

	i = 0;
	while (full_str[i] != '\0')
	{
		if (full_str[i] == '>' || full_str[i] == '<')
		{
			if (full_str[i + 1] == ';' || full_str[i + 1] == '|' ||
				(full_str[i] == '<' && full_str[i + 1] == '>') ||
				(full_str[i] == '>' && full_str[i + 1] == '<'))
			{
				ft_putstr_fd("Erreur , Invalid string\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int				check_error(char *full_str, int i)
{
	if ((full_str[i] == '>' && full_str[i + 1] == '>' &&
		full_str[i + 2] == '>') ||
		(full_str[i] == '>' && full_str[i + 1] == '>' &&
		full_str[i + 2] == '<') ||
		(full_str[i] == '>' && full_str[i + 1] == '>' &&
		full_str[i + 2] == '|') ||
		(full_str[i] == '>' && full_str[i + 1] == '>' &&
		full_str[i + 2] == ';') ||
		(full_str[i] == '<' && full_str[i + 1] == '<' &&
		full_str[i + 2] == '<') ||
		(full_str[i] == '<' && full_str[i + 1] == '<' &&
		full_str[i + 2] == '<') ||
		(full_str[i] == '<' && full_str[i + 1] == '<' &&
		full_str[i + 2] == '|') ||
		(full_str[i] == '<' && full_str[i + 1] == '<' &&
		full_str[i + 2] == ';'))
	{
		ft_putstr_fd("Erreur , Invalid string\n", 2);
		return (-1);
	}
	return (0);
}

int				check_valid_c(char *full_str)
{
	int			i;

	i = 0;
	while (full_str[i] != '\0')
	{
		if (full_str[i] == '>' || full_str[i] == '<')
		{
			if (full_str[i + 1] != '\0')
			{
				if (check_error(full_str, i) == -1)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int				check_valid(char *full_str)
{
	if (check_valid_a(full_str) == 1 || check_valid_b(full_str) == 1 ||
		check_valid_c(full_str) == 1)
		return (0);
	return (1);
}

int				count_and_pipe(char *full_str)
{
	int			i;
	int			cnt;

	i = 0;
	cnt = 0;
	if (check_valid(full_str) == 0)
		return (-1);
	while (full_str[i] != '\0')
	{
		if (full_str[i] == ';' || full_str[i] == '|')
			cnt = cnt + 2;
		i++;
		if (full_str[i] == '\0' && (full_str[i - 1] != ';' &&
			full_str[i - 1] != '|'))
			cnt = cnt + 1;
	}
	if (full_str[i] != '\0')
		cnt++;
	return (cnt);
}

int		pipe_and_case_split(t_splt *vars, char *full_str)
{
	(vars->split_str)[vars->j] =
	ft_strsub(full_str, vars->start, (vars->i) - (vars->start));
	(vars->split_str)[vars->j] =
	ft_strtrim((vars->split_str)[(vars->j)]);
	if ((vars->split_str)[(vars->j)][0] == '\0')
	{
		free((vars->split_str)[vars->j]);
		ft_putstr_fd("Invalid chain\n", 2);
		return (-1);
	}
	vars->start = (vars->i) + 1;
	(vars->j)++;
	(vars->split_str)[vars->j] = (char*)malloc(sizeof(char) * 2);
	(vars->split_str)[vars->j][0] = full_str[vars->i];
	(vars->split_str)[vars->j][1] = '\0';
	(vars->j)++;
	return (0);
}

void	pipe_and_not_split(t_splt *vars, char *full_str)
{
	(vars->split_str)[vars->j] =
	ft_strsub(full_str, vars->start, (vars->i) - (vars->start) + 1);
	(vars->split_str)[vars->j] =
	ft_strtrim((vars->split_str)[vars->j]);
	if ((vars->split_str)[vars->j][0] == '\0')
	{
		free((vars->split_str)[vars->j]);
		(vars->split_str)[vars->j] = NULL;
	}
	(vars->j)++;
}

void	print_split(t_splt *vars)
{
	(vars->i) = 0;
	while ((vars->split_str)[vars->i] != NULL)
	{
		printf("split_str[%d] %s\n", vars->i, (vars->split_str)[vars->i]);
		(vars->i)++;
	}
}

void		init_pipe_and(t_splt *vars, char *full_str)
{
	vars->i = 0;
	vars->j = 0;
	vars->start = 0;
	vars->splits = count_and_pipe(full_str);
}

char		**split_pipe_and(char *full_str)
{
	t_splt	vars;

	init_pipe_and(&vars, full_str);
	if (vars.splits == -1)
	{
		exit(0);
		return (NULL);
	}
	vars.split_str = (char**)malloc(sizeof(char*) * ((vars.splits) + 1));
	while (full_str[vars.i] != '\0')
	{
		if (full_str[vars.i] == ';' || full_str[vars.i] == '|')
		{
			if (pipe_and_case_split(&vars, full_str) == -1)
				return (NULL);
		}
		else if (full_str[(vars.i) + 1] == '\0' &&
				(full_str[(vars.i)] != ';' && full_str[(vars.i)] != '|'))
			pipe_and_not_split(&vars, full_str);
		(vars.i)++;
	}
	(vars.split_str)[vars.j] = NULL;
	print_split(&vars);
	return ((vars.split_str));
}
