/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/20 11:54:14 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    run_expander(t_mini *mini, t_cmd *cmd)
{
    t_cmd   *tmp;

    tmp = cmd;
    tmp->str = expand_cmd_line(mini, tmp->str);
    while (tmp->redirections)
    {
        if (tmp->redirections->token != HDOC) // lo unico que no se expande es el eof de hdoc, todo lo demas son posibles archivos
            tmp->redirections->str = expand_str_line(mini, tmp->redirections->str);
        tmp->redirections = tmp->redirections->next;
    }
}

char	**expand_cmd_line(t_mini *mini, char **str)
{
    char    *new;
    int     i;

    new = NULL;
    i = 0;
    while (str[i])
    {
        if (is_dollar(str[i]) != 0 && str[i][is_dollar(str)] != '\0' && str[i][is_dollar(str[i]) - 2])
        {
            new = search_and_replace_variable(mini, str[i]);
            free(str[i]);
            str[i] = new;
        }
        i++;
    }
}

char    *expand_str_line(t_mini *mini, char *str)
{
    char    *new;

    new = NULL;
    if (is_dollar(str) != 0 && str[is_dollar(str)] != '\0' && str[is_dollar(str) - 2])
    {
        new = search_and_replace_variable(mini, str);
        free(str);
        str = new;
    }

}