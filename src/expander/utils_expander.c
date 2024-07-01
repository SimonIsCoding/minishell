/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/21 11:14:41 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '$')
			return (i + 1);
		str++;
		i++;
	}
	return (0);
}

int	is_equal(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '=')
			return (i + 1);
		str++;
		i++;
	}
	return (0);
}

void	create_space_for_error_code(t_mini *mini, int *i, int *counter)
{
	char		*num_len;

	num_len = ft_itoa(mini->error_code);
	(*counter) += (int)ft_strlen(num_len);
	free(num_len);
	(*i)++;
}

//classic characters are everything that are not $ followed by letters || _ || ?
void	iterate_classic_characters(char *str, int *i, int *counter)
{
	if (str[(*i)] == BACKSLASH)
		(*i)++;
	if ((*i > 0 && str[(*i)] == '$' && str[(*i) - 1] == BACKSLASH)
		|| (str[(*i)] != '$'))
	{
		(*counter)++;
		(*i)++;
	}
}
