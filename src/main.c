/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/31 20:19:40 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	init_mini(&mini, env);
	mini_live(&mini);
	return (0);
}
