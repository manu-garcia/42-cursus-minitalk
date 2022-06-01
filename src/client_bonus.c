/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:32:58 by manu              #+#    #+#             */
/*   Updated: 2022/06/01 20:29:01 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "communication.h"

/*
struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
*/
void	on_user_signal_action_received(
	int signum,	siginfo_t *siginfo, void *ucontext
)
{
	(void)siginfo;
	(void)ucontext;
	printf("Signal received on client (%d).!\n", signum);
	if (signum == SIGUSR1)
		printf("Received SIGUSR1!\n");
	if (signum == SIGUSR2)
		printf("Received SIGUSR2!\n");
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

void	setup_user_signal_handler(void)
{
	struct sigaction	user_signal_action;

	user_signal_action.sa_sigaction = on_user_signal_action_received;
	sigemptyset(&user_signal_action.sa_mask);
	user_signal_action.sa_flags = 0;
	sigaction(SIGUSR1, &user_signal_action, NULL);
	sigaction(SIGUSR2, &user_signal_action, NULL);
}

void	send_bit(int server_pid, t_e_Bit bit)
{
	kill(server_pid, bit);
}

int	validate_input_parameters(int argc, char *argv[])
{
	(void)argv;
	if (argc != 3)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{	
	int	server_pid;

	if (!validate_input_parameters(argc, argv))
	{
		printf("Parameters error. Expected usage:\n");
		printf("client_bonus server_pid \"message\"\n");
		exit(1);
	}
	server_pid = get_server_pid(argv);
	if (!server_pid)
	{
		printf("Invalid server_pid.\n");
		exit(2);
	}
	setup_user_signal_handler();
	send_bit(server_pid, ONE);
	send_bit(server_pid, ZERO);
	return (0);
}
