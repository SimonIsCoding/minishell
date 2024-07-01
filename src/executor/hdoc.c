/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:52 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 16:17:35 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_exists_hdoc(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;
	int		error;

	tmp = cmd->redirections;
	check_max_hdoc(mini, tmp);
	error = EXIT_SUCCESS;
	while (tmp)
	{
		if (tmp->token == HDOC)
		{
			if (cmd->hdoc_filename)
				free(cmd->hdoc_filename);
			cmd->hdoc_filename = generate_filename();
			error = check_eof(mini, tmp, cmd->hdoc_filename);
			if (error)
			{
				mini->error_code = error;
				mini_reset(mini);
			}
		}
		tmp = tmp->next;
	}
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
	if ((str[0] == '\"' && str[len] == '\"')
		|| (str[0] == '\'' && str[len] == '\''))
	{
		remove_eof_quotes(redir);
		quotes = true;
	}
	else
		quotes = false;
	mini->outside_hdoc = 0;
	mini->inside_hdoc = 1;
	error = open_save_hdoc(mini, redir, hdoc_filename, quotes);
	mini->inside_hdoc = 0;
	mini->flag_hdoc = 1;
	return (error);
}

static void	aux_open_save_hdoc(char *line, char *eof)
{
	if (line != NULL)
		free(line);
	else if (line == NULL)
	{
		fprintf(stderr, "bash: warning: here-document at last line delimited ");
		fprintf(stderr, "by end-of-file (wanted `%s')\n", eof);
	}
}

static int	outside_hdoc(t_mini *mini)
{
	mini->error_code = g_status + 128;
	return (130);
}

int	open_save_hdoc(t_mini *mini, t_lexer *redir, char *hdoc_filename,
		bool quotes)
{
	char			*line;
	int				fd;

	set_up_signals_hdoc();
	fd = open(hdoc_filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	line = readline(">");
	while (line != NULL && ft_strcmp_simple(redir->str, line) != 0
		&& mini->outside_hdoc == 0)
	{
		if (g_status == 2)
		{
			mini->outside_hdoc = 1;
			break ;
		}
		if (quotes == false)
			line = expand_str_line(mini, line);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline(">");
	}
	aux_open_save_hdoc(line, redir->str);
	close(fd);
	if (mini->outside_hdoc == 1)
		return (outside_hdoc(mini));
	return (EXIT_SUCCESS);
}
