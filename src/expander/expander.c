/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/20 11:23:34 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//before doing anything, we have to check if the ENV variable HOME is set or not
//if it's not set, we go out from our minishell because the project didn't asked
//to manage the system variables as the pwd is doing
int	check_cd_home(t_mini *mini, t_cmd *cmd)
{
	if (cmd->str && (ft_strcmp_simple(cmd->str[0], "cd") == 0)
		&& (cmd->str[1] && (ft_strcmp_simple(cmd->str[1], "~") == 0
				|| ft_strcmp_simple(cmd->str[1], "~/") == 0)))
	{
		if (variable_existence(mini, "$HOME", 0) == 0)
		{
			if (!mini->home_env)
				return (print_error(mini, UNSET_HOME), 0);
		}
	}
	return (1);
}

//this function is called out of the expander folder 
//this is the only function that does the relation with the principal code
void	run_expander(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;

	cmd->str = expand_cmd_line(mini, cmd->str);
	check_cd_home(mini, cmd);
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
