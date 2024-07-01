/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:47:49 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/19 17:39:27 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_mini *mini)
{
	t_env_lst	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (mini->pwd && mini->old_pwd)
			break ;
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
		{
			if (mini->pwd)
				free(mini->pwd);
			mini->pwd = ft_strdup(tmp->value);
		}
		if (ft_strncmp(tmp->key, "OLD_PWD", 3) == 0)
		{
			if (mini->old_pwd)
				free(mini->old_pwd);
			mini->old_pwd = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	builtin_pwd(t_mini *mini)
{
	if (mini->pwd == NULL)
	{
		ft_putendl_fd(mini->pwd, 1);
		free(mini->pwd);
		mini->pwd = ft_strdup(mini->old_pwd);
	}
	else
		ft_putendl_fd(mini->pwd, 1);
	return (EXIT_SUCCESS);
}
