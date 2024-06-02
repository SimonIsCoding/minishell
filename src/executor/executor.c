/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:41 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/18 17:48:45 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int executor(t_mini *mini)
{
	int	fds[2];
	int	fd_in;
	int	count_pipes;

	count_pipes = mini->pipes;
	mini->pid = ft_calloc((count_pipes + 2), sizeof(int));
	if (!mini->pid)
		print_error(mini, MALLOC_ERROR);
	fd_in = STDIN_FILENO;
	while (mini->cmd)
	{
		//llamar al expander aqui??
		//run_expander(mini, mini->cmd);
		if (mini->cmd->next && pipe(fds) == -1) //mini->cmd->next
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
	wait_pipes(mini, mini->pid, mini->pipes);
	//close(fd_in);
	return (0);
}

int	ft_fork(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in)
{
	static unsigned int	index = 0;

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

int check_next_fd_in(t_mini *mini, t_cmd *cmd, int fds[2])
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

void	wait_pipes(t_mini *mini, int *pid, int pipes)
{
	int	i;
	int	status;

	i = 0;
	while (i <= pipes)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status) == false)
		mini->error_code = WEXITSTATUS(status);
}
