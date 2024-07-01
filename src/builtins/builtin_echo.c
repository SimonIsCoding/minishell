/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/19 17:36:36 by simarcha         ###   ########.fr       */
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

//in this function, the argument *command is type: mini->cmd
//(we could only work with 1 argument)
//for example: echo hello     world     $PWD
//index are  :   0    1         2         3
//the result : hello world /path/
int	builtin_echo(t_mini *mini, t_cmd *cmd)
{
	int	flag;
	int	i;

	(void)mini;
	flag = 0;
	i = 1;
	while (cmd->str[i] && (ft_strcmp_simple(cmd->str[i], "-n") == 0
			|| check_flag(cmd->str[i])))
	{
		flag = 1;
		i++;
	}
	while (cmd->str[i])
	{
		printf("%s", cmd->str[i]);
		if (cmd->str[i][0] && cmd->str[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
