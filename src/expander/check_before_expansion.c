/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:59:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/10 13:01:15 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we will receive our command line as a char **str such as mini->cmd->str
//for example, if the command line is: echo my name is simon > outfile
//we manage: [[echo], [my], [name], [is], [simon]]
//index are:	 0      1      2      3      4
//in this command line, there is nothing to expand. We just have to call for 
//echo giving it the right str which should be "my name is simon"

//but if the command line is: echo "'my name is $USER'" > outfile
//we manage: [[echo], ['my name is $USER']
//index are:	 0              1
//there is str[1] to expand due to $USER. We have to call for
//the expand_the_line function that should return: 'my name is $login'
//because we are in the double quotes

//this function checks if we have to expand the line or we just have to write it 
int	is_expansion_required(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == '$' && str[i - 1] != BACKSLASH)
		{
			if (variable_existence(mini, str, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

//now for example if we have: echo "$USER""this is a test"
//we received it as: [[echo], ["$USER""this is a test"]]
//index are:             0              1
//the result has to be: loginthis is a test
//so we have to remove the doubles quotes
//we suppose that the string received has been checked to have closed quotes
int	return_position_next_quote(char c, char *str, int i)
{
//	i++;//to forget the first quote
	while (str[i] && str[i] != c)
		i++;
	printf("i memory adress = %p\ni = %i\n", &i, i);
	return (i);
}

//we want a function that checks if we are in a simple quotes or not
int	we_are_in_simple_quote(char character)
{
	static int	quote_counter = 0;

	if (character == 39)
		quote_counter++;
	if (quote_counter % 2 == 0)
		return (0);
	return (1);
}

//34 in the ascii table <=> " 
//how to create a function that remove the quotes ?
//if we are in double quotes => we have to know where are the other double 
//quotes that closes the current quotes.
//we supposed that the quotes are closed => if we found one, there will be another one

char	*quit_single_quotes(t_mini *mini, char *str)
{
	int		i;
	int		k;
	char	*result;
	char	*tmp;
	char	*aux;
	
	int		check;
	i = 0;
	aux = ft_strdup("");//⚠️  malloc ⚠️ 
	if (!aux)
		print_error(mini, 2);
	check = 0;
	while (str[i])
	{
		while (we_are_in_simple_quote(str[i]) == 1)

		{
			k =	return_position_next_quote(QUOTE, str, i + 1);
			tmp = ft_substr(str, i + 1, k - (i + 1));//⚠️  malloc ⚠️ 
			if (check == 1)
				free(result);
			result = ft_strjoin(aux, tmp);
			check = 1;
			free(aux);
			free(tmp);
			aux = ft_strdup(result);
//			free(result);//⚠️  you have to free result once used
		}
		//si on trouve un dollar et que le caractere anterieur n'etait pas un BACKSLASH
		if (i > 0 && str[i] == '$' && str[i - 1] != BACKSLASH)
		{
			//if (variable_existence(mini, str, i) == 1)
		}
		printf("result = %s\n", result);
		i++;
	}
	return (free(aux), result);
}

//we have a string like this: echo 'this' "is" '''a' "test" '$from' "$USER"
//the result has to be      : this is a test $from simarcha

//we have the function that partially remove the single string
//but it doesn't work if we have a mix of single and double quotes



/*void	check_the_situation(char *str)
{
	int	i;
	int	lead;

	i = 0;
	lead = 0;
	while (str[i])
	{
		lead = update_the_situation(str[i], lead);
		printf("lead = %i for str[i] = %c\n", lead, str[i]);
		i++;
	}
}*/

//this function returns the situation about being or inside single quotes
//or inside double quotes, or inside none of both.
//lead = 0 => we are in no quotes
//lead = 1 => we are in simple quotes
//lead = 2 => we are in double quotes
int	update_the_situation(char c, int lead)
{
	if (lead == 0)
	{
		if (c == QUOTE)
			lead = 1;
		else if (c == DQUOTE)
			lead = 2;
	}
	else if (lead == 1)
	{
		if (c == QUOTE)
			lead = 0;
	}
	else if (lead == 2)
	{
		if (c == DQUOTE)
			lead = 0;
	}
//	printf("at the end of the fonction update_the_situation\nlead memory adress = %p\nlead = %i\n", lead, *lead);
	return (lead);
}

/*char	*manage_no_quote(t_mini *mini, char *str, int *i)
{
	int		start;
	char	*substring;
	char	*str_joined;

	substring = NULL;
	str_joined = NULL;
	start = i;
	if (str[i] == DQUOTE || str[i] == QUOTE)
		start = i + 1;
	while (str[i] && lead == 0)
	{
		i++;
		lead = update_the_situation(str[i], lead);
		if (lead != 0)
			break ;
	}
	if (start != i)
	{
		substring = ft_substr(str, start, i - start);
		if (!substring)
			print_error(mini, 2);
		printf("0 substring = _%s_\n", substring);}
		
	}
	return (str_joined);
}*/

/*int	possible_env(char *str, int i)
{
	if (str[i] == '$' && i > 0
		&& (ft_isalpha(str[i - 1]) == 1 || str[i - 1] == '_'))
		return (1);
	return (0);
}*/

//for example if our string is : $$
//we don't want to expand it because this is not an env
//we consider it as invalid character and we return 1
//otherwise we consider it as valid and we return 0
int	invalid_characters(const char *str)
{
	int	i;

	i = 0;
//	printf("in invalid_characters str = _%s_\n", str);
	i++;//to forget the '$'
	if (!str[i] || !(ft_isalpha(str[i]) == 1 || str[i] == '_'))
		return (1);
	return (0);
}

char	*final_expansion(t_mini *mini, char *str)
{
	char	*final_line;
	int		i;
	int		lead;
	int		start;
	char	*substring;
	char	*tmp;
	char	*expansion_line;

	i = 0;
	lead = update_the_situation(str[i], 0);
	final_line = NULL;
	tmp = ft_strdup("");
	if (!tmp)
		print_error(mini, 2);
	while (str[i])
	{
		if (lead == 0)
		{
			start = i;
			if (str[i] == DQUOTE || str[i] == QUOTE)
				start = i + 1;
			while (str[i] && lead == 0)
			{
				i++;
				lead = update_the_situation(str[i], lead);
				if (lead != 0 || str[i] == '$')
					break ;
			}
			if (start != i)
			{
				substring = ft_substr(str, start, i - start);
				printf("substring : _%s_\n", substring);
				if (!substring)
					print_error(mini, 2);
				if (invalid_characters(substring) == 1)
				{
					expansion_line = ft_strdup(substring);
					printf("entered in invalid_characters for _%s_\n", substring);
				}
				else
					expansion_line = expand_the_line_lead_zero(mini, substring);
				printf("value expanded = _%s_\n", expansion_line);
				if (!expansion_line)
					print_error(mini, 2);
				free(substring);
				if (final_line)
					free(final_line);
				final_line = ft_strjoin(tmp, expansion_line);
				if (!final_line)
					print_error(mini, 2);
				tmp = ft_strdup(final_line);
				free(expansion_line);
			}
		}
		else if (lead == 1)
		{
			start = i + 1;
			while (str[i] && lead == 1)
			{
				i++;
				lead = update_the_situation(str[i], lead);
				if (lead != 1)
					break ;
			}
			if (start != i)
			{
				substring = ft_substr(str, start, i - start);
				if (!substring)
					print_error(mini, 2);
				if (final_line)
					free(final_line);
				final_line = ft_strjoin(tmp, substring);
				if (!final_line)
					print_error(mini, 2);
				tmp = ft_strdup(final_line);
				free(substring);	
			}
		}
		else if (lead == 2)
		{
			start = i;
			if (str[i] == DQUOTE)//for the second time that we update_the_situation, lead can be = 0  && str[i] can be == quote
				start = i + 1;//we want to forget it
			while (str[i] && lead == 2)
			{
				i++;
				lead = update_the_situation(str[i], lead);
				if (lead != 2 || str[i] == '$')//if the situation has changed || there is two env sticked: $PWD$USER
					break ;
			}
			if (start != i)//I have to create this condition otherwise we call the ft_substr a lot of time for sth empty (with start == i)
			{
				substring = ft_substr(str, start, i - start);
				if (!substring)
					print_error(mini, 2);
				if (invalid_characters(substring) == 1)//if there is $$ => we consider it as invalid
					expansion_line = ft_strdup(substring); 
				else//if the characters are valid <=> $letters_
					expansion_line = expand_the_line(mini, substring);//we expand the line, or we show nothing if the env doesn't exist
				if (!expansion_line)
					print_error(mini, 2);
				free(substring);
				if (final_line)//if it's not the first time that we call for final_line, we will have to free the previous final_line, otherwise we will have some leaks. 
					free(final_line);
				final_line = ft_strjoin(tmp, expansion_line);
				if (!final_line)
					print_error(mini, 2);
				tmp = ft_strdup(final_line);//this is how I keep the characters of final line, to join them just before
				free(expansion_line);
			}
		}
	}
	printf("final_line = _%s_\n", final_line);
	return (free(tmp), final_line);
}
