/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/20 11:54:14 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char    *is_dollar_sign(char *str)
{
    while (*str)
    {
        if (*str == '$')
            return (str + 1);
        str++;
    }
    return (NULL);
}*/

int is_dollar(char *str)
{
    int i;

    i = 0;
    while (*str)
    {
        if (*str == '$')
            return (i + 1);
        str++;
        i++;
    }
    return (0);
}

int is_equal(char *str)
{
    int i;

    i = 0;
    while (*str)
    {
        if (*str == '=')
            return (i + 1);
        str++;
        i++;
    }
    return (0);
}
