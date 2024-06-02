/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:30:58 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/16 15:14:27 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *new_cmd(char **str, int num_redirections, t_lexer *redirections)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
   	if (!new)
		return (0);
	new->str = str;
   	new->builtin = prepare_builtin(str[0]); // find_builtin(str[0]) works well
   	new->hdoc_filename = NULL;
	new->num_redirections = num_redirections;
   	new->redirections = redirections;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	ft_node_add_back_parser(t_cmd **lst, t_cmd *node)
{
	t_cmd *tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->previous = tmp;
}

int		lst_size_cmd(t_mini *mini)
{
	int	len;
	t_cmd	*tmp;

	len = 1;
	tmp = mini->cmd;
	while (tmp->next != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

// no hay malloc en parser!
void	lst_clear_parser(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp =  (*lst)->next;
		free(lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_cmd	*clear_one_cmd(t_cmd **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	del_first_cmd(t_cmd **lst)
{
	t_cmd	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	clear_one_cmd(&tmp);
}