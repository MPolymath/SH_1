/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/10 19:01:21 by mdiouf            #+#    #+#             */
/*   Updated: 2014/10/12 17:43:42 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		test_for_path(char *str)
{
	if	(str[0] == 'P' && str[1] == 'A' && str[2] == 'T'
					&& str[3] == 'H' && str[4] == '=')
		return (1);
	else
		return (0);
}
void	cpy_path(char **cpy_path, char **env)
{
	int	i;

	i = 0;
	while (env[i] != '\0')
	{
		if (test_for_path(env[i]))
		{
			*cpy_path = ft_strdup(env[i]);
			break;
		}
		i++;
	}
}

void	rmv_path(char **path)
{
	int	i;

	i = 5;
	while ((*path)[i] != '\0')
	{
		(*path)[i - 5] = (*path)[i];
		(*path)[i] = '\0';
		i++;
	}
}

char	**ft_split_path(char **envp, char ***env)
{
	int		i;
	char 	*path;
	char	**split_path;

	i = 0;
	path = NULL;
	while (envp[i] != '\0')
		i++;
	*env = (char**)malloc(sizeof(char*) * i);
	i = 0;
	while (envp[i] != '\0')
	{
		(*env)[i] = ft_strdup(envp[i]);
		i++;
	}
	i = 0;
	cpy_path(&path, *env);
	rmv_path(&path);
	split_path = ft_strsplit(path, ':');
//	if (path != NULL)
//	{
//		free(path);
//		path = NULL;
//	}
	return (split_path);
}
