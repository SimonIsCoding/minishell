/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:11:30 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/15 17:42:15 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//for each line of our env, we want to get the characters before the '='
//this will be the content of the 'key' variable in our structure
char	*get_key_from_env(t_mini *mini, char *str)//to free once used
{
	int		i;
	int		len_str;
	char	*result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || (i < (int)ft_strlen(str) - 1
				&& str[i] == '+' && str[i + 1] == '='))
			break ;
		i++;
	}
	len_str = i;
	result = malloc((len_str + 1) * sizeof(char));
	if (!result)
		print_error(mini, 2);
	i = 0;
	while (i < len_str)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

//for each line of our env, we want to get the characters after the '='
//this will be the content of the 'value' variable in our structure
char	*get_value_from_env(t_mini *mini, char *str)//to free once used
{
	int		i;
	int		j;
	char	*result;

	if (!mini)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	j = i;
	while (str[i])
		i++;
	result = ft_substr(str, j, i);
	if (!result)
		return (NULL);
	return (result);
}

t_env_lst	*ft_lstnew_builtin(t_mini *mini, char *env)
{
	t_env_lst	*new_node;
	char		*delimiter;

	(void)mini;
	new_node = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!new_node)
		return (NULL);
	delimiter = ft_strchr(env, '=');
	if (delimiter)
	{
		new_node->key = ft_substr(env, 0, delimiter - env);
		new_node->value = ft_strdup(delimiter + 1);
	}
	else
	{
		new_node->key = ft_strdup(env);
		new_node->value = NULL;
	}
	new_node->next = NULL;
	return (new_node);
}

void	create_builtin_lst(t_mini *mini, t_env_lst **lst_env, char **env)
{
	t_env_lst	*new_node;
	int			i;

	i = 0;
	while (env[i])
	{
		new_node = ft_lstnew_builtin(mini, env[i]);
		if (!new_node)
			print_error(mini, 2);
		ft_lstadd_back_builtin(lst_env, new_node);
		i++;
	}
}

int	builtin_env(t_mini *mini)
{
	print_env_export(mini, 0);
	return (EXIT_SUCCESS);
}
