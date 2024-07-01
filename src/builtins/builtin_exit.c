/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/21 11:08:31 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_number(char *str_user, char *positive_lim,
						char *negative_lim)
{
	int	len_user;

	len_user = ft_strlen(str_user);
	if (len_user > 20)
		return (0);
	else if (len_user == 20 || len_user == 19)
	{
		if (str_user[0] == '-')
		{
			if (ft_strcmp_simple(str_user, negative_lim) > 0)
				return (0);
		}
		else if (str_user[0] == '+')
		{
			if (ft_strcmp_simple(&str_user[1], positive_lim) > 0)
				return (0);
		}
		else
		{
			if (ft_strcmp_simple(str_user, positive_lim) > 0)
				return (0);
		}
	}
	return (1);
}

void	free_elements(char *str1, char *str2)
{
	if (str1)
	{
		if (str2)
			free(str2);
		free(str1);
	}
}

void	free_mini(t_mini *mini)
{
	if (mini->cmd)
		lst_clear_cmds(&mini->cmd);
	if (mini->line)
		free(mini->line);
	if (mini->pipes)
		free(mini->pid);
	ft_free_double_array(&mini->env_cpy);
	ft_lstclear_builtin(&mini->env);
	free(mini->env);
	free(mini->pwd);
	free(mini->old_pwd);
}

int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	str2 = NULL;
	if (cmd->str && cmd->str[1])
	{
		str1 = ft_strdup(cmd->str[1]);
		if (cmd->str[2])
			str2 = ft_strdup(cmd->str[2]);
	}
	if (str2)
	{
		if (check_exit_many_arguments(str1) == 2)
			return (free_mini(mini), free(str2), exit(2), 2);
		else
			return (free_elements(str1, str2), 1);
	}
	if (str1)
		return (exit_with_one_argument(mini, str1, str2));
	return (free_mini(mini), free_elements(str1, str2),
		exit(mini->error_code), mini->error_code);
}
