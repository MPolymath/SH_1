/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 20:44:16 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/16 20:57:54 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		init_set_var_env(t_var_env *bod)
{
	bod->posy = 0;
	bod->cnt_env = 0;
	bod->size_new_line = 0;
	bod->i = 0;
	bod->j = 0;
	bod->alpha = 0;
	bod->var_value = (char **)malloc(sizeof(char*) * 3);
	(bod->var_value)[2] = NULL;
}

void		var_found(t_main **vars, t_var_env **bod)
{
	while ((*vars)->env[(*bod)->i] != NULL)
		((*bod)->i)++;
	(*bod)->cnt_env = (*bod)->i;
	(*bod)->i = 0;
	(*bod)->new_env = (char**)malloc(sizeof(char*) * ((*bod)->cnt_env + 2));
	while ((*vars)->env[(*bod)->i] != NULL)
	{
		((*bod)->new_env)[(*bod)->i] = ((*vars)->env)[(*bod)->i];
		((*bod)->i)++;
	}
	((*bod)->new_env)[(*bod)->i] = (*bod)->temp;
	((*bod)->new_env)[((*bod)->i) + 1] = NULL;
	(*vars)->env = (*bod)->new_env;
}

int			exec_temp_command(t_main **vars, t_var_env *bod)
{
	if ((*vars)->line[bod->i] != ' ' && (*vars)->line[bod->i] != '	')
		(bod->alpha)++;
	if (bod->alpha == 3)
		return (1);
	while ((*vars)->line[bod->i] != ' ' && (*vars)->line[bod->i] != '	' &&
			(*vars)->line[bod->i] != '\0')
		(bod->i)++;
	while (((*vars)->line[bod->i] == ' ' || (*vars)->line[bod->i] == '	') &&
			(*vars)->line[bod->i] != '\0')
		(bod->i)++;
	return (0);
}

void		if_temp_command(t_main **vars, t_paths **var, t_var_env *bod)
{
	(*vars)->line = (char*)malloc(sizeof(char) * (bod->size_new_line + 1));
	while ((bod->temp)[bod->i] != '\0')
	{
		(*vars)->line[bod->j] = (bod->temp)[bod->i];
		(bod->i)++;
		(bod->j)++;
	}
	(*vars)->line[bod->j] = '\0';
	free_temp(&(bod->temp));
	free_temp(&((*vars)->command));
	free((*vars)->split_args);
	(*vars)->split_args = NULL;
	bod->temp = NULL;
	ft_split_args(vars);
	while_funcs(vars, var);
}

void		handle_temp_env(t_main **vars, t_var_env *bod)
{
	if ((bod->posy = find_var_env(vars, bod->var_value)) == -1)
		var_found(vars, &bod);
	else if (ft_strcmp((bod->var_value)[0], "PATH=") == 0 ||
			ft_strcmp((bod->var_value)[0], "PWD=") == 0 ||
			ft_strcmp((bod->var_value)[0], "OLDPWD=") == 0)
		ft_putstr_fd("This variable cannot be altered\n", 2);
	else
	{
		free((*vars)->env[bod->posy]);
		(*vars)->env[bod->posy] = NULL;
		(*vars)->env[bod->posy] = bod->temp;
	}
}
