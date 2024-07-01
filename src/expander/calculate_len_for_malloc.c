/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_len_for_malloc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:17:51 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/21 11:15:21 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the goal is to write the line correctly
// if we have		   :"this is a $TEST for $HOME $USER \$PAGE"
// the result has to be: "this is a  for /Users/login login $PAGE"

//The function changes the characters $HOME into his value =>Expansion
//the goal of this function is to go through our list of environment variable
//if the parameter expand_name has the same name as one environment variable
//we return his content/value
//otherwise we return NULL
char	*search_and_replace_variable(t_env_lst *env_variable, char *expand_name)
{
	t_env_lst	*tmp;

	tmp = env_variable;
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, expand_name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

//in the example of the l.16, this function forgets $TEST.
//That means, if the env variable doesn't exists, we don't write or allocate
//any memory space. And our iterator is just counting until the end of the word
void	forget_the_variable(char *str, int *i)
{
	int	tmp;

	(*i)++;
	tmp = *i;
	while (str[*i] && ((ft_isalpha(str[*i]) || str[*i] == '_')
			|| (ft_isdigit(str[*i]) && *i != tmp)))
		(*i)++;
}

//this function returns the name of the key in our env list
//this function will catch the name of the variable in our str (=command line)
//starting from i, which is the $, until the end of his name
//for example					: echo $USER.
//this function below returns   : USER
char	*catch_expansion_key(t_mini *mini, char *str, int *i)//malloc ⚠️  
{
	char	*result;
	int		counter;
	int		tmp;

	result = NULL;
	counter = 0;
	(*i)++;
	tmp = *i;
	while (str[*i] && ((ft_isalpha(str[*i]) || str[*i] == '_')
			|| (ft_isdigit(str[*i]) && *i != tmp)))
	{
		counter++;
		(*i)++;
	}
	result = malloc(sizeof(char) * counter + 1);
	if (!result)
		print_error(mini, 2);
	*i = tmp;
	tmp = 0;
	while (str[*i] && ((ft_isalpha(str[*i]) || str[*i] == '_')
			|| (ft_isdigit(str[*i]) && *i != tmp)))
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
		if (str[i] == BACKSLASH || ((i > 0 && str[i] == '$'
					&& str[i - 1] == BACKSLASH) || (str[i] != '$')))
			iterate_classic_characters(str, &i, &counter);
		else if (i < (int)ft_strlen(str) - 1 && str[i] == '$'
			&& str[i + 1] == '?')
			create_space_for_error_code(mini, &i, &counter);
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
