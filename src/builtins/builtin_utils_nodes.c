/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:32:02 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/11 19:01:09 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//for testing
/*void	print_list(t_builtin **lst_env)
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
}*/

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
