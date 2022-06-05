/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:32:58 by manu              #+#    #+#             */
/*   Updated: 2022/06/06 00:10:52 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// exit
#include <unistd.h>	// pause usleep getpid
#include <errno.h>	// errno
#include "error.h"
#include "bit.h"
#include "process.h"
#include "message.h"
#include "signals.h"
#include "ft_printf.h"
#include "ft_atoi.h"

void	on_acknowledge_signal_action_received(
	int signum,	siginfo_t *siginfo, void *ucontext
)
{
	(void)signum;
	(void)siginfo;
	(void)ucontext;
	ft_printf("\nAcknowledge received from server");
}

int	get_server_pid(char *argv[])
{
	int	server_pid;

	if (!argv || !argv[1])
		return (0);
	server_pid = ft_atoi(argv[1]);
	if (!server_pid)
		return (0);
	return (server_pid);
}

int	validate_input_parameters(int argc, char *argv[])
{
	if (argc != 3)
		return (0);
	if (!argv[0] || !argv[1])
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	int	server_pid;

	show_process_pid();
	if (!validate_input_parameters(argc, argv))
	{
		ft_printf("\nParameters error. Expected usage:");
		ft_printf("\nclient_bonus server_pid \"message\"\n");
		exit(1);
	}
	server_pid = get_server_pid(argv);
	if (!server_pid)
	{
		ft_printf("\nInvalid server process id\n");
		exit(2);
	}
	setup_user_signal_handler(on_acknowledge_signal_action_received);
	send_message_string(server_pid, argv[2]);
	ft_printf("\nMessage sent successfully!!!\n");
	return (0);
}
