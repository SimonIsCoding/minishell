/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:53:12 by anovio-c          #+#    #+#             */
/*   Updated: 2024/01/15 13:21:50 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_free_double_array(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
    free(str);
}