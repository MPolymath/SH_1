/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 19:03:37 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/19 18:16:35 by mdiouf           ###   ########.fr       */
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
	node->right = NULL;
	return (node);
}

void	create_tree(char ***split_commands)
{
	int	i;
	int	j;
	t_tree *root;
	t_tree *start_child;
	t_tree *temp;

	i = 0;
	j = 0;
	temp = NULL;
	if ((root = ft_new_node(NULL)) == NULL)
	{
		ft_putstr_fd("Malloc returned NULL\n", 2);
		exit(0);
	}
	while ((*split_commands)[i] != NULL)
	{
		if (root->child == 0)
		{
			start_child = ft_new_node(&((*split_commands)[i]));
			root->child += 1;
		}
		else
		{
			temp = start_child;
			printf("root_child: %d\n", root->child);
			printf("j: %d\n", j);
			while (j != (root->child - 1))
			{
				temp = temp->right;
				j++;
			}
			j = 0;
			temp->right = ft_new_node(&((*split_commands)[i]));
			if (root->child == 1)
			{
				temp->left = temp->right;
				temp->right->right = start_child;
				temp->right->left = temp;
			}
			else
			{
				start_child->left = temp->right;
				temp->right->right = start_child;
				temp->right->left = temp;
			}
			root->child += 1;
		}
		i++;
	}
	temp = start_child;
	i = 0;
	while (i != root->child)
	{
		printf("Test7\n");
		printf("Command: %s\n", temp->cmd);
		temp = temp->right;
		i++;
	}
	// make tree
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
