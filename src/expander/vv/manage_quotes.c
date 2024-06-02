/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:49:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/21 12:32:19 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//we want a function to know if the expanded variable has to be expanded or not
//for example, if we have: echo '$test' => we don't have to expand it =>output: $test
//but if we have		 : echo "$test" => we have to expand it => output : content of test
//basically if the content is between simple quotes => we don't expand it
//else (there is no quotes or double quotes), we expand it

//we want to return a int to know if we have to expand it or not
//it means if we are in a double or a single quote
/*int	expand_or_not(t_mini *mini, char *str)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			if (check == 1)
				check = 0;
			else
				check = 1;
		}
		i++;
	}
	return (!check);
}

int	expand_or_not(char *str)
{
	int	i;
	int	sq_check;
	int	dq_check;

	i = 0;
	sq_check = 0;
	dq_check = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE && sq_check == 0)
			dq_check = !dq_check;
		if (str[i] == QUOTE && dq_check == 0)
			sq_check = !sq_check;
		i++;
	}
	if (dq_check == 0)
		return (1);
	return (0);
}*/

char	*search_and_replace_variable(t_builtin *env_variable, char *expand_name)
{
	t_builtin	*tmp;

	tmp = env_variable;
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, expand_name) == 0)
			return (get_value_from_env(tmp->key));//malloc ⚠️
		tmp = tmp->next;
	}
	return (NULL);
}

//in this function we want the name/key of the variable to expand
//then when we got it, we will know which value to look for, thanks to that result
//if we find a dollar, we want to know if after it's not a '?'
//if it's not, we will store the characters until we found a character that is different from letters || _
char	*get_expansion_name(t_mini *mini, char *str, int i)
{
	char	*result;
	int		counter;
	int		tmp;

	counter = 0;
	i++;
	if (i < (int)ft_strlen(str) - 1
		&& (ft_isalpha((int)str[i + 1]) == 1 || str[i + 1] == '_'))//we want to check if the next one is a letter, to be sure that is valid && not a '?'
	{
		tmp = i;
		while (str[++i] != ' ') 
			counter++;
		result = malloc(sizeof(char) * counter + 1);
		if (!result)
			print_error(mini, 2);
		i = tmp;
		tmp = 0;
		while (str[i] != ' ')
			result[tmp++] = str[i++];
		result[tmp] = '\0';
	}
	printf("result %p\nresult = %s\n", &result, result);
	return (result);
}

char	*expand_or_not(t_mini *mini, char *str)
{
	int		simple_quote;
	int		double_quote;
	char	*result;//the string with everything written => characters and the value of the expanded variable
	char	*expansion;
	int		i;

	i = 0;
	simple_quote = 0;
	double_quote = 0;
	if (check_all_quotes_closed(str) == 0)
		print_error(mini, 1);//not well written
	//you have to malloc the good size of characters for the result
	while (str[i])
	{
		if (str[i] == DQUOTE && simple_quote == 0)
			double_quote = !double_quote;
		else if (str[i] == QUOTE && double_quote == 0)
			simple_quote = !simple_quote;
		else if (simple_quote == 1)//in this case we don't expand
			result[i] += str[i];
		else if (double_quote == 1)//we expand it
		{
			//if it's a $
			if (str[i] == '$')
			{
				expansion = get_expansion_name(mini, str, i); 	
				expansion = search_and_replace_variable(
			}
				//search_and_replace_variable with strjoin
				//we want to search for the variable that is the same as the name after the $
				//and join his value with what we had before
			else if (str[i] == BACKSLASH)
				i++;
			else
				result[i] += str[i];
		}
		else
		{

		}
		i++;
	}
	return (result);
}

//you have to do a function that returns an int
//this int means that is it or in a DQUOTE or in a simple QUOTE
//in this case we know if we have to expand or not

//we have to check if all quotes are closed to execute command with quotes
//if there is one open, we return 0. It means the command can't be executed
int	check_all_quotes_closed(char *str)
{
	int	simple_quote;
	int	double_quote;
	int	i;

	simple_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
			simple_quote = !simple_quote;
		if (str[i] == DQUOTE)
			double_quote = !double_quote;
		i++;
	}
	if (simple_quote == 0 && double_quote == 0)
		return (1);
	return (0);
}
