/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:42:11 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/13 12:48:01 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void	print_error(char *str);

/*typedef struct s_simple_cmd
{
	char					**str;//array of cmd with flags
	int						(*builtin)(t_mini *, struct s_simple_cmd *);//
	int						num_redirections;
	char					*hd_filename;
	t_lexer					*redirections;
	struct s_simple_cmd		*next;
}				t_simple_cmd;
*/

void	builtin_echo(char **command, char *line)
{
	if (ft_strncmp(command[0], "echo", 4) == 0)
	{
		if (!ft_strncmp(command[1], "-n", 2))
		{
			if (write(1, line, ft_strlen(line)) == -1)//line means what's after echo => the characters we want to write
				print_error("write failed in src/builtin_echo");
		}
		else// if (ft_strncmp(command[1], "-n", 2))//if the flag is NOT -n
		{
			if (write(1, line, ft_strlen(line)) == -1)//line means what's after echo => the characters we want to write
				print_error("write failed in src/builtin_echo");
			if (write(1, "\n", 1) == -1)
				print_error("write failed in src/builtin_echo");
		}
	}
}

//I created another function for the ENV builtin but with lists
/*char	**builtin_env(char **env)//to free once used
{
	int		i;
	char	**result_env;

	i = 0;
	while (env[i])
		i++;
	result_env = malloc((i + 1) * sizeof(*result_env));
	if (!result_env)
		print_error("malloc failed in src/builtin_env");
	i = 0;
	while (env[i])
	{
		result_env[i] = ft_strdup(env[i]);
		if (!result_env[i])
			print_error("ft_strdup failed in src/builtin_env");
		i++;
	}
	result_env[i] = NULL;
	return (result_env);
}*/


/*
int	main(int argc, char **argv, char **env)
{
	int		x;
	char	**array_env;

	x = 0;
	array_env = builtin_env(env);
	if (!array_env)
		print_error("error for creating the array");
	while (array_env[x])
	{
		printf("%s\n", array_env[x]);
		x++;
	}
	return (0);
}*/


//we don't need a function for this
void	builtin_exit(void)
{
	exit(0);//you have to go out with the exit status!
	//exit(EXIT_STATUS);
}

char	*builtin_pwd(char **env)//to free after having used it
{
	int		i;
	char	*path_prefix;
	char	*result;

	path_prefix = ft_strdup("PWD=");
	if (!path_prefix)
		print_error("ft_strdup failed");
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], path_prefix, ft_strlen(path_prefix)) == 0)
		{
			free(path_prefix);
			result = ft_strdup(env[i] + 4);
			if (!result)
				print_error("ft_strdup failed");
			return (result);
		}
		i++;
	}
	return (NULL);
}

/*int	main(int argc, char **argv, char **env)
{
	printf("%s\n", builtin_pwd(env));
	return (0);
}*/

/*void	builtin_cd(char *path, char **env)
{
	
}*/

/*int	main(void)
{
	char	*path = "Users/simarcha/commonCore/";
	int		chdir_result;
	
	if (ft_strncmp(argv[0], "cd", 2) == 0)
	{	
		
		chdir_result = chdir("/");
		if (chdir_result == -1)
			print_error("chdir function failed");
		printf("chdir result = %i\n", chdir_result);
	}
	return (0);
}*/
