/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/12 13:31:23 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we want to count the lines of the array
int	lines_counter(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

//we have to check if the flag of the echo cmd is written in that way :
//-nnnnnnnnnnnnn -> that is also considered as correct
static int	check_flag(char *flag)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (flag[i])
	{
		if (flag[i] == '-' && i == 0)
		{
			i++;
			check = 1;
		}
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	if (check == 1 && i == (int)ft_strlen(flag))
		return (1);
	return (0);
}

//in this function there is the same verification as the previous one
//because the user can write: echo -n -n -nnnn -nn test
//and we have to return, without line break: test
static int	builtin_echo_flag_n(t_mini *mini, t_cmd *command, int i, int wc)
{
	char	*content;

	while (command->str[i])
	{
		while (command->str[i] && (ft_strcmp_simple(command->str[i], "-n") == 0
				|| check_flag(command->str[i]) == 1))
			i++;
		content = final_expansion(mini, command->str[i]);
		if (!content)
			print_error(mini, 2);
		if (write(1, content, ft_strlen(content)) == -1)
			print_error(mini, 0);
		if (i < wc - 1)
			if (write(1, " ", 1) == -1)
				return (print_error(mini, 0), 0);
		i++;
		free(content);
	}
	return (1);
}

int	builtin_echo_without_flag(t_mini *mini, t_cmd *command, int i, int wc)
{
	char	*content;

	while (command->str[i])
	{
		content = final_expansion(mini, command->str[i]);
		if (!content)
			print_error(mini, 2);
		if (write(1, content, ft_strlen(content)) == -1)
			print_error(mini, 0);
		if (i < wc - 1)
			if (write(1, " ", 1) == -1)
				return (print_error(mini, 0), 0);
		i++;
		free(content);
	}
	if (write(1, "\n", 1) == -1)
		return (print_error(mini, 0), 0);
	return (1);
}

//in this function, the argument *command is type: mini->cmd
//(we could only work with 1 argument)
//for example: echo hello     world     $PWD
//index are  :   0    1         2         3
//the result : hello world /path/
int	builtin_echo(t_mini *mini, t_cmd *command)
{
	int		wordcount;
	int		i;

	wordcount = lines_counter(command->str);
	i = 1;
	if (command->str[i] && (ft_strcmp_simple(command->str[i], "-n") == 0
			|| check_flag(command->str[i]) == 1))
		return (builtin_echo_flag_n(mini, command, 2, wordcount));
	else
		return (builtin_echo_without_flag(mini, command, i, wordcount));
}
