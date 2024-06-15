/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_builtin_nodes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:00:09 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/11 19:04:09 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_builtin(t_env_lst **lst)
{
	t_env_lst	*tmp;
	t_env_lst	*current;

	if (!lst | !*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		current = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = current;
	}
	*lst = NULL;
}

t_env_lst	*clear_one_node_env(t_env_lst **lst)
{
	if ((*lst)->key)
	{
		free((*lst)->key);
		(*lst)->key = NULL;
	}
	if ((*lst)->value)
	{
		free((*lst)->value);
		(*lst)->value = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	del_first_node_env(t_env_lst **lst)
{
	t_env_lst	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	clear_one_node_env(&tmp);
}

void	delone_node_env(int num_del, t_env_lst **lst)
{
	t_env_lst	*node;
	t_env_lst	*prev;
	t_env_lst	*start;

	start = *lst;
	node = start;
	if ((*lst)->index == num_del)
	{
		del_first_node_env(lst);
		return ;
	}
	while (node && node->index != num_del)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	clear_one_node_env(&node);
	*lst = start;
}
