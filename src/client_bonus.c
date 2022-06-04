/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:32:58 by manu              #+#    #+#             */
/*   Updated: 2022/06/04 18:55:47 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// printf
#include <stdlib.h>	// atoi exit
#include <unistd.h>	// pause usleep getpid
#include <errno.h>	// errno
#include "communication.h"
#include "error.h"
#include "bit.h"
#include "process.h"
#include "message.h"

void	on_acknowledge_signal_action_received(
	int signum,	siginfo_t *siginfo, void *ucontext
)
{
	(void)signum;
	(void)siginfo;
	(void)ucontext;
	printf("\nAcknowledge received from server");
}

int	get_server_pid(char *argv[])
{
	int	server_pid;

	if (!argv || !argv[1])
		return (0);
	server_pid = atoi(argv[1]);
	if (!server_pid)
		return (0);
	return (server_pid);
}

void	setup_acknowledge_signal_handler(void)
{
	struct sigaction	signal_action;

	signal_action.sa_sigaction = on_acknowledge_signal_action_received;
	signal_action.sa_flags = SA_SIGINFO;
	sigemptyset(&signal_action.sa_mask);
	sigaddset(&signal_action.sa_mask, SIGUSR1);
	sigaddset(&signal_action.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
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
		printf("\nParameters error. Expected usage:");
		printf("\nclient_bonus server_pid \"message\"\n");
		exit(1);
	}
	server_pid = get_server_pid(argv);
	if (!server_pid)
	{
		printf("\nInvalid server process id\n");
		exit(2);
	}
	setup_acknowledge_signal_handler();
	send_message_string(server_pid, argv[2]);
	printf("\nMessage sent successfully!!!\n");
	return (0);
}
