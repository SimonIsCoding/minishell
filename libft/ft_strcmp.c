/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asiercara <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:41:52 by asiercara         #+#    #+#             */
/*   Updated: 2024/06/10 19:05:47 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2 || (!s1 && !s2))
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0'
		&& ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	if ((s1[i] - s2[i] == 0) && ft_strlen(s1) == ft_strlen(s2))
		return (0);
	else
		return (1);
}
