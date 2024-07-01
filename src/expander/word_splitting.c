/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:38:51 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/19 09:08:48 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**search_and_replace_variable_lead_zero(t_mini *mini,
				t_env_lst *env_variable, char *expand_name)
{
	t_env_lst	*tmp;
	char		**word_splitted;

	tmp = env_variable;
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, expand_name) == 0)
		{
			word_splitted = ft_split(tmp->value, ' ');
			if (!word_splitted)
				print_error(mini, 2);
			return (word_splitted);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static char	**free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}

//this function splits every word n our array by only one space
//if this is the last word, we won't add a space
static void	word_splitting(char **env_value, char *result, int *j)
{
	int	k;
	int	l;

	k = 0;
	while (env_value[k])
	{
		l = 0;
		while (env_value[k][l])
			result[(*j)++] = env_value[k][l++];
		if (k + 1 < lines_counter(env_value))
			result[(*j)++] = ' ';
		k++;
	}
}

int	expand_dollar_variable_lead_zero(t_mini *mini, char *str, int *i,
					char *result)
{
	int		j;
	char	*env_key;
	char	**env_value;

	j = 0;
	if (variable_existence(mini, str, *i) == 1)
	{
		env_key = catch_expansion_key(mini, str, i);
		if (!env_key)
			print_error(mini, 2);
		env_value = search_and_replace_variable_lead_zero(mini, mini->env,
				env_key);
		word_splitting(env_value, result, &j);
		free(env_key);
		free_array(env_value);
	}
	else
		forget_the_variable(str, i);
	result[j] = str[*i];
	return (j);
}

//this will expand the line when lead == 0.
//It means that we have to split the word by one space if there is various
//spaces in the same env
//watch out you allocate too much space for result.
char	*expand_the_line_lead_zero(t_mini *mini, char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = calculate_len_for_malloc(mini, str);
	result = malloc((j + 1) * sizeof(char));
	if (!result)
		print_error(mini, 2);
	j = 0;
	while (str[i] && i <= j)
	{
		if (str[i] == BACKSLASH)
			i++;
		if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH)
			|| (str[i] != '$'))
			result[j++] = str[i++];
		else if (i < (int)ft_strlen(str) - 1 && str[i] == '$'
			&& str[i + 1] == '?')
			j += expand_error_code(mini, &i, &result[j]);
		else
			j += expand_dollar_variable_lead_zero(mini, str, &i, &result[j]);
	}
	result[j] = '\0';
	return (result);
}
