/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:46:27 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/18 20:13:06 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

char	*final_expansion(t_mini *mini, char *str)
{
	t_expansor	*expansion;
	char		*result;

	expansion = malloc(sizeof(t_expansor));
	if (!expansion)
		print_error(mini, 2);
	expansion->i = 0;
	expansion->lead = update_the_situation(str[expansion->i], 0);
	expansion->final_line = NULL;
	expansion->tmp = ft_strdup("");
	if (!expansion->tmp)
		print_error(mini, 2);
	while (str[expansion->i])
	{
		if (expansion->lead == 0)
			lead_is_zero(mini, str, expansion);
		else if (expansion->lead == 1)
			lead_is_one(mini, str, expansion);
		else if (expansion->lead == 2)
			lead_is_two(mini, str, expansion);
	}
	result = ft_strdup(expansion->final_line);
	return (free(expansion->tmp), free(expansion->final_line), free(expansion),
		result);
}

//At the beginning it was this function, but it didn't fulfilled the Norminette
//standards. That's why I created final_expansion.c, final_expansion_utils.c
//and expander.h
/*
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
}*/
