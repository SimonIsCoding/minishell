/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/10 14:30:58 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    run_expander(t_mini *mini, t_cmd *cmd)
{
    t_cmd   *tmp;

    tmp = cmd;
    tmp->str = expand_cmd_line(mini, tmp->str); // contiene char** cmd line ==> [[cat] [hola.c]] [[echo] [$HELLO]]
    while (tmp->redirections)
    {
        if (tmp->redirections->token != HDOC) // lo unico que no se expande es el eof de hdoc, todo lo demas son posibles archivos
            tmp->redirections->str = expand_str_line(mini, tmp->redirections->str); // lexer->token && lexer->str(filename) char *
        tmp->redirections = tmp->redirections->next;
    }
}

// expand cmd line. only cmd flags and args of the cmd
char	**expand_cmd_line(t_mini *mini, char **str)
{
    char    *new;
    int     i;

    new = NULL;
    i = 0;
    while (str[i])
    {
        //if (is_dollar(str[i]) != 0 && str[i][is_dollar(str[i])] != '\0' && str[i][is_dollar(str[i]) - 2])
        //{
        new = final_expansion(mini, str[i]);
       printf("NEW cmd_line: %s\n", new);
        free(str[i]);
        str[i] = new;
        // ft_strdup(new)
        // free(new);
        //}
        i++;
    }
    return (str);
}


// expand str==> filename
char    *expand_str_line(t_mini *mini, char *str)
{
    char    *new;

    new = NULL;
    //if (is_dollar(str) != 0 && str[is_dollar(str)] != '\0' && str[is_dollar(str) - 2])
    //{
    new = final_expansion(mini, str);
    printf("NEW : %s\n", new);
    free(str);
    str = new;
    //}
    return (str);
}
