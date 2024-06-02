/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:32:12 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/19 16:56:23 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_list_env(t_mini *mini)
{
	t_builtin	*tmp_env;

	tmp_env = mini->env;
	while (tmp_env)
	{
		if (ft_strcmp_simple(tmp_env->key, "PWD") == 0)
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(mini->pwd);
		}
		else if (ft_strcmp_simple(tmp_env->key, "OLDPWD") == 0)
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(mini->old_pwd);
		}
		tmp_env = tmp_env->next;
	}	
}

static void	update_path(t_mini *mini)
{
	char	*old;

	old = ft_strdup(mini->pwd);
	mini->old_pwd = old;
	mini->pwd = getcwd(NULL, sizeof(NULL));
}

static	char	*return_value(t_mini *mini, char *str)
{
	t_builtin	*tmp;
	//char		*value;

	tmp = mini->env;
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, str) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

static int	do_cd(t_mini *mini, char *path)
{
	int		error;
	char	*tmp_key;

	tmp_key = return_value(mini, path);
	error = chdir(tmp_key);
	free(tmp_key);
	return (error);
}


int	builtin_cd(t_mini *mini, t_cmd *cmd)
{
	int	error;

	error = 1;
	if (cmd->str[1] == NULL || ft_strcmp_simple(cmd->str[1], "~") == 0) // to HOME
		error = do_cd(mini, "HOME");
	else if (ft_strcmp_simple(cmd->str[1], "-") == 0)
		error = do_cd(mini, "OLDPWD");
	else if (ft_strcmp_simple(cmd->str[1], "tmp") == 0)
		error = chdir("/private/tmp");
	else
	{
		error = chdir(cmd->str[1]);
		if (error == -1)
		{
			//bash: cd: jkwenr: No such file or directory
			ft_putstr_fd("shelldone: cd: ", STDERR_FILENO);
			ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			return (error);
		}
	}
	update_path(mini);
	update_list_env(mini);
	concat_lst_env(mini);
	return (error);
}