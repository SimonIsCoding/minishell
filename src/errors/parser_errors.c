/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:43:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:59:36 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_fatal_error(t_mini *mini, int keycode)
{
	free_mini(mini);
	if (keycode == MALLOC_ERROR)
		ft_putendl_fd("malloc: cannot allocate memory", STDERR_FILENO);
	else if (keycode == PIPE_ERROR)
		ft_putendl_fd("pipe: Error", STDERR_FILENO);
	else if (keycode == FORK_ERROR)
		ft_putendl_fd("fork: Error", STDERR_FILENO);
	else if (keycode == DUP2_ERROR)
		ft_putendl_fd("dup2: Error", STDERR_FILENO);
	else if (keycode == MAX_HDOC)
		ft_putendl_fd("maximum here-document count exceeded", STDERR_FILENO);
	else if (keycode == RANDOM)
		ft_putendl_fd("exit", STDERR_FILENO);
	exit(2);
}

static void	handle_specific_error(int keycode)
{
	if (keycode == SINTAX_ERROR)
		ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
	else if (keycode == IN_ERROR)
		ft_putstr_fd("in: No such file or directory\n", STDERR_FILENO);
	else if (keycode == OUT_ERROR)
		ft_putstr_fd("out: No such file or directory\n", STDERR_FILENO);
	else if (keycode == CMD_NOT_FOUND_ERROR)
		ft_putstr_fd("command not found\n", STDERR_FILENO);
	else if (keycode == EXECVE_ERROR)
		ft_putstr_fd("execve error\n", STDERR_FILENO);
	else if (keycode == EXIT_ERROR)
	{
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	else if (keycode == UNLINK_ERROR)
		ft_putstr_fd("unlink: No such file or directory\n", STDERR_FILENO);
	else if (keycode == EXPORT_ERROR)
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
}

int	print_error(t_mini *mini, int keycode)
{
	ft_putstr_fd("shelldone: ", STDERR_FILENO);
	if (keycode == MALLOC_ERROR || keycode == PIPE_ERROR
		|| keycode == FORK_ERROR || keycode == DUP2_ERROR
		|| keycode == MAX_HDOC || keycode == UNSET_HOME
		|| keycode == RANDOM)
		print_fatal_error(mini, keycode);
	else
		handle_specific_error(keycode);
	mini->error_code = STDERR_FILENO;
	mini_reset(mini);
	return (EXIT_FAILURE);
}

int	token_error(t_mini *mini, int token)
{
	ft_putstr_fd("shelldone: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else if (token == RED_IN)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == RED_OUT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == HDOC)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == RED_OUT_APP)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	mini->error_code = STDERR_FILENO;
	mini_reset(mini);
	return (EXIT_FAILURE);
}
