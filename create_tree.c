/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 19:03:37 by mdiouf            #+#    #+#             */
/*   Updated: 2014/11/18 19:08:04 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Structure
int	child; // number of children for the starting root pointer; all leafs have 0 only root has a number;
left struct;  // child 1 is only left struct of root tree; rest are right children;
right struct; // this is a chained list of stuctures going to the right ending with NULL all of them are children
 */
