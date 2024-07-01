/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:22:39 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/19 16:50:13 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function assigns a value to that operator as desired. The only 
// different ones are '>>' and '<<', so we create a special case for 
// each of them. If not, we assume it's '|', '<', or '>'.
//And add it as a new node.

int	put_operator(char *str, int i, t_lexer **lst)
{
	enum e_operator	operator;

	operator = check_operator(str[i]);
	if (operator == RED_IN && check_operator(str[i + 1]) == RED_IN)
	{
		operator = HDOC;
		if (!list_add_node(lst, operator, NULL))
			return (-1);
		return (2);
	}
	else if (operator == RED_OUT && check_operator(str[i + 1]) == RED_OUT)
	{
		operator = RED_OUT_APP;
		if (!list_add_node(lst, operator, NULL))
			return (-1);
		return (2);
	}
	else if (operator)
	{
		if (!list_add_node(lst, operator, NULL))
			return (-1);
		return (1);
	}
	return (0);
}

// Identify the word, trim it from spaces, and add it as a new node.
// Also, identify quotes.

int	put_word(char *str, int i, t_lexer **lst)
{
	int		j;
	char	quote;

	j = 0;
	quote = 0;
	while (str[i + j] && (quote || check_operator(str[i + j]) == 0))
	{
		if (str[i + j] == 34 || str[i + j] == 39)
		{
			if (quote == 0)
				quote = str[i + j];
			else if (quote == str[i + j])
				quote = 0;
		}
		else if (str[i + j] == ' ' && quote == 0)
			break ;
		j++;
	}
	if (!list_add_node(lst, 0, ft_substr(str, i, j)))
		return (-1);
	return (j);
}

// This function separate the command line, separated between operator and word.
int	lexer_tokenizer(t_mini *mini)
{
	int	i;
	int	diff;

	i = 0;
	while (mini->line[i])
	{
		diff = 0;
		while (mini->line[i] == 32 || (mini->line[i] > 8 && mini->line[i] < 14))
			i++;
		if (check_operator(mini->line[i]))
			diff = put_operator(mini->line, i, &mini->lexer);
		else
			diff = put_word(mini->line, i, &mini->lexer);
		if (diff < 0)
			return (0);
		i += diff;
	}
	return (1);
}
