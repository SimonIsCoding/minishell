/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asiercara <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:55:08 by asiercara         #+#    #+#             */
/*   Updated: 2024/03/07 10:33:03 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	value_in_base(const char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
			break ;
		i++;
	}
	if (base[i] != '\0')
		return (i);
	else
		return (-1);
}

static int	atoi_check_invalid(const char *str)
{
	int	i;
	int	j;

	if (str[0] == '\0' || str[1] == '\0')
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' || str[i] == '+')
			return (1);
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		j = i + 1;
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

unsigned int	ft_atoi_base(const char *str, const char *base)
{
	unsigned int	value;

	value = 0;
	if (!atoi_check_invalid(base))
	{
		while ((*str == ' ' || (*str >= 9 && *str <= 13)))
			str++;
		if (!ft_strncmp(str, "0x", 2)
			&& !ft_strncmp(base, "0123456789ABCDEF", 16))
			str += 2;
		while (*str != '\0')
		{
			if (value_in_base(ft_toupper(*str), base) >= 0)
				value = (value * ft_strlen(base))
					+ value_in_base(ft_toupper(*str), base);
			else
				break ;
			str++;
		}
	}
	return (value);
}

/*static int	is_valid(int c, int len_base)
{
	if (ft_isdigit(c))
		return (c - '0' < len_base);
	if (ft_islower(c))
		return (c - 'a' + 10 < len_base);
	if (ft_isuper(c))
		return (c - 'A' + 10 < len_base);
	return (0);
}

static int	get_value(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	if (ft_islower(c))
		return (c - 'a' + 10);
	return (c - 'A' + 10);
}

int	ft_atoi_base(char *str, char *base)
{
	int	len_base;
	int	res;
	int	sign;
	int i;

	if (str == NULL || !*str)
		return (0);
	len_base = ft_strlen(base);
	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (is_valid(str[i], len_base))
	{
		res = res * len_base + (get_value(str[i]));
		i++;
	}
	return (sign * res);
}*/
/*
#include <stdio.h>

int	main(void)
{
	char *str = "23CACE";
	int	res = ft_atoi_base(str, "0123456789");
	printf("%X", res);
   return (0);
}*/
