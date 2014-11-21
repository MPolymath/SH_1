/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 14:50:17 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/21 02:37:22 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		check_valid_a(char *full_str)
{
	int		i;

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

int		check_valid_b(char *full_str)
{
	int		i;

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

int		check_valid_c(char *full_str)
{
	int		i;

	i = 0;
	while (full_str[i] != '\0')
	{
		if (full_str[i] == '>' || full_str[i] == '<')
		{
			if (full_str[i + 1] != '\0')
				if ((full_str[i] == '>' && full_str[i + 1] == '>' && full_str[i + 2] == '>') ||
					(full_str[i] == '>' && full_str[i + 1] == '>' && full_str[i + 2] == '<') ||
					(full_str[i] == '>' && full_str[i + 1] == '>' && full_str[i + 2] == '|') ||
					(full_str[i] == '>' && full_str[i + 1] == '>' && full_str[i + 2] == ';') ||
					(full_str[i] == '<' && full_str[i + 1] == '<' && full_str[i + 2] == '<') ||
					(full_str[i] == '<' && full_str[i + 1] == '<' && full_str[i + 2] == '<') ||
					(full_str[i] == '<' && full_str[i + 1] == '<' && full_str[i + 2] == '|') ||
					(full_str[i] == '<' && full_str[i + 1] == '<' && full_str[i + 2] == ';'))
				{
					ft_putstr_fd("Erreur , Invalid string\n", 2);
					return (1);
				}
		}
		i++;
	}
	return (0);
}

int		check_valid(char *full_str)
{
	if (check_valid_a(full_str) == 1 || check_valid_b(full_str) == 1 || check_valid_c(full_str) == 1)
		return (0);
	return (1);
}

int			count_and_pipe(char	*full_str)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	if (check_valid(full_str) == 0)
		return (-1);
	while (full_str[i] != '\0')
	{
		if (full_str[i] == ';' || full_str[i] == '|')
			cnt = cnt + 2;
		i++;
		if (full_str[i] == '\0' && (full_str[i - 1] != ';' && full_str[i - 1] != '|'))
			cnt = cnt + 1;
	}
	if (full_str[i] != '\0')
		cnt++;
	return (cnt);
}

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
		return (NULL);
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

/*
char		*create_node(char *str)
{
}

void		*insert_node()
{
}
*/

int		main(int argc, char **argv)
{
	char	**list;
	int		i;

	i = 0;
	if (argc == 2)
	{
		list = split_pipe_and(argv[1]);
		while (list[i] != NULL)
		{
			printf("%s\n", list[i]);
			i++;
		}
		create_tree(&list);
	}
	else
		ft_putstr_fd("Erreur\n", 2);
}
