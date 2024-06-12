/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/12 12:07:00 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_var	g_global_var = {0, 0, 0, 0};

int	main(int argc, char **argv, char **env)
{
	t_mini		mini;
	t_builtin	*lst_env;

	if (argc != 1 && argv[0])
	{
		printf("Don't write any argument");
		exit(0);
	}
	lst_env = NULL;
	//mini.original_env = env;
	mini.env = create_builtin_lst(&mini, lst_env, env);
	concat_lst_env(&mini);
//	mini.error_code = 0;
	init_mini(&mini, env);
	mini_live(&mini);
	return (0);
}