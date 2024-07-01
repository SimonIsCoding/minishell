/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:41 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:07:06 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_mini *mini)
{
	int	fds[2];
	int	fd_in;

	mini->pid = ft_calloc((mini->pipes + 2), sizeof(int));
	if (!mini->pid)
		print_error(mini, MALLOC_ERROR);
	fd_in = STDIN_FILENO;
	while (mini->cmd)
	{
		run_expander(mini, mini->cmd);
		if (mini->cmd->next && pipe(fds) == -1)
			print_error(mini, PIPE_ERROR);
		check_if_exists_hdoc(mini, mini->cmd);
		ft_fork(mini, mini->cmd, fds, fd_in);
		if (mini->cmd->previous != NULL)
			close(fd_in);
		fd_in = check_next_fd_in(mini, mini->cmd, fds);
		if (mini->cmd->next)
			mini->cmd = mini->cmd->next;
		else
			break ;
	}
	wait_pipes(mini, mini->pid);
	return (0);
}

int	ft_fork(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in)
{
	static unsigned int	index = 0;

	if (mini->flag_reset == 0)
	{
		index = 0;
		mini->flag_reset = 1;
	}
	mini->pid[index] = fork();
	if (mini->pid[index] == -1)
		print_error(mini, FORK_ERROR);
	if (mini->pid[index] == 0)
		ft_dup(mini, cmd, fds, fd_in);
	index++;
	close(fds[1]);
	return (EXIT_SUCCESS);
}

void	ft_dup(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in)
{
	if (cmd->previous)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			print_error(mini, DUP2_ERROR);
	}
	close(fds[0]);
	if (cmd->next)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			print_error(mini, DUP2_ERROR);
	}
	close(fds[1]);
	if (cmd->previous)
		close(fd_in);
	ft_exec_cmd(mini, cmd);
}

int	check_next_fd_in(t_mini *mini, t_cmd *cmd, int fds[2])
{
	int	fd_in;

	fd_in = 0;
	if (mini->flag_hdoc == 1)
	{
		mini->flag_hdoc = 0;
		close(fds[0]);
		fd_in = open(cmd->hdoc_filename, 0644);
	}
	else
		fd_in = fds[0];
	return (fd_in);
}

void	wait_pipes(t_mini *mini, int *pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < mini->pipes)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		mini->error_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			mini->error_code = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			mini->error_code = 131;
	}
}
