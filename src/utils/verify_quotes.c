/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:58:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/26 14:24:41 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"
#include <stdio.h>

// NEW NEW NEW NEW

/*void	print_error(char *str)
{
	perror(str);
//	exit(1);//you don't have to exit => tu have to display a newline
}

void	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34)//"
		{
			i++;
			while (line[i] && line[i] != 34)
			{
//				write(1, "out\n", 4);
				if (line[i] == 92 && i < (int)ft_strlen(line) - 1)
					i++;
				i++;//in this condition, we can also add a string to catch what's inside the quotes
			}
			if (line[i] == '\0')
				print_error("The line was not well written. Please try again.");
		}
		else if (line[i] == 39)//'
		{
			i++;
			while (line[i] && line[i] != 39)
			{
				if (line[i] == 92 && i < (int)ft_strlen(line) - 1)
					i++;
				i++;//in this condition, we can also add a string to catch what's inside the quotes
			}
			if (line[i] == '\0')
				print_error("The line was not well written. Please try again.");
		}
		i++;
	}
}*/

static int find_married_quote(char *line, int start_index, int *num_quotes, int delimiter)
{
    int index;

    index = start_index + 1;
    *num_quotes += 1; // Incrementa el contador de quotes
    while (line[index] && line[index] != delimiter)
        index++;
    if (line[index] == delimiter)
        *num_quotes += 1; // Incrementa el contador de delimitadores si se encuentra una coincidencia
    return (index - start_index); // Devuelve la longitud hasta el delimitador coincidente
}

int check_quotes_is_married(char *line)
{
    int i;
	int	offset;
    int single_quote_count = 0;
    int double_quote_count = 0;

	i = 0;
    single_quote_count = 0;
    double_quote_count = 0;
    while (line[i])
	{
        if (line[i] == '"') 
		{
            offset = find_married_quote(line, i, &double_quote_count, '"');
            i += offset;
        }
		else if (line[i] == '\'')
		{
            offset = find_married_quote(line, i, &single_quote_count, '\'');
            i += offset;
        }
        i++;
    }
    // Verifica si hay un número impar de comillas
    if ((double_quote_count % 2 != 0) || (single_quote_count % 2 != 0))
        return 0;
    return 1;
}