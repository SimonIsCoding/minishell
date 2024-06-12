/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:47:43 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/12 12:07:05 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pre_executor(t_mini *mini)
{
	g_global_var.inside_cmd = 1;
	if (mini->pipes == 0)
		handle_single_cmd(mini, mini->cmd);
	else
		executor(mini);
	printf("pre_executor g_global_var.error_code = %i\n", g_global_var.error_code);
	//printf("mini->error = %i\n", mini->error_code);
	g_global_var.error_code = mini->error_code;
	g_global_var.inside_cmd = 0;
	return (0);
}

static int generate_random_number(void)
{
    static unsigned int seed = 12345;

    // Generador de números pseudoaleatorios lineal congruencial (LCG)
    seed = (seed * 1103515245 + 12345) & 0x7fffffff; // LCG: valores típicos para un generador simple
    return (seed % 10000);
}

char	*generate_filename(void)
{
	char		*str;
	char		*num;

	num = ft_itoa(generate_random_number());
	str = ft_strjoin("hdoc_tmp_file", num);
	free(num);
	return (str);
}

void	remove_eof_quotes(t_lexer *node)
{
	char	*str;
	
	str = node->str;
	free(node->str);
	if (str[0] == '\"' || str[0] == '\'')
		node->str = ft_substr(str, 1, ft_strlen(str) -1);
}

t_builtin	*find_node_path(t_builtin *lst_env)
{
	t_builtin	*tmp;

	tmp = lst_env;
	while (tmp)
	{
		if (ft_strcmp(lst_env->key, "PATH") == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*void	concat_lst_env(t_mini *mini)
{
	t_builtin	*tmp;
	int		len;
	int		i;

	tmp = mini->env;
	len = ft_lstsize_builtin(tmp);
	mini->env_cpy = (char **)malloc((len + 1) * sizeof(char *));
	if (!mini->env_cpy)
		print_error(mini, 2);
	i = 0;
	while (tmp)
	{
		mini->env_cpy[i] = (char *)malloc((ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2) * sizeof(char));
		if (!mini->env_cpy[i])
		{
			ft_free_double_array(mini->env_cpy);
			print_error(mini, 2);
		}
		if (tmp->value != NULL)
			mini->env_cpy[i] = ft_strjoin(tmp->key, ft_strjoin("=", tmp->value));
		else
			mini->env_cpy[i] = tmp->key;
		tmp = tmp->next;
		i++;
	}
	mini->env_cpy[len] = NULL;
}*/

void concat_lst_env(t_mini *mini)
{
	t_builtin	*tmp;
	int			i;
	char		*joined_value;
	char 		*temp;

	//if (mini->env_cpy)
	//	ft_free_double_array(mini->env_cpy);
	tmp = mini->env;
	mini->env_cpy = (char **)malloc((ft_lstsize_builtin(tmp) + 1) * sizeof(char *));
	if (!mini->env_cpy)
		print_error(mini, 2);
	i = 0;
	while (tmp)
	{
		joined_value = NULL;
		if (tmp->value != NULL)
		{
			temp = ft_strjoin("=", tmp->value);
			if (!temp)
			{
				ft_free_double_array(mini->env_cpy);
				print_error(mini, 2);
			}
			joined_value = ft_strjoin(tmp->key, temp);
			free(temp);
			if (!joined_value)
			{
				ft_free_double_array(mini->env_cpy);
				print_error(mini, 2);
			}
		}
		else
		{
			joined_value = ft_strdup(tmp->key);
			if (!joined_value)
			{
				ft_free_double_array(mini->env_cpy);
				print_error(mini, 2);
			}
		}
		mini->env_cpy[i] = joined_value;
		tmp = tmp->next;
		i++;
	} 
	mini->env_cpy[i] = NULL;
}