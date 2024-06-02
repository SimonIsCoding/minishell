/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/13 12:45:01 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	s_builtin
{
	char				*key;//the name of the variable in env
	char				*value;
	int					index;//the index of the node
//	int					checker;//to check if the builtin is ENV or EXPORT
	struct s_builtin	*next;
}				t_builtin;//for ENV and EXPORT builtins

t_builtin	*ft_lstnew_builtin(char *str, int i);
char		*get_key_from_env(char *str);
char		*get_value_from_env(char *str);
void		print_list(t_builtin **lst_env);
void		ft_lstadd_back_builtin(t_builtin **lst, t_builtin *new);
void		ft_lstclear_builtin(t_builtin **lst);
t_builtin	*create_builtin_lst(char **env);
t_builtin	*init_builtin_node(char **env);
int			ft_lstsize_builtin(t_builtin *lst);
//void		unset_builtin(t_builtin **head, char *str);



// mirar ft_strcmp libft minishell

/*int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}*/

//I HAVE TO REMOVE THE NODE->KEY = _ BECAUSE IT ISN'T IN EXPORT
void	remove_node(t_builtin **head)
{
	t_builtin	*current;
	t_builtin	*previous;

	previous = NULL;
	current = *head;
	if (*head == NULL)
		return ;
	while (current)
	{
		if (ft_strcmp(current->key, "_") == 0)
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

//there is a second argument whereas I really need one because I had norminette
//issues. This second argument has to be set as NULL
t_builtin	*sort_ascii(t_builtin *lst_export, t_builtin *sorted)
{
	t_builtin	*current;
	t_builtin	*the_next;
	t_builtin	*tmp;

	current = lst_export;
	while (current)
	{
		the_next = current->next;
		if (!sorted || ft_strcmp(current->key, sorted->key) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next && ft_strcmp(current->key, tmp->next->key) >= 0)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = the_next;
	}
	return (sorted);
}

//we want to check if everything is well written before the '='.
//It means if there is a key name to the str.
int	check_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		if (i == 0 && str[i] == 34)
			i++;
		else if (i == 0 && str[i] != '_' && !ft_isalpha(str[i]))
			return (perror("export: not a valid identifier"), 0);
		i++;
	}
	if (i > 0 && str[i] == '=' && str[i - 1] == '+')
		return (2);
	if (i > 0)
		return (1);
	return (0);
}

//in this function, str refers to the new export variable. ie: 'abc=test'
//we may need an extra variable to know if there is a node to add or not
void	add_export_variable(t_builtin *lst, char *str)
{
	t_builtin	*new_node;
	int			lst_size;

	lst_size = ft_lstsize_builtin(lst);
	new_node = ft_lstnew_builtin(str, lst_size - 1);
	if (!new_node)
		perror("failed creating the new variable for the export");
	ft_lstadd_back_builtin(&lst, new_node);
	//sort the list
}

void	join_values(t_builtin **lst_export, char *str)
{
	t_builtin	*tmp;
	char		*key_str;
	char		*value_str;
	char		*value_node;

	key_str = get_key_from_env(str);
	if (!key_str)
		return ;
	value_str = get_value_from_env(str);
	if (!value_str)
		return (free(key_str));
	tmp = *lst_export;
	while (ft_strcmp(tmp->key, key_str))//while it's different
		tmp = tmp->next;
	value_node = tmp->value;
	free(tmp->value);
	tmp->value = ft_strjoin(value_node, value_str);
	free(key_str);
	free(value_str);
}

int	builtin_export(char **env, char *str)
{
	t_builtin	*lst_export;
	t_builtin	*tmp;

	lst_export = create_builtin_lst(env);
	if (!lst_export)
		perror("error creating the list for the env");
	if (str != NULL)
	{
		if (check_variable(str) == 1)
			add_export_variable(lst_export, str);
		else if (check_variable(str) == 2)
			join_values(&lst_export, str);
	}
	lst_export = sort_ascii(lst_export, NULL);
	tmp = lst_export;
	remove_node(&tmp);
	//before printing the list, we want to free the _ node
//	unset_builtin(&tmp, "HOME");
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
//	lst_export = tmp;
	ft_lstclear_builtin(&lst_export);//this line will be written at the very
	//last step of the pgrm. Just before return (0) of the main
	return (1);
}

/*int	main(int argc, char **argv, char **env)
{
//	builtin_export(env, "PAGER+=TEEEEEEEEEEEEEEEST");
	builtin_export(env, "PAGER+=SIIIIIIIIIIIIIIMON");
	argc = 0;
	argv[0] = "./a.out";
//	unset_builtin(env, "PAGER");
//	printf("%lu\n", sizeof(t_builtin));
//	printf("%p\n", argc);
	return (0);
}*/












/*void	builtin_export(char **env, char *str)
{
	t_builtin	**lst_export;
	t_builtin	*tmp;
	char		*key_str;

	*lst_export = create_builtin_lst(env);
	if (!(*lst_export))
		perror("error creating the list for the env");
	if (str != NULL)
	{
		if (check_variable(str) == 1)
			add_export_variable(*lst_export, str);
		else if (check_variable(str) == 2)
		{
			key_str = get_key_from_env(str);
			if (!key_str)
				return ;
//			tmp = *lst_export;
			while (ft_strcmp((*lst_export)->key, key_str))//while it's different
				*lst_export = (*lst_export)->next;
			(*lst_export)->value = ft_strjoin((*lst_export)->value, key_str);
		}
	}
//	lst_export = sort_ascii(lst_export);
	tmp = *lst_export;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	ft_lstclear_builtin(lst_export);
}
*/
