/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/12 13:42:07 by anovio-c         ###   ########.fr       */
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
/*
int	count_lines_in_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
*/
