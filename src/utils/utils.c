/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:07:20 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/15 17:45:43 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_value(t_mini *mini)
{
	t_env_lst	*tmp_builtin;
	char		*result;
	
	result = NULL;
	tmp_builtin = mini->env;
	while (tmp_builtin)
	{
		if (ft_strcmp_simple(tmp_builtin->key, "HOME") == 0)
			result = get_value_from_env(mini, tmp_builtin->key);
		tmp_builtin = tmp_builtin->next;
	}
	return (result);
}

void	count_pipes(t_mini *mini)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (mini->line[++i])
		if (mini->line[i] == '|')
			count++;
	mini->pipes = count;
}

int	count_args(t_lexer *lst)
{
	int		count;
	t_lexer	*tmp;

	count = 0;
	tmp = lst;
	while (tmp && tmp->token != PIPE)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	concat_lst_env(t_mini *mini)
{
	t_env_lst	*tmp;
	int			i;
	char		*joined_value;
	char		*temp;

	tmp = mini->env;
	mini->env_cpy = (char **)malloc(
			(ft_lstsize_builtin(tmp) + 1) * sizeof(char *));
	if (!mini->env_cpy)
		print_error(mini, 2);
	i = 0;
	while (tmp)
	{
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
		{
			joined_value = ft_strdup(tmp->key);
			if (!joined_value)
			{
				ft_free_double_array(&mini->env_cpy);
				print_error(mini, 2);
			}
		}
		mini->env_cpy[i] = joined_value;
		tmp = tmp->next;
		i++;
	}
	mini->env_cpy[i] = NULL;
}


