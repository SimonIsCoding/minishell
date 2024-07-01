/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:41:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 16:25:10 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_parser(t_mini *mini)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = mini->cmd;
	while (tmp)
	{
		printf("1\n");
		printf("Node %d, str** = %s\n", i, tmp->str[0]);
		tmp = tmp->next;
		i++;
	}
}

// Initiate the parser structure, see in minishell.h.

t_parser	init_struct(t_lexer *lexer, t_mini *mini)
{
	t_parser	parser;

	parser.lexer = lexer;
	parser.redirections = NULL;
	parser.num_redirections = 0;
	parser.mini = mini;
	return (parser);
}

t_cmd	*create_cmd(t_mini *mini, t_parser *parser)
{
	char	**str;
	int		i;
	int		num_args;
	t_lexer	*tmp;

	redirections(mini, parser);
	num_args = count_args(parser->lexer);
	str = ft_calloc((num_args + 1), sizeof(char *));
	if (!str)
		print_error(parser->mini, 2);
	i = 0;
	tmp = parser->lexer;
	while (i < num_args)
	{
		if (tmp->str)
		{
			str[i] = ft_strdup(tmp->str);
			delone_node(tmp->num_node, &parser->lexer);
			tmp = parser->lexer;
		}
		i++;
	}
	return (new_cmd(str, parser->num_redirections, parser->redirections));
}

int	parser(t_mini *mini)
{
	t_parser	parser;
	t_cmd		*new;

	mini->cmd = NULL;
	count_pipes(mini);
	if (mini->lexer->token == PIPE)
	{
		token_error(mini, PIPE);
		return (EXIT_FAILURE);
	}
	while (mini->lexer)
	{
		if (mini->lexer && mini->lexer->token == PIPE)
			delone_node(mini->lexer->num_node, &mini->lexer);
		if (check_line(mini))
			return (EXIT_FAILURE);
		parser = init_struct(mini->lexer, mini);
		new = create_cmd(mini, &parser);
		if (!new)
			print_error(mini, 0);
		ft_node_add_back_parser(&mini->cmd, new);
		mini->lexer = parser.lexer;
	}
	return (EXIT_SUCCESS);
}
