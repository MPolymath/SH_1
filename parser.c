/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 14:50:17 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/06 19:56:07 by mdiouf           ###   ########.fr       */
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

int				count_and_pipe(char	*full_str)
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

/*int		if_splits(char ***split_str, int i,)
{

}*/


char 		**split_pipe_and(char *full_str)
{
//	int		i;
//	int		j;
//	int		splits;
//	int		start;
//	char	**split_str;
	t_splt	vars;

	vars.i = 0;
	vars.j = 0;
	vars.start = 0;
	vars.splits = count_and_pipe(full_str);
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
			(vars.split_str)[vars.j] = ft_strsub(full_str, vars.start, (vars.i) - (vars.start));
			(vars.split_str)[vars.j] = ft_strtrim((vars.split_str)[(vars.j)]);
			if ((vars.split_str)[(vars.j)][0] == '\0')
			{
				free((vars.split_str)[vars.j]);
				ft_putstr_fd("Invalid chain\n", 2);
				return (NULL);
			}
			vars.start = (vars.i) + 1;
			(vars.j)++;
			(vars.split_str)[vars.j] = (char*)malloc(sizeof(char) * 2);
			(vars.split_str)[vars.j][0] = full_str[vars.i];
			(vars.split_str)[vars.j][1] = '\0';
			(vars.j)++;
		}
		else if (full_str[(vars.i) + 1] == '\0' && (full_str[(vars.i)] != ';' && full_str[(vars.i)] != '|'))
		{
			(vars.split_str)[vars.j] = ft_strsub(full_str, vars.start, (vars.i) - (vars.start) + 1);
			(vars.split_str)[vars.j] = ft_strtrim((vars.split_str)[vars.j]);
			if ((vars.split_str)[vars.j][0] == '\0')
			{
				free((vars.split_str)[vars.j]);
				(vars.split_str)[vars.j] = NULL;
			}
			(vars.j)++;
		}
		(vars.i)++;
	}
	(vars.split_str)[vars.j] = NULL;
	(vars.i) = 0;
	while ((vars.split_str)[vars.i] != NULL)
	{
		printf("split_str[%d] %s\n", vars.i, (vars.split_str)[vars.i]);
		(vars.i)++;
	}
	return ((vars.split_str));
}

/*
char 		**split_pipe_and(char *full_str)
{
	int		i;
	int		j;
	int		splits;
	int		start;
	char	**split_str;

	i = 0;
	j = 0;
	start = 0;
	splits = count_and_pipe(full_str);
	if (splits == -1)
	{
		exit (0);
		return (NULL);
	}
	split_str = (char**)malloc(sizeof(char*) * (splits + 1));
	while (full_str[i] != '\0')
	{
		if (full_str[i] == ';' || full_str[i] == '|')
		{
			split_str[j] = ft_strsub(full_str, start, i - start);
			split_str[j] = ft_strtrim(split_str[j]);
			if (split_str[j][0] == '\0')
			{
				free(split_str[j]);
				ft_putstr_fd("Invalid chain\n", 2);
				return (NULL);
			}
			start = i + 1;
			j++;
			split_str[j] = (char*)malloc(sizeof(char) * 2);
			split_str[j][0] = full_str[i];
			split_str[j][1] = '\0';
			j++;
		}
		else if (full_str[i + 1] == '\0' && (full_str[i] != ';' && full_str[i] != '|'))
		{
			split_str[j] = ft_strsub(full_str, start, i - start + 1);
			split_str[j] = ft_strtrim(split_str[j]);
			if (split_str[j][0] == '\0')
			{
				free(split_str[j]);
				split_str[j] = NULL;
			}
			j++;
		}
		i++;
	}
	split_str[j] = NULL;
	i = 0;
	while (split_str[i] != NULL)
	{
		printf("split_str[%d] %s\n", i, split_str[i]);
		i++;
	}
	return (split_str);
}
*/
