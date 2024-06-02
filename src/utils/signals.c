/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:33:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/18 18:33:48 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void    sigint_handler(int signal) //duante la ejecucion, de hdoc o de cmd, diferenciar ambas
{   
    if (!g_global_var.inside_hdoc)
        ft_putstr_fd("\n", STDERR_FILENO); 
    if (g_global_var.inside_hdoc == 1 && g_global_var.inside_cmd == 1)//g_global_var.inside_cmd == 1)
    {
        g_global_var.outside_hdoc = 1;
        rl_replace_line("", 0);
		rl_redisplay();
        rl_done = 1;
        return ;
    }
    rl_on_new_line(); // resetear el estado interno de Readline para prepararse para una nueva línea de entrada
    rl_replace_line("", 0); //Cuando se necesita cambiar el contenido de la línea actual que el usuario está 
                            //editando. Por ejemplo, para borrar la línea actual o para poner un texto específico en ella.
	rl_redisplay(); //se desea que esos cambios se muestren inmediatamente al usuario
    (void)signal;  // Para evitar una advertencia del compilador sobre el parámetro no utilizado
}

void    init_signals(void)
{
    rl_event_hook = event;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}