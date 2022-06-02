/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:33:06 by manu              #+#    #+#             */
/*   Updated: 2022/06/02 20:30:50 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc
#include <string.h>	// memset
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include "communication.h"

#define MESSAGE_BUFFER_SIZE	500

typedef struct s_state {
	char	message_char;
	char	*message;
	int		message_len;
	int		message_buffer_size;
	int		n_bits_received;
}	t_state;

static t_state	*g_state;

t_state	*get_state(void)
{
	if (!g_state)
	{
		g_state = (t_state *) malloc(sizeof(t_state));
		if (!g_state)
		{
			printf("Error not enough memory to allocate state.\n");
			exit(3);
		}
		memset(g_state, 0, sizeof(t_state));
	}
	return (g_state);
}

void	add_message_char(t_state *state)
{
	char	*message_aux;

	if (!state)
		return ;
	if (!state->message)
	{
		state->message_buffer_size = MESSAGE_BUFFER_SIZE;
		state->message_len = 0;
		state->message = (char *) malloc(state->message_buffer_size);
	}
	if (state->message_len >= state->message_buffer_size)
	{
		message_aux = state->message;
		state->message_buffer_size += MESSAGE_BUFFER_SIZE;
		state->message = (char *) malloc(state->message_buffer_size);
		strncpy(state->message, message_aux, state->message_len);
		free(message_aux);
	}
	state->message[state->message_len] = state->message_char;
	state->message_len++;
}

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
	t_state	*state;

	(void)ucontext;
	state = get_state();
	if (!state)
	{
		printf("\nCritical error getting comunication state. Exiting...\n");
		exit(1);
	}
	if (signum == SIGNAL_BIT_ONE)
		state->message_char = set_bit(state->message_char, state->n_bits_received);
	state->n_bits_received++;
	if (state->n_bits_received == 8)
	{
		add_message_char(state);
		if (state->message_char == '\0')
		{
			printf("%s\n", state->message);
			state->message[0] = '\0';
			state->message_len = 0;
		}
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
	printf("Server finished successfully.\n");
	return (0);
}
