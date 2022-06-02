/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:33:06 by manu              #+#    #+#             */
/*   Updated: 2022/06/02 19:32:59 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc
#include <string.h>	// memset
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include "communication.h"

typedef struct s_state {
	char	message_char;
	int		n_bits_received;
}	t_state;

int	send_acknowledge(int process_id)
{
	if (!process_id)
	{
		printf("\nInvalid process id sending acknowledge to client.\n");
		return (0);
	}
	if (kill(process_id, SIGNAL_ACKNOWLEDGE) == -1)
	{
		printf("\nError sending ack. Errno: %d\n", errno);
		return (0);
	}
	return (1);
}

int	set_bit(char value, int bit_position)
{
	return (value | (0x01 << bit_position));
}

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
	int signum, siginfo_t *siginfo, void *ucontext
)
{
	static t_state	*state;

	(void)ucontext;
	if (!state)
	{
		state = (t_state *) malloc(sizeof(t_state));
		if (!state)
		{
			printf("Error not enough memory to allocate state.\n");
			exit(3);
		}
		memset(state, 0, sizeof(t_state));
	}
	if (signum == SIGNAL_BIT_ONE)
		state->message_char = set_bit(state->message_char, state->n_bits_received);
	state->n_bits_received++;
	if (state->n_bits_received == 8)
	{
		write(1, &state->message_char, 1);
		state->message_char = 0;
		state->n_bits_received = 0;
	}
	if (usleep(100) == -1)
		printf("Error sleeping.\n");
	if (!send_acknowledge(siginfo->si_pid))
		printf("\nError sending acknoledge to client. Client is blocked now.\n");
}

void	show_server_pid(void)
{
	printf("Server PID: %d\n", getpid());
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

void	handle_signals(void)
{
	while (pause() == PAUSE_SUCCESS)
		;
}

int	main(void)
{	
	show_server_pid();
	setup_user_signal_handler();
	handle_signals();
	return (0);
}
