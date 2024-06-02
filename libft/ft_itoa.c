/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:28:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/03/18 12:43:20 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static size_t	ft_num_len(long num)
{
	size_t	len;

	len = 0;
	if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static char	*ft_put_z(char *str)
{
	str = (char *)malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	long		tmp;
	size_t		len;

	str = NULL;
	tmp = n;
	len = ft_num_len(tmp);
	if (n == 0)
		return (ft_put_z(str));
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (tmp < 0)
	{
		tmp *= -1;
		str[0] = '-';
	}
	while (tmp > 0)
	{
		str[len--] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (str);
}*/

static size_t	get_str_size(int n)
{
	size_t	size;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		n++;
	size = 0;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*get_nums(char *str, int size, int n)
{
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		str[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;

	size = get_str_size(n);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[size] = '\0';
		return (str);
	}
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
	}
	if (n < 0)
		str[0] = '-';
	str = get_nums(str, size, n);
	str[size] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	int	n = 1345;
	int	nn = 0;
	int nnn = -2147483648;
	int nnnn = 65543767;
	long m = -2147483649;
	char	*res = ft_itoa(n);

	//printf("%s", res);
	printf("Num %d: %s\n", n, ft_itoa(n));
	printf("Num %d: %s\n", nn, ft_itoa(nn));
	printf("Num %d: %s\n", nnn, ft_itoa(nnn));
	printf("Num %d: %s\n", nnnn, ft_itoa(nnnn));
	printf("Num %ld: %s\n", m, ft_itoa(m));
	return (0);
}*/
