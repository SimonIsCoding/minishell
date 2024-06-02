/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:54:26 by anovio-c          #+#    #+#             */
/*   Updated: 2024/01/14 17:32:27 by asinovio-c       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	void	*dst;

	dst = dest;
	if (!dest && !src)
		return (dest);
	if (dest > src)
	{
		while (count--)
			*((char *)dest + count) = *((char *)src + count);
	}
	else if (dest < src)
	{
		while (count--)
			*(char *)dest++ = *(char *)src++;
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
:x
int	main(void)
{
	char	src[] = "Hello, World!";
	char	dest[20];

	printf("Before the copy:\n");
	printf("Src: %s\n", src);
	printf("Dest: %s\n", dest);

	ft_memmove(src + 6, src, strlen(src) - 6);

	printf("After the copy:\n");
	printf("Src: %s\n", src);
	printf("Dest: %s\n", dest);

	return (0);
}*/
