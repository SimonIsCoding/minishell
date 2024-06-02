/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:43:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/29 17:34:31 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	print_error(t_mini *mini, int keycode)
{
	ft_putstr_fd("shelldone: ", STDERR_FILENO);
	if (keycode == SINTAX_ERROR)
		ft_putstr_fd("syntax error near unexpected token\n", 1);
	else if (keycode == MALLOC_ERROR)
		ft_putstr_fd("malloc: cannot allocate memory\n", STDERR_FILENO);
	else if (keycode == IN_ERROR)
		ft_putstr_fd("in: No such file or directory\n", STDERR_FILENO);
	else if (keycode == OUT_ERROR)
		ft_putstr_fd("out: No such file or directory\n", STDERR_FILENO);
	else if (keycode == PIPE_ERROR)
		ft_putstr_fd("pipe: Error\n", STDERR_FILENO);
	else if (keycode == FORK_ERROR)
		ft_putstr_fd("fork: Error\n", STDERR_FILENO);
	else if (keycode == DUP2_ERROR)
		ft_putstr_fd("dup2: Error\n", STDERR_FILENO);
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
	mini_reset(mini);
	return (EXIT_FAILURE);
}

int	token_error(t_mini *mini, int token)
{
	ft_putstr_fd("shelldone: syntax error near unexpected token ", STDERR_FILENO);
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
	lexer_clear(&mini->lexer);
	//if (mini->lexer)
		//lst_clear_lexer(&mini->lexer);
	mini_reset(mini);
	return (EXIT_FAILURE); // exit code 258 bash;
}
