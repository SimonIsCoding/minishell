/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:12:39 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/13 21:09:34 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print(t_mini *mini)
{
	t_lexer	*tmp;
	//int	i = 1;
	//int	len = lst_size_lexer(mini);

	tmp = mini->lexer;
	while (tmp)
	{
		printf("Node %d, str = %s  token(ope) = %d\n", tmp->num_node, tmp->str, tmp->token);
		tmp = tmp->next;
	//	i++;
	}
}


// Function to clear spaces from the beginning, and from the end of the command line.

void	clear_line(t_mini *mini)
{
	char	*tmp;

	tmp = ft_strtrim(mini->line, " ");
	free(mini->line);
	mini->line = tmp;
}

// Traverse the string from that quote until the next character that
// matches the first one.

int	find_next_quote(char c, char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != c)
		j++;
	j++;
	//printf("valor j: %d\n", j);
	return (j);
}

// This function serves to check if that character is an operator.
// If so, we assign a value to that key (operator character).

int	check_operator(int c)
{
	int	i;
	int operator[3][2] = {
		{'|', PIPE},
		{'<', RED_IN},
		{'>', RED_OUT},
	};

	i = -1;
	while (++i <= 2)
		if (operator[i][0] == c)
			return (operator[i][1]);
	return (0);
}
