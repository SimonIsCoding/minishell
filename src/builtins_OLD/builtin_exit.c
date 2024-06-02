/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:08:54 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/13 13:10:05 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we don't need a function for this
void	builtin_exit(void)
{
	exit(0);//you have to go out with the exit status!
	//exit(EXIT_STATUS);
}
