/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 15:12:46 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **original_env)
{
	t_mini		mini;

	if ((argc != 1 && argv[0]))
	{
		printf("Don't write any argument\n");
		exit(0);
	}
	mini.env = NULL;
	if (!original_env[0])
		exit(1);
	else
	{
		create_builtin_lst(&mini, &mini.env, original_env);
		concat_lst_env(&mini);
	}
	mini.error_code = 0;
	init_mini(&mini, original_env);
	if (!save_pwd(&mini, original_env))
		print_error(&mini, RANDOM);
	mini.error_code = 0;
	mini_live(&mini);
	return (0);
}
