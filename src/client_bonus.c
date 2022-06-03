/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:32:58 by manu              #+#    #+#             */
/*   Updated: 2022/06/03 19:56:57 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
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

int	is_bit_set(char value, int bit_position)
{
	return ((value) & (1 << bit_position));
}

int	send_user_signal(int process_pid, t_signal signal)
{
	if (kill(process_pid, signal) == -1)
	{
		printf("\nError sending signal. Errno: %d", errno);
		return (1);
	}
	if (pause() != PAUSE_SUCCESS)
		printf("\nError in pause");
	if (usleep(100) == -1)
		printf("\nError sleeping");
	return (0);
}

void	send_char(int process_id, char c)
{
	int	bit_position;

	bit_position = 0;
	while (bit_position < 8)
	{
		if (is_bit_set(c, bit_position))
			send_user_signal(process_id, SIGNAL_SET_BIT_ONE);
		else
			send_user_signal(process_id, SIGNAL_SET_BIT_ZERO);
		bit_position++;
	}
}

void	send_message_string(int process_id, char *str)
{
	if (!str)
	{
		printf("\nNothing to be sent");
		return ;
	}
	while (*str)
	{
		send_char(process_id, *str);
		str++;
	}
	send_char(process_id, FINAL_MESSAGE_CHAR);
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

	printf("\nProcess PID: %d", getpid());
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
