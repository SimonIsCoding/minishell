/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:27:35 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/18 16:58:28 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_redirections(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;

	tmp = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == RED_IN)
			put_infile(mini, cmd->redirections->str);
		else if (cmd->redirections->token == HDOC)
			put_infile(mini, cmd->hdoc_filename);
		else if (cmd->redirections->token == RED_OUT
			|| cmd->redirections->token == RED_OUT_APP)
			put_outfile(mini, cmd->redirections, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = tmp;
	return (EXIT_SUCCESS);
}

int	put_infile(t_mini *mini, char *filename)
{
	int	fd_in;

	fd_in = open(filename, O_RDONLY);
	if (fd_in == -1)
		print_error(mini, IN_ERROR);
	if (fd_in > 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			print_error(mini, DUP2_ERROR);
		close(fd_in);
	}
	return (EXIT_SUCCESS);
}

int	put_outfile(t_mini *mini, t_lexer *lex, char *filename)
{
	int	fd_out;

	fd_out = 0;
	if (lex->token == RED_OUT)
		fd_out = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (lex->token == RED_OUT_APP)
		fd_out = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd_out == -1)
		print_error(mini, OUT_ERROR);
	if (fd_out > 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			print_error(mini, DUP2_ERROR);
		close(fd_out);
	}
	return (EXIT_SUCCESS);
}
