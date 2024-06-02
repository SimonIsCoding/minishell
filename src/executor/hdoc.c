/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:52 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/18 17:23:54 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_exists_hdoc(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;
	int		error;
	int		count;

	tmp = cmd->redirections;
	error = EXIT_SUCCESS;
	count = 0;
	while (cmd->redirections)
	{
		if (count >= 16)
			break ;
			//bash: maximum here-document count exceeded == exit (sale de bash)
		if (cmd->redirections->token == HDOC)
		{
			count++;
			if (cmd->hdoc_filename)
				free(cmd->hdoc_filename);
			cmd->hdoc_filename = generate_filename();
			error = check_eof(mini, mini->cmd->redirections, cmd->hdoc_filename);
			if (error) // error == exitFAILURE
			{
				g_global_var.error_code = error;
				mini_reset(mini);
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = tmp;
	return (error);
}

int	check_eof(t_mini *mini, t_lexer *redir, char *hdoc_filename)
{
	int			error;
	char		*str;
	int			len;
	bool		quotes;

	error = EXIT_SUCCESS;
	str = redir->str;
	len = ft_strlen(str) - 1;
	// hacer un strchr que encuentre la pareja, si hay alguna comilla no se expande
	// hacer un check quotes, que sea par
	if ((str[0] == '\"' && str[len] == '\"')
		|| (str[0] == '\'' && str[len] == '\''))
	{
		remove_eof_quotes(redir);
		quotes = true;
	}
	else
		quotes = false;
	g_global_var.outside_hdoc = 0;
	g_global_var.inside_hdoc = 1;
	error = open_save_hdoc(redir, hdoc_filename, quotes);
	g_global_var.inside_hdoc = 0;
	mini->flag_hdoc = 1;
	return (error);
}

int	open_save_hdoc(t_lexer *redir, char *hdoc_filename, bool quotes)
{
	char	*line;
	int		fd;

	fd = open(hdoc_filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	line = readline(">");
	while (line != NULL && ft_strcmp_simple(redir->str, line) != 0 && g_global_var.outside_hdoc == 0)
	{
		if (quotes == false)
			ft_putendl_fd(line, fd);
		//	line = expand_line(mini, line);
		else
			ft_putendl_fd(line, fd);
		free(line);
		line = readline(">");
	}
	free(line);
	if (g_global_var.outside_hdoc == 1)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}
