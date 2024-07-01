/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:58:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/19 17:21:53 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_married_quote(char *line, int start_index,
		int *num_quotes, int delimiter)
{
	int	index;

	index = start_index + 1;
	(*num_quotes) += 1;
	while (line[index] && line[index] != delimiter)
		index++;
	if (line[index] == delimiter)
		(*num_quotes)++;
	return (index - start_index);
}

int	check_quotes_is_married(char *line)
{
	int	i;
	int	len;
	int	single_quote_count;
	int	double_quote_count;

	i = 0;
	len = (int)ft_strlen(line);
	single_quote_count = 0;
	double_quote_count = 0;
	while (i < len)
	{
		if (line[i] == DQUOTE)
			i += find_married_quote(line, i, &double_quote_count, DQUOTE);
		if (line[i] == QUOTE)
			i += find_married_quote(line, i, &single_quote_count, QUOTE);
		if (i >= len)
			break ;
		i++;
	}
	if ((double_quote_count > 0 && double_quote_count % 2 != 0)
		|| (single_quote_count > 0 && single_quote_count % 2 != 0))
		return (0);
	return (1);
}
