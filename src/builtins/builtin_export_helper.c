/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/25 16:58:29 by anovio-c         ###   ########.fr       */
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

	mini->env = sort_ascii(mini->env, NULL);
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
	result = ft_strdup(&str[i]);
	if (!result)
		print_error(mini, 2);
	return (result);
}
