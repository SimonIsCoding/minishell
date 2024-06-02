/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:47:44 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/06 20:38:51 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void delone_node(int num_del, t_lexer **lst)
{
	t_lexer *node;
	t_lexer *prev;
	t_lexer *start;

	start = *lst;
	node = start;
	if ((*lst)->num_node == num_del)
	{
		del_first_node(lst);
		return ;
	}
	while (node && node->num_node != num_del)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	clear_one_node(&node);
	*lst = start;
}*/

void delone_node(int num_del, t_lexer **lst)
{
    t_lexer *node;
    t_lexer *prev;

	node = *lst;
	prev = NULL;
    if (node && node->num_node == num_del)
	{
		//printf("FLAG 1\n");
        del_first_node(lst);
        return;
    }
    while (node && node->num_node != num_del)
	{
		//printf("FLAG 2\n");
        prev = node;
        node = node->next;
    }
    if (node) 
	{
        if (prev)
            prev->next = node->next;
		//printf("FLAG 3\n");
        clear_one_node(&node);
    }
}

void	lst_clear_lexer(t_lexer **lst)
{
	t_lexer *tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int		lst_size_lexer(t_mini *mini)
{
	int	len;
	t_lexer	*tmp;

	tmp = mini->lexer;
	len = 0;
	while (tmp->next)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
