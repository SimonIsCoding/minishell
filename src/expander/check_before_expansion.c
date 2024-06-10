/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:59:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/10 19:01:26 by simarcha         ###   ########.fr       */
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

//other examples:
//string like this			: echo 'this' "is" '''a' "test" '$from' "$USER"
//the result has to be      : this is a test $from simarcha

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
	return (lead);
}

//for example if our string is : $$
//we don't want to expand it because this is not an env
//we consider it as invalid character and we return 1
//otherwise we consider it as valid and we return 0
int	invalid_characters(const char *str)
{
	int	i;

	i = 0;
	i++;
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
				if (!substring)
					print_error(mini, 2);
				if (invalid_characters(substring) == 1)
					expansion_line = ft_strdup(substring);
				else
					expansion_line = expand_the_line_lead_zero(mini, substring);
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
			if (str[i] == DQUOTE)
				start = i + 1;
			while (str[i] && lead == 2)
			{
				i++;
				lead = update_the_situation(str[i], lead);
				if (lead != 2 || str[i] == '$')
					break ;
			}
			if (start != i)
			{
				substring = ft_substr(str, start, i - start);
				if (!substring)
					print_error(mini, 2);
				if (invalid_characters(substring) == 1)
					expansion_line = ft_strdup(substring);
				else
					expansion_line = expand_the_line(mini, substring);
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
	}
	return (free(tmp), final_line);
}
