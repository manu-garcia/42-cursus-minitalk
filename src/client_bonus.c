/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:32:58 by manu              #+#    #+#             */
/*   Updated: 2022/06/02 19:44:50 by manu             ###   ########.fr       */
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
void	on_user_signal_action_received(
	int signum,	siginfo_t *siginfo, void *ucontext
)
{
	(void)siginfo;
	(void)ucontext;
	// printf("Signal received on client (%d).!\n", signum);
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
	user_signal_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &user_signal_action, NULL);
	sigaction(SIGUSR2, &user_signal_action, NULL);
}

int	is_bit_set(char value, int bit_position)
{
	return ((value) & (1 << bit_position));
}

void	send_user_signal(int process_pid, t_signal signal)
{
	if (kill(process_pid, signal) == -1)
	{
		printf("\nError sending signal. Errno: %d\n", errno);
		return ;
	}
	pause();
	if (usleep(100) == -1)	// usleep works, whereas pause hangs!!
		printf("Error sleeping.\n");
}

void	send_char(int server_pid, char c)
{
	int	bit_position;

	bit_position = 0;
	while (bit_position < 8)
	{
		if (is_bit_set(c, bit_position))
			send_user_signal(server_pid, SIGNAL_BIT_ONE);
		else
			send_user_signal(server_pid, SIGNAL_BIT_ZERO);
		bit_position++;
	}
}

void	send_string(int server_pid, char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		send_char(server_pid, *str);
		str++;
	}
	send_char(server_pid, '\0');
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

	printf("Process PID: %d\n", getpid());
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
	send_string(server_pid, argv[2]);
	printf("Message sent successfully!!!.\n");
	return (0);
}
