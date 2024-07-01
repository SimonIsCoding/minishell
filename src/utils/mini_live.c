/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:52:42 by asiercara         #+#    #+#             */
/*   Updated: 2024/06/25 15:08:27 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_live(t_mini *mini)
{
	if (mini->error_code != 0)
		mini->line = readline("\x1b[31mshelldone >\x1b[0m");
	else
		mini->line = readline("\x1b[32mshelldone >\x1b[0m");
	clear_line(mini);
	if (mini->line == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (mini->line[0] == '\0')
		mini_reset(mini);
	if (!check_quotes_is_married(mini->line))
		print_error(mini, 1);
	add_history(mini->line);
	if (!lexer_tokenizer(mini))
		print_error(mini, 1);
	parser(mini);
	pre_executor(mini);
	mini_reset(mini);
	return (0);
}

void	init_mini(t_mini *mini, char **env)
{
	mini->line = NULL;
	mini->lexer = NULL;
	mini->cmd = NULL;
	mini->flag_hdoc = 0;
	mini->flag_reset = 0;
	mini->pid = NULL;
	mini->original_env = env;
	mini->home_env = get_value_from_env(mini, "HOME");
	mini->inside_cmd = 0;
	mini->inside_hdoc = 0;
	mini->outside_hdoc = 0;
	init_signals();
}

static void	lst_clear_cmds_helper(t_cmd **cmd, t_cmd *tmp_cmd)
{
	t_lexer	*tmp_redirects;

	while (*cmd)
	{
		tmp_cmd = (*cmd)->next;
		tmp_redirects = (*cmd)->redirections;
		lexer_clear(&tmp_redirects);
		if ((*cmd)->hdoc_filename)
		{
			if (unlink((*cmd)->hdoc_filename) == -1)
				print_error(NULL, 12);
			free((*cmd)->hdoc_filename);
		}
		if ((*cmd)->str)
			free_cmd_line((*cmd)->str);
		free(*cmd);
		*cmd = tmp_cmd;
	}
}

void	lst_clear_cmds(t_cmd **cmd)
{
	t_cmd	*tmp_cmd;

	if (!*cmd)
		return ;
	tmp_cmd = *cmd;
	while (tmp_cmd && tmp_cmd->previous)
	{
		tmp_cmd = tmp_cmd->previous;
	}
	*cmd = tmp_cmd;
	lst_clear_cmds_helper(cmd, tmp_cmd);
}

// function for free all and call another time mini_live for create a loop
int	mini_reset(t_mini *mini)
{
	if (mini->cmd)
		lst_clear_cmds(&mini->cmd);
	mini->cmd = NULL;
	if (mini->line)
		free(mini->line);
	if (mini->pid)
		free(mini->pid);
	init_mini(mini, mini->original_env);
	mini_live(mini);
	return (0);
}
