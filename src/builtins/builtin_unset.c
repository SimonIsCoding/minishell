/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:25:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/06 17:18:26 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//**head refers to the env builtin list
//the str refers to the unset_arg to remove (for example PWD)
//this function is basically remove a node

static	int	scan_start_unset_arg(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->str[1] || cmd->str[1][0] == '_'
		|| (cmd->str[1][0] == '\'' && cmd->str[1][1] == '\0'))
		return (EXIT_SUCCESS);
	while (cmd->str[1][i])
		i++;
	i--;
	if (cmd->str[1][i] == '/' || cmd->str[1][i] == '\\')
	{
		ft_putstr_fd("shelldone: unset: `", STDERR_FILENO);
		ft_putstr_fd(&cmd->str[1][i], STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

static	int	detect_unset_error(t_cmd *cmd)
{
	char	*unset_arg;
	int		i;

	i = 0;
	unset_arg = cmd->str[1];
	if (is_equal(&unset_arg[0]) != 0)
	{
		ft_putendl_fd("shelldone: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (unset_arg[i++])
	{
		if (unset_arg[i++] == '/')
		{
			ft_putstr_fd("shelldone: unset: `", STDERR_FILENO);
			ft_putstr_fd(&unset_arg[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static	void	remove_env_variable(t_builtin **head, t_builtin *current,
							t_builtin *previous)
{
	if (previous == NULL)
		*head = current->next;
	else
		previous->next = current->next;
	free(current->key);
	free(current->value);
	free(current);
}

static	int	unset_check(t_cmd *cmd)
{
	if (scan_start_unset_arg(cmd) == 0)
		return (EXIT_SUCCESS);
	if (detect_unset_error(cmd) == 1)
		return (EXIT_FAILURE);
	return (-1);
}

// hacer que si el index es <1000 no se elimine, pero de el success
// porque? porque asi no tendremos errores o segs
// que eliminen una env del sistema como home
int	builtin_unset(t_mini *mini, t_builtin **head, t_cmd *cmd)
{
	int			i;
	t_builtin	*current;
	t_builtin	*previous;

	i = 0;
	while (cmd->str[++i])
	{
		if (unset_check(cmd) != -1)
			return (unset_check(cmd));
		previous = NULL;
		current = *head;
		while (current)
		{
			if (ft_strcmp_simple(current->key, cmd->str[i]) == 0)
			{
				remove_env_variable(head, current, previous);
				break ;
			}
			previous = current;
			current = current->next;
		}
	}
	ft_free_double_array(mini->env_cpy);
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
}
