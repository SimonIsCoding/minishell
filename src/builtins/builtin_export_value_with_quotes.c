/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_value_with_quotes.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:57:23 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/25 16:24:44 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_to_export(t_mini *mini, const char *str, const char quote_to_del)
{
	int		len;
	char	*res;

	len = (int)ft_strlen(str) - 1;
	while (len >= 0)
	{
		len--;
		if (str[len] == quote_to_del)
		{
			res = ft_substr(str, 1, len);
			if (!res)
				print_error(mini, 2);
		}
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

//there is a second argument whereas I only need one. I had norminette issues.
//This second argument has to be set as NULL. I couldn't declare it in the 
//declaration section otherwise I would have 26/27 lines.
t_env_lst	*sort_ascii(t_env_lst *lst_export, t_env_lst *sorted)
{
	t_env_lst	*current;
	t_env_lst	*the_next;
	t_env_lst	*tmp;

	current = lst_export;
	while (current)
	{
		the_next = current->next;
		if (!sorted || ft_strcmp_simple(current->key, sorted->key) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next && ft_strcmp_simple(current->key,
					tmp->next->key) >= 0)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = the_next;
	}
	return (sorted);
}
