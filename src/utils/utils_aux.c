/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:07:20 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/20 08:53:10 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_values_aux(t_mini *mini, char *joined_value, char *key)
{
	joined_value = ft_strdup(key);
	if (!joined_value)
	{
		ft_free_double_array(&mini->env_cpy);
		print_error(mini, 2);
	}
	return (joined_value);
}

static char	*join_key_value(t_mini *mini, t_env_lst *tmp)
{
	char	*joined_value;
	char	*temp;

	joined_value = NULL;
	if (tmp->value != NULL)
	{
		temp = ft_strjoin("=", tmp->value);
		if (!temp)
		{
			ft_free_double_array(&mini->env_cpy);
			print_error(mini, 2);
		}
		joined_value = ft_strjoin(tmp->key, temp);
		free(temp);
		if (!joined_value)
		{
			ft_free_double_array(&mini->env_cpy);
			print_error(mini, 2);
		}
	}
	else
		joined_value = join_values_aux(mini, joined_value, tmp->key);
	return (joined_value);
}

void	concat_lst_env(t_mini *mini)
{
	t_env_lst	*tmp;
	int			i;

	tmp = mini->env;
	mini->env_cpy = (char **)malloc(
			(ft_lstsize_builtin(mini->env) + 1) * sizeof(char *));
	if (!mini->env_cpy)
		print_error(mini, 2);
	i = 0;
	while (tmp)
	{
		mini->env_cpy[i] = join_key_value(mini, tmp);
		tmp = tmp->next;
		i++;
	}
	mini->env_cpy[i] = NULL;
}
