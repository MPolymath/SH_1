/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 19:03:37 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/22 02:12:57 by mdiouf           ###   ########.fr       */
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

void	create_tree(char ***split_commands)
{
	int	i;
	int	j;
	int	splits;
	t_ptr	var;

// circular list creation
	i = 0;
	j = 0;
	splits = 0;
	var.temp = NULL;
	if ((*split_commands)[i] == NULL)
		return ;
	if ((var.root = ft_new_node(NULL)) == NULL)
	{
		ft_putstr_fd("Malloc returned NULL\n", 2);
		exit(0);
	}
	while ((*split_commands)[i] != NULL)
	{
		if ((var.root)->child == 0)
		{
			var.start_child = ft_new_node(&((*split_commands)[i]));
			(var.root)->child += 1;
			(var.start_child)->left = var.start_child; // test
			(var.start_child)->right = var.start_child; // test
		}
		else
		{
			var.temp = var.start_child;
			while (j != ((var.root)->child - 1))
			{
				var.temp = (var.temp)->right;
				j++;
			}
			j = 0;
			(var.temp)->right = ft_new_node(&((*split_commands)[i]));
			if ((var.root)->child == 1)
			{
				(var.temp)->left = (var.temp)->right;
				(var.temp)->right->right = var.start_child;
				(var.temp)->right->left = var.temp;
			}
			else
			{
				(var.start_child)->left = (var.temp)->right;
				(var.temp)->right->right = var.start_child;
				(var.temp)->right->left = var.temp;
			}
			(var.root)->child += 1;
		}
		i++;
		printf("i: %d\n", i);
	}
// circular list printing
	printf("root child %d\n", (var.root)->child);
	var.temp = var.start_child;
	i = 0;
	while (i != (var.root)->child)
	{
		printf("temp->cmd: %s\n", (var.temp)->cmd);
		var.temp = (var.temp)->right;
		i++;
	}
// binary tree creation
	var.temp = var.start_child;
	var.temp2 = (var.root)->right;
	i = 0;
	j = 0;
	while (i != (var.root)->child)
	{
		if ((var.temp)->cmd != NULL && (ft_strcmp((var.temp)->cmd, ";") == 0 || ft_strcmp((var.temp)->cmd, "|") == 0))
		{
			if ((var.root)->left == NULL)
			{
				(var.root)->left = var.temp;
				(var.temp)->left_two = (var.temp)->left;
				if ((var.root)->child > 2) // test
					(var.temp)->right_two = (var.temp)->right;
			}
			else if ((var.root)->right_next == NULL)
			{
				(var.root)->right_next = var.temp;
				j++;
				if ((var.root)->child > 4) // test
					(var.temp)->right_two = (var.temp)->right;
			}
			else
			{
				var.temp2 = (var.root)->right_next;
				while ((var.temp2)->right_next != NULL)
					var.temp2 = (var.temp2)->right_next;
				(var.temp2)->right_next = var.temp;
				if (i + 1 != (var.root)->child)
					(var.temp)->right_two = (var.temp)->right;
				j++;
			}
		}
		else if ((var.root)->child == 1)
			(var.root)->left = var.temp;
		var.temp = (var.temp)->right;
		i++;
	}
// counting amounts of | ;
	var.temp = (var.root)->right;
	i = 0;
	while ((*split_commands)[i] != NULL)
	{
		if (ft_strcmp((*split_commands)[i], ";") == 0 || ft_strcmp((*split_commands)[i], "|") == 0)
			splits++;
		i++;
	}
	//tree structure a circular list is made with different commands
	// with left and right nodes;
	// right_two is used only for right_next nodes (; or |) and constitutes argument linked to it
	// only node of right_next type (kinda) has the same proportions but has a left and right lower
	// leaft and that is root->left

// printing finished tree
	var.temp = var.root;
	printf("root->left: %s\n", (var.temp)->left->cmd);
	if ((var.root)->child > 1)
		printf("left: %s\n", (var.temp)->left->left_two->cmd);
	if ((var.root)->child > 2)
		printf("right: %s\n", (var.temp)->left->right_two->cmd);
	i = 0;
	while ((var.temp)->right_next != NULL)
	{
		var.temp = (var.temp)->right_next; //right2
		printf("root->right: %s\n", (var.temp)->cmd);
		if ((var.temp)->right_two != NULL)
			printf("right: %s\n", (var.temp)->right_two->cmd);
		i++;
	}
/*
	temp = start_child;
	while (i != root->child)
	{
		if (ft_strcmp(temp->cmd, ";") == 0 || ft_strcmp(temp->cmd, "|") == 0)
		{
// build tree;
			if (root->left == NULL)
			{
				ft_new_node(&((*split_commands)[i]));
			}
		}
		temp = temp->next;
		i++;
	}
*/
}
/*
Structure
int	child; // number of children for the starting root pointer; all leafs have 0 only root has a number;
left struct;  // child 1 is only left struct of root tree; rest are right children;
right struct; // this is a chained list of stuctures going to the right ending with NULL all of them are children
 */
