/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 19:03:37 by mdiouf            #+#    #+#             */
/*   Updated: 2014/12/08 20:20:10 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

t_tree		*ft_new_node(char **command)
{
	t_tree	*node;

	if ((node = (t_tree*)malloc(sizeof(t_tree))) == NULL)
	{
		ft_putstr_fd("Malloc returned NULL\n", 2);
		exit(0);
	}
	node->child = 0;
	if (command == NULL)
		node->cmd = NULL;
	else
		node->cmd = *command;
	node->left = NULL;
	node->left_two = NULL;
	node->right = NULL;
	node->right_next = NULL;
	node->right_two = NULL;
	return (node);
}

void		create_root(char ***split_commands, t_ptr **var, int i)
{
	(*var)->start_child = ft_new_node(&((*split_commands)[i]));
	((*var)->root)->child += 1;
	((*var)->start_child)->left = (*var)->start_child;
	((*var)->start_child)->right = (*var)->start_child;
}

void		fill_tree(char ***split_commands, t_ptr **var, int *j, int i)
{
	(*var)->temp = (*var)->start_child;
	while (*j != (((*var)->root)->child - 1))
	{
		(*var)->temp = ((*var)->temp)->right;
		(*j)++;
	}
	*j = 0;
	((*var)->temp)->right = ft_new_node(&((*split_commands)[i]));
	if (((*var)->root)->child == 1)
	{
		((*var)->temp)->left = ((*var)->temp)->right;
		((*var)->temp)->right->right = (*var)->start_child;
		((*var)->temp)->right->left = (*var)->temp;
	}
	else
	{
		((*var)->start_child)->left = ((*var)->temp)->right;
		((*var)->temp)->right->right = (*var)->start_child;
		((*var)->temp)->right->left = (*var)->temp;
	}
	((*var)->root)->child += 1;
}

void		circular_list_print(t_ptr **var)
{
	int		i;

	i = 0;
	printf("root child %d\n", ((*var)->root)->child); // circular list printing
	(*var)->temp = (*var)->start_child;
	i = 0;
	while (i != ((*var)->root)->child)
	{
		printf("temp->cmd: %s\n", ((*var)->temp)->cmd);
		(*var)->temp = ((*var)->temp)->right;
		i++;
	}
}

void		bin_tree_body(t_ptr **var, int **j, int i)
{
	if (((*var)->root)->left == NULL)
	{
		((*var)->root)->left = (*var)->temp;
		((*var)->temp)->left_two = ((*var)->temp)->left;
		if (((*var)->root)->child > 2)
			((*var)->temp)->right_two = ((*var)->temp)->right;
	}
	else if (((*var)->root)->right_next == NULL)
	{
		((*var)->root)->right_next = (*var)->temp;
		(**j)++;
		if (((*var)->root)->child > 4)
			((*var)->temp)->right_two = ((*var)->temp)->right;
	}
	else
	{
		(*var)->temp2 = ((*var)->root)->right_next;
		while (((*var)->temp2)->right_next != NULL)
			(*var)->temp2 = ((*var)->temp2)->right_next;
		((*var)->temp2)->right_next = (*var)->temp;
		if (i + 1 != ((*var)->root)->child)
			((*var)->temp)->right_two = ((*var)->temp)->right;
		(**j)++;
	}
}

void		count_splits(char ***split_commands, int *splits, t_ptr **var)
{
	int		i;

	(*var)->temp = ((*var)->root)->right; // counting amounts of | ;
	i = 0;
	while ((*split_commands)[i] != NULL)
	{
		if (ft_strcmp((*split_commands)[i], ";") == 0 ||
			ft_strcmp((*split_commands)[i], "|") == 0)
			(*splits)++;
		i++;
	}
}

void		print_tree(t_ptr **var)
{
	int		i;

	i = 0;
	(*var)->temp = (*var)->root; // printing finished tree
	printf("root->left: %s\n", ((*var)->temp)->left->cmd);
	if (((*var)->root)->child > 1)
		printf("left: %s\n", ((*var)->temp)->left->left_two->cmd);
	if (((*var)->root)->child > 2)
		printf("right: %s\n", ((*var)->temp)->left->right_two->cmd);
	i = 0;
	while (((*var)->temp)->right_next != NULL)
	{
		(*var)->temp = ((*var)->temp)->right_next;
		printf("root->right: %s\n", ((*var)->temp)->cmd);
		if (((*var)->temp)->right_two != NULL)
			printf("right: %s\n", ((*var)->temp)->right_two->cmd);
		i++;
	}
}

void		mk_bin_tree(t_ptr **var, int *j, int *i)
{
	(*var)->temp = (*var)->start_child; // binary tree creation
	(*var)->temp2 = ((*var)->root)->right;
	*i = 0;
	*j = 0;
	while (*i != ((*var)->root)->child)
	{
		if (((*var)->temp)->cmd != NULL &&
			(ft_strcmp(((*var)->temp)->cmd, ";") == 0 ||
			ft_strcmp(((*var)->temp)->cmd, "|") == 0))
			bin_tree_body(var, &j, *i);
		else if (((*var)->root)->child == 1)
			((*var)->root)->left = (*var)->temp;
		(*var)->temp = ((*var)->temp)->right;
		(*i)++;
	}
}

int			tree_error(char ***split_commands, int i, t_ptr **var)
{
	if ((*split_commands)[i] == NULL)
	{
		exit(0);
		return (-1);
	}
	if (((*var)->root = ft_new_node(NULL)) == NULL)
	{
		ft_putstr_fd("Malloc returned NULL\n", 2);
		exit(0);
	}
	return (0);
}

void		create_tree(char ***split_commands, t_ptr *var)
{
	int		i;
	int		j;
	int		splits;

	i = 0;
	j = 0;
	splits = 0;
	var->temp = NULL;
	if (tree_error(split_commands, i, &var) == -1)
		return ;
	while ((*split_commands)[i] != NULL)
	{
		if ((var->root)->child == 0)
			create_root(split_commands, &var, i);
		else
			fill_tree(split_commands, &var, &j, i);
		i++;
		printf("i: %d\n", i);
	}
	circular_list_print(&var);
	mk_bin_tree(&var, &j, &i);
	count_splits(split_commands, &splits, &var);
	print_tree(&var);
}
