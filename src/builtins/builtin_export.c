/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/25 16:59:46 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static char	**clear_line_export(char **str);
//lst refers to the list that contains all the lines of the export env
//in this function, str refers to the new export variable. ie: 'abc=test'
static t_env_lst	*add_export_variable(t_mini *mini, t_env_lst *lst,
				char *str, char *value_trimmed)
{
	static int	index = 150;
	t_env_lst	*new_node;

	new_node = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!new_node)
		print_error(mini, 2);
	new_node->key = get_key_from_env(mini, str);
	if (!new_node->key)
		print_error(mini, 2);
	if (value_trimmed)
		new_node->value = value_trimmed;
	else
		new_node->value = NULL;
	new_node->index = index++;
	new_node->next = NULL;
	ft_lstadd_back_builtin(&lst, new_node);
	return (lst);
}

//we go through our export list that contains every env variables
//if and only if we found the same, we will change the previous value with the
//current && the one that thee user wants to add (value_str) by concatenating
//both 
int	concat_value_export(t_env_lst **lst_export, char *key_str,
						char *value_str)
{
	t_env_lst	*tmp;
	char		*value_node;

	tmp = *lst_export;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key_str))
		{
			value_node = ft_strdup(tmp->value);
			free(tmp->value);
			tmp->value = ft_strjoin(value_node, value_str);
			return (free(value_node), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

//for the last 5 lines in this function:
//this is a special case: if we don't have any variables that are called
//'EXAMPLE' and the user wants to execute: export EXAMPLE+="text"
//then we have to create it and to add the 'text' to the EXAMPLE variable
// and to add EXAMPLE in our **lst_export
static void	join_values(t_mini *mini, t_env_lst **lst_export, char *str)
{
	char		*key_str;
	char		*value_str;
	char		*tmp_join;
	t_env_lst	*tmp;

	key_str = get_key_from_env(mini, str);
	if (!key_str)
		return ;
	value_str = clean_value(mini, str);
	if (!value_str)
	{
		free(key_str);
		print_error(mini, 2);
	}
	if (concat_value_export(lst_export, key_str, value_str) == 1)
		return (free(key_str), free(value_str));
	tmp_join = ft_strjoin(key_str, "=");
	free(key_str);
	key_str = ft_strjoin(tmp_join, value_str);
	tmp = ft_lstnew_builtin(mini, key_str);
	ft_lstadd_back_builtin(lst_export, tmp);
	return (free(tmp_join), free(key_str), free(value_str));
}

//if the variable already exists and we want to change it complelty
static void	check_key_already_exists(t_mini *mini, t_env_lst *lst_export,
					char *str)
{
	t_env_lst	*tmp;
	char		*key_str;

	tmp = lst_export;
	key_str = get_key_from_env(mini, str);
	if (!key_str)
		print_error(mini, 2);
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, key_str) == 0)
		{
			delone_node_env(tmp->index, &lst_export);
			break ;
		}
		tmp = tmp->next;
	}
	free(key_str);
}

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	char		*value_trimmed;
	int			i;

	if (ft_strcmp(cmd->str[0], "export") == 0 && cmd->str[1] == NULL)
		print_env_export(mini, 1);
	i = 1;
	while (cmd->str[i])
	{
		if (check_variable(cmd->str[i]) == 1)
		{
			check_key_already_exists(mini, mini->env, cmd->str[i]);
			value_trimmed = clean_value(mini, cmd->str[i]);
			mini->env = add_export_variable(mini, mini->env, cmd->str[i],
					value_trimmed);
		}
		else if (check_variable(cmd->str[i]) == 2)
			join_values(mini, &mini->env, cmd->str[i]);
		i++;
	}
	ft_free_double_array(&mini->env_cpy);
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
}
