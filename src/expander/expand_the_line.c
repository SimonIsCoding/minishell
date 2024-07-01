/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_the_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:23:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/21 11:08:31 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the goal is to write the line correctly
// if we have: "this is a $TEST for $HOME $USER \$PAGE"
// the result: this is a  for /Users/login login $PAGE"

//we have the function to forget $TEST
//we have the function to change the $HOME with the expanded value
//we have the function to calculate_right_malloc_size 
//we have the function to know the env variable_existence

//I had norminette issues so I had to cut the expand_the_line function
int	expand_dollar_variable(t_mini *mini, char *str, int *i, char *result)
{
	int		j;
	int		k;
	char	*env_key;
	char	*env_value;

	j = 0;
	k = 0;
	if (variable_existence(mini, str, *i) == 1)
	{
		env_key = catch_expansion_key(mini, str, i);
		if (!env_key)
			print_error(mini, 2);
		env_value = search_and_replace_variable(mini->env, env_key);
		while (env_value[k])
			result[j++] = env_value[k++];
		free(env_key);
	}
	else
		forget_the_variable(str, i);
	result[j] = str[*i];
	return (j);
}

//the goal of this function is to show the error_code when we have: echo $?
//the result has to be a number which represents the last error_code

int	expand_error_code(t_mini *mini, int *i, char *result)
{
	int		j;
	int		k;
	char	*number;

	j = 0;
	k = 0;
	(*i) = (*i) + 2;
	number = ft_itoa(mini->error_code);
	if (!number)
		print_error(mini, 2);
	while (number[j])
		result[k++] = number[j++];
	return (free(number), j);
}

//this function will expand the whole line
//at the beginning we have the str like the example at the line 16
//and it returns the str like the line 17
char	*expand_the_line(t_mini *mini, char *str)//malloc ⚠️  
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = calculate_len_for_malloc(mini, str);
	result = malloc(sizeof(char) * j + 1);
	if (!result)
		print_error(mini, 2);
	j = 0;
	while (str[i])
	{
		if (str[i] == BACKSLASH)
			i++;
		if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH)
			|| (str[i] != '$'))
			result[j++] = str[i++];
		else if (i < (int)ft_strlen(str) - 1 && str[i] == '$'
			&& str[i + 1] == '?')
			j += expand_error_code(mini, &i, &result[j]);
		else
			j += expand_dollar_variable(mini, str, &i, &result[j]);
	}
	result[j] = '\0';
	return (result);
}
