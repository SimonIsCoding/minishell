/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:41:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/29 17:44:53 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// printf final test struct

void	ft_print_parser(t_mini *mini)
{
	t_cmd	*tmp;
	//t_lexer			*tmp2;
	int	i = 0;
	int	len = lst_size_cmd(mini);

	printf("1111111111STRING : %s\n", mini->cmd->next->str[0]);
	tmp = mini->cmd;
	printf("LEN %d\n", len);
	//tmp2 = mini->simple_cmd->redirections;
	while (tmp)
	{
		printf("1\n");
		printf("Node %d, str** = %s;", i, tmp->str[0]);
		/*printf("Node %d, str** = %s;", i, tmp->str[1]);*/

		//if (tmp2->str)
		//	printf("redirections str = %s, operator = %d", tmp2->str,
		//		tmp2->token);
		tmp = tmp->next;
		//tmp2 = tmp2->next;
		printf("\n");
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
	//static int	flag = 0;
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
	// !! siguientes dos lineas son para mac m2 !!!
	/*if (flag == 0)
	{
		mini->cmd = mini->cmd->next;
		mini->cmd->previous = NULL;
		flag = 1;
	}*/
	return (EXIT_SUCCESS);
}
