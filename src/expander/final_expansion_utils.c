/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:41:11 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/11 17:32:40 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

void	lead_is_zero_helper(char *str, t_expansor *expansion)
{
	expansion->start = expansion->i;
	if (str[expansion->i] == DQUOTE || str[expansion->i] == QUOTE)
		expansion->start = expansion->i + 1;
	while (str[expansion->i] && expansion->lead == 0)
	{
		expansion->i++;
		expansion->lead = update_the_situation(str[expansion->i],
				expansion->lead);
		if (expansion->lead != 0 || str[expansion->i] == '$')
			break ;
	}
}

void	lead_is_zero(t_mini *mini, char *str, t_expansor *expansion)
{
	lead_is_zero_helper(str, expansion);
	if (expansion->start != expansion->i)
	{
		expansion->substring = ft_substr(str, expansion->start,
				expansion->i - expansion->start);
		if (!expansion->substring)
			print_error(mini, 2);
		if (invalid_characters(expansion->substring) == 1)
			expansion->expansion_line = ft_strdup(expansion->substring);
		else
			expansion->expansion_line = expand_the_line_lead_zero(mini,
					expansion->substring);
		if (!expansion->expansion_line)
			print_error(mini, 2);
		free(expansion->substring);
		if (expansion->final_line)
			free(expansion->final_line);
		expansion->final_line = ft_strjoin(expansion->tmp,
				expansion->expansion_line);
		if (!expansion->final_line)
			print_error(mini, 2);
		free(expansion->tmp);
		expansion->tmp = ft_strdup(expansion->final_line);
		free(expansion->expansion_line);
	}
}

void	lead_is_one(t_mini *mini, char *str, t_expansor *expansion)
{
	expansion->start = expansion->i + 1;
	while (str[expansion->i] && expansion->lead == 1)
	{
		expansion->i++;
		expansion->lead = update_the_situation(str[expansion->i],
				expansion->lead);
		if (expansion->lead != 1)
			break ;
	}
	if (expansion->start != expansion->i)
	{
		expansion->substring = ft_substr(str, expansion->start,
				expansion->i - expansion->start);
		if (!expansion->substring)
			print_error(mini, 2);
		if (expansion->final_line)
			free(expansion->final_line);
		expansion->final_line = ft_strjoin(expansion->tmp,
				expansion->substring);
		if (!expansion->final_line)
			print_error(mini, 2);
		free(expansion->tmp);
		expansion->tmp = ft_strdup(expansion->final_line);
		free(expansion->substring);
	}
}

void	lead_is_two_helper(char *str, t_expansor *expansion)
{
	expansion->start = expansion->i;
	if (str[expansion->i] == DQUOTE)
		expansion->start = expansion->i + 1;
	while (str[expansion->i] && expansion->lead == 2)
	{
		expansion->i++;
		expansion->lead = update_the_situation(str[expansion->i],
				expansion->lead);
		if (expansion->lead != 2 || str[expansion->i] == '$')
			break ;
	}
}

void	lead_is_two(t_mini *mini, char *str, t_expansor *expansion)
{
	lead_is_two_helper(str, expansion);
	if (expansion->start != expansion->i)
	{
		expansion->substring = ft_substr(str, expansion->start,
				expansion->i - expansion->start);
		if (!expansion->substring)
			print_error(mini, 2);
		if (invalid_characters(expansion->substring) == 1)
			expansion->expansion_line = ft_strdup(expansion->substring);
		else
			expansion->expansion_line = expand_the_line(mini,
					expansion->substring);
		if (!expansion->expansion_line)
			print_error(mini, 2);
		free(expansion->substring);
		if (expansion->final_line)
			free(expansion->final_line);
		expansion->final_line = ft_strjoin(expansion->tmp,
				expansion->expansion_line);
		if (!expansion->final_line)
			print_error(mini, 2);
		free(expansion->tmp);
		expansion->tmp = ft_strdup(expansion->final_line);
		free(expansion->expansion_line);
	}
}
