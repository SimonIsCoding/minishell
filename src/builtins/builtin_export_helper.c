/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/15 17:42:15 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_flag(t_env_lst *tmp)
{
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "_", 1) != 0)
		{
			if (tmp->value == NULL)
				printf("declare -x %s\n", tmp->key);
			else
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
}

void	print_env_export(t_mini *mini, int flag)
{
	t_env_lst	*tmp;

	tmp = mini->env;
	if (flag == 0)
	{
		while (tmp)
		{
			if (tmp->key && tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else if (flag == 1)
		print_env_flag(tmp);
}

//I HAVE TO REMOVE THE NODE->KEY = _ BECAUSE IT ISN'T IN EXPORT
void	remove_special_node(t_env_lst **head)
{
	t_env_lst	*current;
	t_env_lst	*previous;

	previous = NULL;
	current = *head;
	if (*head == NULL)
		return ;
	while (current)
	{
		if (ft_strcmp(current->key, "_") == 0)
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

//there is a second argument whereas I only need one. I had norminette issues.
//This second argument has to be set as NULL
/*t_env_lst	*sort_ascii(t_env_lst *lst_export, t_env_lst *sorted)
{
	t_env_lst	*current;
	t_env_lst	*the_next;
	t_env_lst	*tmp;

	current = lst_export;
	while (current)
	{
		the_next = current->next;
		if (!sorted || ft_strcmp(current->key, sorted->key) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next && ft_strcmp(current->key, tmp->next->key) >= 0)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = the_next;
	}
	return (sorted);
}*/

//we want to check if everything is well written before the '='.
//It means if there is a key name to the str.
//we check if it's writtent like this: for+=example || for=example
//here: str <=> 'simon=test'
int	check_variable(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	if (ft_strchr(tmp, '=') != NULL)
	{
		while (str[i] != '=')
		{
			if (i == 0 && str[i] == 34)
				i++;
			else if (i == 0 && str[i] != '_' && !ft_isalpha(str[i]))
				return (perror("export: not a valid identifier"), 0);
			i++;
		}
	}
	else
		i = 1;
	if (i > 0 && str[i] == '=' && str[i - 1] == '+')
		return (2);
	if (i > 0)
		return (1);
	return (0);
}

char	*clean_value(t_mini *mini, char *str)
{
	int		i;
	char	*result;

	if (ft_strchr(str, '=') == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	if (str[i] == '\0')
		return (ft_strdup(""));
	if (str[i] == QUOTE || str[i] == DQUOTE)
	{
		result = value_with_quotes(mini, &str[i]);
		if (!result)
			print_error(mini, 2);
		return (result);
	}
	else
	{
		result = ft_strdup(&str[i]);
		if (!result)
			print_error(mini, 2);
		return (result);
	}
}
