/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:14:30 by euyi              #+#    #+#             */
/*   Updated: 2022/09/12 15:43:18 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

int	main(int i, char *argv[], char *envp[])
{
	t_mini	shell;

	(void)argv;
	shell_env_switch(&shell, envp);
	init_signal(&shell);
	if (!envp_validator(&shell))
		return (0);
	while (!shell.exit)
	{
		parser_switch(&shell, 1);
		if (shell.exit == 2 && (shell_env_switch(&shell, NULL), 1))
			kill(0, SIGTERM);
		i = -1;
		while (shell.cmd && shell.cmd[++i])
		{
			shell.cycle = i;
			run_plugins(&shell);
		}
		while (wait(NULL) != -1)
			;
		parser_switch(&shell, 0);
	}
	shell_env_switch(&shell, NULL);
	return (0);
}
