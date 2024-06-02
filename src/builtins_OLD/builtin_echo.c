/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:52:06 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/13 13:00:50 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **command, char *line)
{
	if (ft_strncmp(command[0], "echo", 4) == 0)
	//comprobar si funciona igual ft_strcmp(command[0], "echo") pq strcmp compara len de ambos
	{
		if (!ft_strncmp(command[1], "-n", 2))
		{
			if (write(1, line, ft_strlen(line)) == -1)
				//line means what's after echo => the characters we want to write
				print_error("write failed in src/builtin_echo");
		}
		else// if (ft_strncmp(command[1], "-n", 2))//if the flag is NOT -n
		{
			if (write(1, line, ft_strlen(line)) == -1)
				//line means what's after echo => the characters we want to write
				print_error("write failed in src/builtin_echo");
			if (write(1, "\n", 1) == -1)
				print_error("write failed in src/builtin_echo");
		}
	}
}
