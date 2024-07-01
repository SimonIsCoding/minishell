/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:48 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/25 15:59:05 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_zero(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '0')
		{
			if (!(i == 0 && (str[i] == '-' || str[i] == '+')))
				return (0);
		}
	}
	return (1);
}

int	ft_isdigit_and_signs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (i != 0 && (str[i] != '-' || str[i] != '+'))
				return (0);
		}
	}
	return (1);
}

int	numeric_argument_required(char *str)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	free(str);
	return (2);
}

int	check_exit_many_arguments(char *str)
{
	if (ft_isdigit_and_signs(str) == 0)
		return (numeric_argument_required(str));
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("shelldone: exit", STDERR_FILENO);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		return (1);
	}
}

int	exit_with_one_argument(t_mini *mini, char *str1, char *str2)
{
	int	exit_code;

	if (ft_isdigit_and_signs(str1) == 0 || (check_zero(str1) == 0
			&& (check_exit_number(str1, "9223372036854775807",
					"-9223372036854775808") == 0)))
		return (free_mini(mini), exit(numeric_argument_required(str1)), 2);
	else
	{
		if (check_zero(str1) == 1)
			return (free_mini(mini), free_elements(str1, str2), exit(0), 0);
		exit_code = ft_atoi(str1) % 256;
		free_elements(str1, str2);
		return (free_mini(mini), exit(exit_code), exit_code);
	}
}
