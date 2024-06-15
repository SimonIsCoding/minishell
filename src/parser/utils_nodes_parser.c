/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:30:58 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/13 20:27:51 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char **str, int num_redirections, t_lexer *redirections)
{
	t_cmd	*new_cmd_node;

	new_cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd_node)
		return (0);
	new_cmd_node->str = str;
	new_cmd_node->builtin = prepare_builtin(str[0]);
	new_cmd_node->hdoc_filename = NULL;
	new_cmd_node->num_redirections = num_redirections;
	new_cmd_node->redirections = redirections;
	new_cmd_node->next = NULL;
	new_cmd_node->previous = NULL;
	return (new_cmd_node);
}

void	ft_node_add_back_parser(t_cmd **lst, t_cmd *node)
{
	t_cmd	*tmp;

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

int	lst_size_cmd(t_mini *mini)
{
	t_cmd	*tmp;
	int		len;

	len = 1;
	tmp = mini->cmd;
	while (tmp->next)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	lst_clear_parser(t_cmd **lst)
{
	t_cmd	*tmp;

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
