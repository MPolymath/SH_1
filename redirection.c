/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 02:52:18 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/08 20:53:32 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char	*ft_element(char *str, int start, int end)
{
	char	*new_string;
	int		i;

	if (start == end)
		return (NULL);
	new_string = (char*)malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (start != (end))
	{
		new_string[i] = str[start];
		start++;
		i++;
	}
	new_string[i] = '\0';
	new_string = ft_strtrim(new_string);
	return (new_string);
}

void	init_splt_counts(int *i, int *cnt)
{
	*i = 0;
	*cnt = 0;
}

int		split_counts(char *str)
{
	int	i;
	int	cnt;

	init_splt_counts(&i, &cnt);
	while (str[i] != '\0')
	{
		if ((str[i] == '>' && str[i + 1] == '>'))
		{
			cnt += 2;
			i++;
		}
		else if ((str[i] == '<' && str[i + 1] == '<'))
		{
			cnt += 2;
			i++;
		}
		else if ((str[i] == '>'))
			cnt += 2;
		else if ((str[i] == '<'))
			cnt += 2;
		else if (str[i + 1] == '\0')
			cnt++;
		i++;
	}
	return (cnt);
}

void	case1(t_splt_var *var, char *str)
{
	(var->split_args)[var->j] = ft_element(str, var->start, var->i);
	(var->j)++;
	(var->split_args)[var->j] = ft_element(str, var->i, var->i + 1);
	(var->j)++;
	(var->i)++;
	var->start = var->i;
}

void	case2(t_splt_var *var, char *str)
{
	(var->split_args)[var->j] = ft_element(str, var->start, var->i);
	(var->j)++;
	(var->split_args)[var->j] = ft_element(str, var->i, var->i + 2);
	(var->j)++;
	(var->i)++;
	(var->i)++;
	var->start = var->i;
}

void	case3(t_splt_var *var, char *str)
{
	(var->i)++;
	(var->split_args)[var->j] = ft_element(str, var->start, var->i);
	(var->j)++;
}

char		**str_split_pipes(char *str)
{
	t_splt_var	var;

	var.i = 0;
	var.j = 0;
	var.start = 0;
	var.count = 0;
	var.count = split_counts(str);
	var.split_args = (char**)malloc(sizeof(char*) * (var.count + 1));
	while ((str)[var.i] != '\0')
	{
		if (((str)[var.i] == '>' && (str)[var.i + 1] == '>') && var.i != 0)
			case2(&var, str);
		else if (((str)[var.i] == '<' && (str)[var.i + 1] == '<') && var.i != 0)
			case2(&var, str);
		else if (((str)[var.i] == '>') && var.i != 0)
			case1(&var, str);
		else if (((str)[var.i] == '<') && var.i != 0)
			case1(&var, str);
		else if (((str)[var.i + 1] == '\0') && var.i != 0)
			case3(&var, str);
		else
			(var.i)++;
	}
	(var.split_args)[var.count] = NULL;
	return (var.split_args);
}
