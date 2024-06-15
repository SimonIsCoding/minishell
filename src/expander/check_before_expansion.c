/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:59:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/12 13:40:02 by anovio-c         ###   ########.fr       */
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
	if (str[i] == '?')
		return (0);
	if (!str[i] || !(ft_isalpha(str[i]) == 1 || str[i] == '_'))
		return (1);
	return (0);
}
