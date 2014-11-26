/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 02:52:18 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/26 05:06:09 by mdiouf           ###   ########.fr       */
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

int		split_counts(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
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

char	**str_split_pipes(char *str)
{
	int		i;
	int		j;
	int		start;
	int		count;
	char	**split_args;

	i = 0;
	j = 0;
	start = 0;
	count = 0;
	count = split_counts(str);
//	printf("count: %d\n", count);
	split_args =  (char**)malloc(sizeof(char*) * (count + 1));
	while (str[i] != '\0')
	{
		if ((str[i] == '>' && str[i + 1] == '>') && i != 0)
		{
			split_args[j] = ft_element(str, start, i);
			j++;
			split_args[j] =ft_element(str, i, i + 2);
			j++;
			i++;
			i++;
			start = i;
		}
		else if ((str[i] == '<' && str[i + 1] == '<') && i != 0)
		{
			split_args[j] = ft_element(str, start, i);
			j++;
			split_args[j] = ft_element(str, i, i + 2);
			j++;
			i++;
			i++;
			start = i;
		}
		else if ((str[i] == '>') && i != 0)
		{
			split_args[j] = ft_element(str, start, i);
			j++;
			split_args[j] = ft_element(str, i, i + 1);
			j++;
			i++;
			start = i;
		}
		else if ((str[i] == '<') && i != 0)
		{
			split_args[j] = ft_element(str, start, i);
			j++;
			split_args[j] = ft_element(str, i, i + 1);
			j++;
			i++;
			start = i;
		}
		else if ((str[i + 1] == '\0') && i != 0)
		{
			i++;
			split_args[j] = ft_element(str, start, i);
			j++;
		}
		else
			i++;
	}
//	printf("split_args[count - 1] : %s\n", split_args[count - 1]);
	split_args[count] = NULL;
	return (split_args);
}
/*
int		main(int argc,	char **argv)
{
	char	**str;
	int		i;

	i = 0;
	str = str_split_pipes(argv[1]);
	while (str[i] != NULL)
	{
		printf("str[i] %s\n", str[i]);
		i++;
	}
}*/
