/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:25:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/13 13:07:16 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	s_builtin
{
	char				*key;//the name of the variable in env
	char				*value;
	int					index;
//	int					checker;//to check if the builtin is ENV or EXPORT
	struct s_builtin	*next;
}				t_builtin;//for ENV and EXPORT builtins

int	ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *str);

//the str refers to the variable to remove (for example PWD)
void	unset_builtin(t_builtin **head, char *str)
{
	t_builtin	*current;
	t_builtin	*previous;

	previous = NULL;
	current = *head;
	if (*head == NULL)
		return ;
	while (current)
	{
		if (ft_strlen(current->key) == ft_strlen(str) &&
			ft_strcmp_simple(current->key, str) == 0)
		{
			if (previous == NULL)
			{
				*head = current->next;
				return ;
			}
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
