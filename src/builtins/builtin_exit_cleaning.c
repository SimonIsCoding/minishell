/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_cleaning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:28:38 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/19 17:38:55 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mini(t_mini *mini)
{
	if (mini->cmd)
		lst_clear_cmds(&mini->cmd);
	if (mini->line)
		free(mini->line);
	if (mini->pid)
		free(mini->pid);
	ft_free_double_array(mini->env_cpy);
	ft_lstclear_builtin(&mini->env);
	if (mini->pwd && *mini->pwd)
		free(mini->pwd);
	if (mini->old_pwd && *mini->old_pwd)
		free(mini->old_pwd);
	if (mini->pipes)
		free(mini->pid);
}
