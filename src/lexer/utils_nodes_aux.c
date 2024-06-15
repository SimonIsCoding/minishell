/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils_nodes_aux.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: simarcha <simarcha@student.42barcelona.	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/06 20:47:44 by anovio-c		  #+#	#+#			 */
/*   Updated: 2024/06/15 14:04:25 by simarcha		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	delone_node(int num_del, t_lexer **lst)
{
	t_lexer	*node;
	t_lexer	*prev;

	node = *lst;
	prev = NULL;
	if (node && node->num_node == num_del)
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
	{
		if (prev)
			prev->next = node->next;
		clear_one_node(&node);
	}
}

void	lst_clear_lexer(t_lexer **lst)
{
	t_lexer	*tmp;

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

int	lst_size_lexer(t_mini *mini)
{
	int		len;
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

void	lexer_clear(t_lexer **list)
{
	t_lexer	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->str)
			free((*list)->str);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}
