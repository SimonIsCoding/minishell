/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_lst_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:32:02 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/13 18:09:04 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back_builtin(t_builtin **lst, t_builtin *new)
{
	t_builtin	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

//to test
void	print_list(t_builtin **lst_env)
{
	int	i;

	i = 1;
	printf("list memory adress [%p]\n", lst_env);
	while (*lst_env)
	{
		printf("--------node%i--------\n", i);
		printf("memory adress [%p]\n", *lst_env);
		printf("key: %s\n", (*lst_env)->key);
		printf("value: %s\n", (*lst_env)->value);
		printf("index: %i\n", (*lst_env)->index);
		i++;
		*lst_env = (*lst_env)->next;
	}
}

int	ft_lstsize_builtin(t_builtin *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/*void	ft_lstclear_builtin(t_builtin **lst)
{
	t_builtin	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	lst = NULL;
}*/

void	ft_lstclear_builtin(t_builtin **lst)
{
	t_builtin	*tmp;
	t_builtin	*current;

	//tmp = lst;
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

t_builtin	*clear_one_node_env(t_builtin **lst)
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

void	del_first_node_env(t_builtin **lst)
{
	t_builtin	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	clear_one_node_env(&tmp);
}

void delone_node_env(int num_del, t_builtin **lst)
{
	t_builtin *node;
	t_builtin *prev;
	t_builtin *start;

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