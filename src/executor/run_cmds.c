/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:36:30 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:55:32 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_mini *mini, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
		if (do_redirections(mini, cmd))
			exit(1);
	if (cmd->builtin != NOT_HAVE)
	{
		exit_code = do_builtin(mini, cmd);
		exit(exit_code);
	}
	else if (cmd->str[0] && cmd->str[0][0])
		exit_code = do_cmd(mini, cmd);
	exit(exit_code);
}

int	do_builtin(t_mini *mini, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->builtin == ECHO)
		exit_code = builtin_echo(mini, cmd);
	else if (cmd->builtin == CD)
		exit_code = builtin_cd(mini, cmd);
	else if (cmd->builtin == PWD)
		exit_code = builtin_pwd(mini);
	else if (cmd->builtin == EXPORT)
		exit_code = builtin_export(mini, cmd);
	else if (cmd->builtin == UNSET)
		exit_code = builtin_unset(mini, &mini->env, cmd);
	else if (cmd->builtin == ENV)
		exit_code = builtin_env(mini);
	else if (cmd->builtin == EXIT)
		exit_code = builtin_exit(mini, cmd);
	return (exit_code);
}

static void	aux_do_cmd(t_mini *mini, char **paths, char *tmp)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	while (paths && paths[i])
	{
		cmd_path = ft_strjoin(paths[i], tmp);
		if (!cmd_path)
			print_error(mini, 2);
		if (access(cmd_path, F_OK | X_OK) == 0)
			execve(cmd_path, mini->cmd->str, mini->env_cpy);
		free(cmd_path);
		i++;
	}
}

int	do_cmd(t_mini *mini, t_cmd *cmd)
{
	char	**env;
	char	**paths;
	char	*tmp;

	paths = NULL;
	env = mini->env_cpy;
	if (!access(cmd->str[0], F_OK | X_OK))
		execve(cmd->str[0], cmd->str, mini->env_cpy);
	while (*env && !ft_strnstr(*env, "PATH", 5))
		env++;
	tmp = ft_substr(*env, 5, ft_strlen(*env) - 5);
	if (tmp[0] != '\0')
		paths = ft_split(tmp, ':');
	free(tmp);
	tmp = ft_strjoin("/", cmd->str[0]);
	aux_do_cmd(mini, paths, tmp);
	if (paths)
		ft_free_paths(paths);
	return (free(tmp), not_found(cmd->str[0]));
}

void	handle_single_cmd(t_mini *mini, t_cmd *cmd)
{
	int	pid;
	int	status;

	run_expander(mini, cmd);
	if (cmd->builtin != NOT_HAVE && cmd->builtin != ECHO && cmd->builtin != PWD)
	{
		mini->error_code = do_builtin(mini, cmd);
		return ;
	}
	check_if_exists_hdoc(mini, mini->cmd);
	pid = fork();
	if (pid == -1)
		print_error(mini, FORK_ERROR);
	if (pid == 0)
		ft_exec_cmd(mini, cmd);
	waitpid(pid, &status, 0);
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
