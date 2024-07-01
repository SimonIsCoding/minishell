/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:07:20 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 12:35:17 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_value(t_mini *mini)
{
	t_env_lst	*tmp_builtin;
	char		*result;

	result = NULL;
	tmp_builtin = mini->env;
	while (tmp_builtin)
	{
		if (ft_strcmp_simple(tmp_builtin->key, "HOME") == 0)
			result = get_value_from_env(mini, tmp_builtin->key);
		tmp_builtin = tmp_builtin->next;
	}
	return (result);
}

void	count_pipes(t_mini *mini)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (mini->line[++i])
		if (mini->line[i] == '|')
			count++;
	mini->pipes = count;
}

int	count_args(t_lexer *lst)
{
	int		count;
	t_lexer	*tmp;

	count = 0;
	tmp = lst;
	while (tmp && tmp->token != PIPE)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	save_pwd(t_mini *mini, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			mini->pwd = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			mini->old_pwd = ft_substr(env[i], 7, ft_strlen(env[i]) - 7);
		i++;
	}
	if (mini->pwd[0] == '\0')
		return (0);
	else
		return (1);
}
