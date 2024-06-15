/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/15 18:16:32 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_expander(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;

	cmd->str = expand_cmd_line(mini, cmd->str);
	if (cmd->str && (ft_strcmp_simple(cmd->str[0], "cd") == 0)
		&& (cmd->str[1] && (ft_strcmp_simple(cmd->str[1], "~") == 0
			|| ft_strcmp_simple(cmd->str[1], "~/") == 0)))
	{
		if (variable_existence(mini, "$HOME", 0) == 0)
		{
			if (!mini->home_env)
				print_error(mini, UNSET_HOME);
		}
	}
	tmp = cmd->redirections;
	while (tmp)
	{
		if (tmp->token != HDOC)
			tmp->str = expand_str_line(mini, tmp->str);
		tmp = tmp->next;
	}
}

// expand cmd line. only cmd flags and args of the cmd
char	**expand_cmd_line(t_mini *mini, char **str)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	while (str[i])
	{
		new = final_expansion(mini, str[i]);
		free(str[i]);
		str[i] = new;
		i++;
	}
	return (str);
}

// expand str==> filename
char	*expand_str_line(t_mini *mini, char *str)
{
	char	*new;

	new = NULL;
	new = final_expansion(mini, str);
	free(str);
	str = new;
	return (str);
}
