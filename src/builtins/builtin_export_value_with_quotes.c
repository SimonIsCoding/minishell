/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_value_with_quotes.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:57:23 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/14 20:06:49 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_to_export(t_mini *mini, const char *str, const char quote_to_del)
{
	int		len;
	char	*res;

	len = (int)ft_strlen(str) - 1;
	while (str[len])
	{
		if (str[len] == quote_to_del)
		{
			res = ft_substr(str, 1, len - 1);
			if (!res)
				print_error(mini, 2);
		}
		len--;
	}
	return (res);
}

char	*value_with_quotes(t_mini *mini, char *str)
{
	char	quote_to_del;
	int		len;
	char	*res;
	int		i;
	char	*final;

	quote_to_del = str[0];
	res = value_to_export(mini, str, quote_to_del);
	len = (int)ft_strlen(res);
	i = -1;
	while (res[++i])
		if (ft_strchr(res, quote_to_del))
			len--;
	final = malloc(sizeof(char) * len + 1);
	if (!final)
		print_error(mini, 2);
	i = 0;
	len = 0;
	while (res[i])
		if (res[i] != quote_to_del)
			final[len++] = res[i++];
	final[len] = '\0';
	return (free(res), final);
}
