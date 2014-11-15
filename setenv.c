/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*     setenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 16:33:38 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/15 22:50:05 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int			find_var_env(t_main **vars, char **vars_value)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*vars)->env[j] != '\0')
	{
		while (vars_value[0][i] != '\0')
		{
			if (vars_value[0][i] != ((*vars)->env)[j][i])
			{
				i = 0;
				break;
			}
			else
				i++;
		}
		if (vars_value[0][i] == '\0')
			return (j);
		j++;
	}
	return (-1);
}

int			find_var(t_main **vars)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*vars)->env[j] != '\0')
	{
		while (((*vars)->split_args)[1][i] != '\0')
		{
			if (((*vars)->split_args)[1][i] != ((*vars)->env)[j][i])
			{
				i = 0;
				break;
			}
			else
				i++;
		}
		if (((*vars)->split_args)[1][i] == '\0')
			return (j);
		j++;
	}
	return (-1);
}

void		get_var_value(char ***var_value, t_main **vars)
{
	int		i;
	int		j;
	int		limit;

	i = 0;
	j = 0;
	while ((*vars)->split_args[1][i] != '=')
		i++;
	limit = i + 1;
	(*var_value)[0] = (char*)malloc(sizeof(char) * (limit + 1));
	i = 0;
	while (i != limit)
	{
		(*var_value)[0][i] = (*vars)->split_args[1][i];
		i++;
	}
	(*var_value)[0][i] = '\0';
	(*var_value)[1] = (char*)malloc(sizeof(char) * (ft_strlen((*vars)->split_args[1]) - (limit - 1)));
	while ((*vars)->split_args[1][i] != '\0')
	{
		(*var_value)[1][j] = (*vars)->split_args[1][i];
		i++;
		j++;
	}
	(*var_value)[1][j] = '\0';
}

void		cpy_envp(t_main **vars, char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if ((*vars)->temp_env == NULL)
		(*vars)->temp_env = (char **)malloc(sizeof(char*) * (i + 1));
	else
		return ;
	i = 0;
	while (env[i] != NULL)
	{
		(*vars)->temp_env[i] = ft_strdup(env[i]);
		i++;
	}
	(*vars)->temp_env[i] = NULL;
}

void		set_var_env(t_main **vars, t_paths **var)
{
	int		posy;
	int		cnt_env;
	int		i;
	int		j;
	int		alpha;
	int		size_new_line;
	char	**var_value;
	char	**new_env;
	char 	*temp;

	posy = 0;
	cnt_env = 0;
	size_new_line = 0;
	i = 0;
	j = 0;
	alpha = 0;
	var_value = (char **)malloc(sizeof(char*) * 3);
	var_value[2] = NULL;
	get_var_value(&var_value, vars);
	cpy_envp(vars, (*vars)->env);
	temp = ft_strjoin(var_value[0], var_value[1]);
	if ((posy = find_var_env(vars, var_value)) == -1)
	{
		while ((*vars)->env[i] != NULL)
			i++;
		cnt_env = i;
		i = 0;
		new_env = (char**)malloc(sizeof(char*) * (cnt_env + 2)); // 3 original
		while ((*vars)->env[i] != NULL)
		{
			new_env[i] = ((*vars)->env)[i];
			i++;
		}
		new_env[i] = temp;
		new_env[i + 1] = NULL;
		i = 0;
		while (new_env[i] != NULL)
		{
			printf("%s\n", new_env[i]);
			i++;
		}
	}
	else if (ft_strcmp(var_value[0], "PATH=") == 0 || ft_strcmp(var_value[0], "PWD=") == 0 || ft_strcmp(var_value[0], "OLDPWD=") == 0)
		ft_putstr_fd("This variable cannot be altered\n", 2);
	else
	{
		free((*vars)->env[posy]);
		(*vars)->env[posy] = NULL;
		(*vars)->env[posy] = temp;
	}
	i = 0;
/*	while ((*vars)->split_args[i] != NULL) // must free split_args // must free command must free line must redo line
	{
		printf("%s\n", (*vars)->split_args[i]);
		i++;
	}*/
	while ((*vars)->line[i] != '\0')
	{
		if ((*vars)->line[i] != ' ' && (*vars)->line[i] != '	')
			alpha++;
		if (alpha == 3)
			break ;
		while ((*vars)->line[i] != ' ' && (*vars)->line[i] != '	' && (*vars)->line[i] != '\0')
			i++;
		while (((*vars)->line[i] == ' ' || (*vars)->line[i] == '	') && (*vars)->line[i] != '\0')
			i++;
	}
	printf("%c\n", (*vars)->line[i]);
	printf("%d\n", i);
	size_new_line = ft_strlen((*vars)->line) - i;
	temp = (*vars)->line;
	if (size_new_line != 0)
	{
		(*vars)->line = (char*)malloc(sizeof(char) * (size_new_line + 1));
		while (temp[i] != '\0')
		{
			(*vars)->line[j] = temp[i];
			i++;
			j++;
		}
		(*vars)->line[j] = '\0';
//		while ((*vars)->line[j] != '\0')
//		{
//			(*vars)->line[j] = '\0';
//			j++;
//		}
		free_temp(&temp);
		free_temp(&((*vars)->command));
		free((*vars)->split_args);
		(*vars)->split_args = NULL;
		temp = NULL;
		ft_split_args(vars);
		while_funcs(vars, var);
	}
	else
	{
		free((*vars)->line);
		(*vars)->line = NULL;
	}
//	free_temp(&temp);
//	free_temp(&((*vars)->command));
//	free((*vars)->split_args);
//	(*vars)->split_args = NULL;
//	temp = NULL;
//	printf("%s\n", (*vars)->line);
}

void		set_var(t_main **vars)
{
	int		posy;
	int		cnt_env;
	int		i;
	char	**temp_env;

	i = 0;
	posy = 0;
	cnt_env = 0;
	while (((*vars)->env)[i] != NULL)
		i++;
	cnt_env = i;
	i = 0;
	if ((posy = find_var(vars)) == -1)
	{
		temp_env = (char**)malloc(sizeof(char*) * (cnt_env + 2));
		while ((*vars)->env[i] != NULL)
		{
			temp_env[i] = ft_strdup((*vars)->env[i]);
			i++;
		}
		temp_env[i] = ft_strjoin((*vars)->split_args[1], "=");
		temp_env[i] = ft_strjoin(temp_env[i] , (*vars)->split_args[2]);
		temp_env[i + 1] = NULL;
		i = 0;
		if ((*vars)->env != NULL)
		{
			free((*vars)->env);
			(*vars)->env = NULL;
		}
		(*vars)->env = temp_env;
		ft_putstr_fd("Variable not found\n", 2);
	}
	else if (ft_strcmp((*vars)->split_args[1], "PATH=") == 0 || ft_strcmp((*vars)->split_args[1], "PWD=") == 0 || ft_strcmp((*vars)->split_args[1], "OLDPWD=") == 0)
	{
		ft_putstr_fd("This variable cannot be altered\n", 2);
	}
	else
	{
		free(((*vars)->env)[posy]);
		(*vars)->env[posy] = NULL;
		(*vars)->env[posy] = ft_strjoin((*vars)->split_args[1], (*vars)->split_args[2]);
	}
}
