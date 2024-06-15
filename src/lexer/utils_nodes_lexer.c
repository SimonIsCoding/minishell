/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:47:44 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/15 14:08:08 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_add_node(t_lexer **lexer_list, enum e_operator token, char *str)
{
	t_lexer	*node;

	node = ft_new_node(str, token);
	if (!node)
		return (0);
	ft_node_add_back(lexer_list, node);
	return (1);
}

t_lexer	*ft_new_node(char *str, int token)
{
	t_lexer				*new;
	static unsigned int	i = 0;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->str = str;
	new->num_node = i++;
	new->token = token;
	new->next = NULL;
	return (new);
}

void	ft_node_add_back(t_lexer **lst, t_lexer *node)
{
	t_lexer	*tmp;

	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	clear_one_node(t_lexer **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
}

void	del_first_node(t_lexer **lst)
{
	t_lexer	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	clear_one_node(&tmp);
}
