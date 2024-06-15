/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:23:50 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/13 20:32:52 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function is responsible for creating the redirect node, identifying the
// operator and the string (filename or EOF), and removing those corresponding
// nodes from the lexer/tokenizer list, to free the set of nodes from the 
// simple command and leave only the command ready to be joined.

void	new_redirection(t_parser *parser, t_lexer *tmp)
{
	t_lexer	*node;
	int		num_node_delete;

	node = ft_new_node(ft_strdup(tmp->next->str), tmp->token);
	if (!node)
		return ;//print_error(mini, 2); //error malloc
	ft_node_add_back(&parser->redirections, node);
	parser->num_redirections++;
	num_node_delete = tmp->num_node;
	delone_node(num_node_delete, &parser->lexer);
	num_node_delete += 1;
	delone_node(num_node_delete, &parser->lexer);
}

// Begin redirections, shift the node until the redirect (making verifications),
// to then send it to new_redirection to create the node.

void	redirections(t_mini *mini, t_parser *parser)
{
	t_lexer	*tmp;

	tmp = parser->lexer;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
		return ;
	if (!tmp->next)
		print_error(mini, SINTAX_ERROR);
	if (tmp->next->token != 0)
		token_error(mini, tmp->next->token);
	if (tmp->token >= RED_IN && tmp->token <= RED_OUT_APP)
		new_redirection(parser, tmp);
	redirections(mini, parser);
}
