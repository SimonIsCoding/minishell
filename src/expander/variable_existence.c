/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_existence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:44:51 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/10 18:30:10 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//I had norminette issues so I had to cut the function variable_existence in two
//if variable_existence was one function, this would have been at the beginning
void	variable_existence_helper(char *str, int *i, int *j, int *k)
{
	(*i)++;
	*j = 0;
	*k = *i;
	while (str[*i] && ((ft_isalpha(str[*i]) || str[*i] == '_')
			|| (ft_isdigit(str[*i]) && *i != *k)))
	{
		(*i)++;
		(*j)++;
	}
}

//this functions checks only for 1 variable
//this function checks if the variable that we sent is in our env list
//it returns 1 if the variable is in the env list
//0 if it doesn't exists
//for example if we have the command line: "$test"
//$test is not in env => it returns 0
//the argument i is important because it's where we start
int	variable_existence(t_mini *mini, char *str, int i)
{
	t_env_lst	*tmp;
	int			k;
	int			j;
	char		*env_key;

	variable_existence_helper(str, &i, &j, &k);
	env_key = malloc(sizeof(char) * j + 1);
	if (!env_key)
		print_error(mini, 2);
	i = k;
	j = 0;
	while (str[i] && ((ft_isalpha(str[i]) || str[i] == '_')
			|| (ft_isdigit(str[i]) && i != k)))
		env_key[j++] = str[i++];
	env_key[j] = '\0';
	tmp = mini->env;
	while (tmp)
	{
		if (ft_strcmp_simple(env_key, tmp->key) == 0)
			return (free(env_key), 1);
		tmp = tmp->next;
	}
	return (free(env_key), 0);
}
