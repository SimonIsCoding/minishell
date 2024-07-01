/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:47:43 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:59:50 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_up_signals_hdoc(void)
{
	g_status = 0;
}

int	not_found(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

void	ft_free_paths(char **str)
{
	int	i;

	if (!str || *str == NULL)
		return ;
	i = -1;
	while (str[++i])
	{
		free(str[i]);
	}
	free(str);
	str = NULL;
}

void	check_max_hdoc(t_mini *mini, t_lexer *redirects)
{
	t_lexer	*tmp;
	int		count;

	count = 0;
	tmp = redirects;
	while (tmp)
	{
		if (tmp->token == HDOC)
			count++;
		tmp = tmp->next;
	}
	if (count > 16)
		print_error(mini, MAX_HDOC);
}
