/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 16:08:57 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*modify_line_aux(char **env, char *tmp)
{
	char	*tmp2;
	char	*result;
	int		i;

	i = -1;
	tmp2 = NULL;
	result = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			tmp2 = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			result = ft_strjoin(tmp2, tmp);
			free(tmp2);
			break ;
		}
	}
	return (result);
}

char	*modify_line(t_mini *mini, char *str)
{
	char	*tmp;
	char	*result;
	char	*tmp2;
	char	**env;

	result = NULL;
	if (str[0] == '~')
		tmp = ft_strdup(&str[1]);
	else
		tmp = ft_strdup(str);
	if (tmp[0] != '/')
	{
		tmp2 = ft_strjoin("/", tmp);
		free(tmp);
		tmp = ft_strdup(tmp2);
		free(tmp2);
	}
	env = mini->env_cpy;
	result = modify_line_aux(env, tmp);
	return (free(tmp), result);
}

char	*return_value(t_mini *mini, char *str)
{
	t_env_lst	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, str) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd_dash(t_mini *mini, int *error)
{
	*error = do_cd(mini, "OLDPWD");
	if (*error == -1)
		*error = do_cd(mini, "PWD");
}
