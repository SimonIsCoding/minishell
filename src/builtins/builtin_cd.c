/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:32:12 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/25 16:14:50 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_list_env(t_mini *mini)
{
	t_env_lst	*tmp_env;

	tmp_env = mini->env;
	while (tmp_env)
	{
		if (ft_strcmp_simple(tmp_env->key, "PWD") == 0)
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(mini->pwd);
		}
		if (ft_strcmp_simple(tmp_env->key, "OLDPWD") == 0)
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(mini->old_pwd);
		}
		tmp_env = tmp_env->next;
	}
}

static void	update_path(t_mini *mini)
{
	char	*buffer;

	buffer = NULL;
	if (mini->pwd)
	{
		free(mini->old_pwd);
		mini->old_pwd = ft_strdup(mini->pwd);
	}
	buffer = getcwd(NULL, 0);
	free(mini->pwd);
	if (buffer)
	{
		mini->pwd = ft_strdup(buffer);
		free(buffer);
	}
}

int	do_cd(t_mini *mini, char *path)
{
	int		error;
	char	*tmp_key;

	tmp_key = NULL;
	error = 0;
	tmp_key = return_value(mini, path);
	if (tmp_key != NULL)
	{
		error = chdir(tmp_key);
		free(tmp_key);
	}
	if (error != 0)
		print_error(mini, RANDOM);
	return (error);
}

static int	builtin_cd_aux(t_mini *mini, t_cmd *cmd, int *error)
{
	*error = chdir(cmd->str[1]);
	if (!ft_strcmp_simple(cmd->str[1], ".") && *error == 0
		&& chdir(mini->pwd) < 0)
		print_error(mini, RANDOM);
	if (*error == -1)
	{
		ft_putstr_fd("shelldone: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd->str[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		*error = 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(t_mini *mini, t_cmd *cmd)
{
	int		error;
	char	*tmp;

	error = 1;
	if (cmd->str[1] == NULL || ft_strcmp_simple(cmd->str[1], "~") == 0
		|| ft_strcmp_simple(cmd->str[1], "~/") == 0)
		error = do_cd(mini, "HOME");
	else if (ft_strcmp_simple(cmd->str[1], "-") == 0)
		cd_dash(mini, &error);
	else if (ft_strncmp(cmd->str[1], "~/", 2) == 0 && cmd->str[1][3])
	{
		tmp = modify_line(mini, cmd->str[1]);
		free(cmd->str[1]);
		cmd->str[1] = ft_strdup(tmp);
		free(tmp);
		error = chdir(cmd->str[1]);
		if (error == -1)
			error = 1;
	}
	else
		if (builtin_cd_aux(mini, cmd, &error) == 1)
			return (1);
	update_path(mini);
	update_list_env(mini);
	return (error);
}
