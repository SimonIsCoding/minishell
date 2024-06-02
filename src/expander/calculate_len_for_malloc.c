/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_len_for_malloc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:17:51 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/30 16:39:49 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the goal is to write the line correctly
// if we have "this is a $TEST for $HOME $USER \$PAGE"
// the result "this is a  for /Users/login login $PAGE"

//we have the function to change the characters $HOME into his value =>Expansion
//we have to forget $TEST

//this functions checks only for 1 variable
//this function checks if the variable that we sent is in our env
//it returns 1 if the variable is in the env
//0 if it doesn't exists
//for example if we have the command line: "$test"
//$test is not in env => it returns 0
//the argument i is important because it's where we start
int	variable_existence(t_mini *mini, char *str, int i)
{
	t_builtin	*tmp;
	int			k;
	int			j;
	char		*env_key;

	i++;
	k = i;
	j = 0;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
	{
		j++;
		i++;
	}
	env_key = malloc(sizeof(char) * j + 1);
	if (!env_key)
		print_error(mini, 2);
	i = k;
	j = 0;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		env_key[j++] = str[i++];
	tmp = mini->env;
	while (tmp)
	{
		if (ft_strcmp_simple(env_key, tmp->key) == 0)
			return (free(env_key), 1);
		tmp = tmp->next;
	}
	return (free(env_key), 0);
}

//in the example of the l.16, this function forgets $TEST.
//That means, if the env variable doesn't exists, we don't write or allocate
//any memory space. And our iterator is just counting until the end of the word
void	forget_the_variable(char *str, int *i)
{
	(*i)++;
	while (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_'))
		(*i)++;
}

//this function returns the name of the key in our env list
char	*catch_expansion_key(t_mini *mini, char *str, int *i)//malloc ⚠️  
{
	char	*result;
	int		counter;
	int		tmp;

	result = NULL;
	counter = 0;
	(*i)++;
	tmp = *i;
	while (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_'))
	{
		counter++;
		(*i)++;
	}
	result = malloc(sizeof(char) * counter + 1);
	if (!result)
		print_error(mini, 2);
	*i = tmp;
	tmp = 0;
	while (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_'))
		result[tmp++] = str[(*i)++];
	result[tmp] = '\0';
	return (result);
}

//I had norminette issues so I had to cut the calculate_len_for_malloc function
void	manage_dollar_variable(t_mini *mini, char *str, int *i, int *counter)
{
	char		*env_key;
	char		*env_value;

	if (variable_existence(mini, str, *i) == 1)
	{
		env_key = catch_expansion_key(mini, str, i);
		if (!env_key)
			print_error(mini, 2);
		env_value = search_and_replace_variable(mini->env, env_key);
		(*counter) += ft_strlen(env_value);
		free(env_key);
	}
	else
		forget_the_variable(str, i);
}

//92 in the ascii table <=> BACKSLASH
//if we have the line to expand, this function returns the size that we will
//need for the malloc
int	calculate_len_for_malloc(t_mini *mini, char *str)
{
	int			i;
	int			counter;
	int			check;

	i = 0;
	counter = 0;
	check = 0;
	while (str[i] && i < (int)ft_strlen(str))
	{
		if (str[i] == BACKSLASH)
			i++;
		if ((i > 0 && str[i] == '$' && str[i - 1] == 92) || (str[i] != '$'))
		{
			counter++;
			i++;
		}
		else
		{
			manage_dollar_variable(mini, str, &i, &counter);
			check++;
			if (check > 1)
				counter++;
		}
	}
	return (counter);
}
