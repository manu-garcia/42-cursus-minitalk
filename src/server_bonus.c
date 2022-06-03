/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:33:06 by manu              #+#    #+#             */
/*   Updated: 2022/06/03 20:12:48 by manu             ###   ########.fr       */
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
#define ERROR_MEMORY		1
#define ERROR_INTERNAL		2

typedef struct s_state {
	char	message_char;
	char	*message;
	int		message_len;
	int		message_buffer_size;
	int		n_bits_received;
}	t_state;

static t_state	*g_state;

void	exit_with_error_message(char *error_message, int exit_code)
{
	printf("\n%s\n", error_message);
	exit(exit_code);
}

void	exit_with_internal_error()
{
	exit_with_error_message(
		"Internal error getting comunication state",
		ERROR_INTERNAL);
}

void	exit_with_memory_error()
{
	exit_with_error_message(
		"Error not enough memory",
		ERROR_MEMORY);
}

t_state	*get_state(void)
{
	if (!g_state)
	{
		g_state = (t_state *) malloc(sizeof(t_state));
		if (!g_state)
			exit_with_memory_error();
		memset(g_state, 0, sizeof(t_state));
	}
	return (g_state);
}

void	add_char_to_message(t_state *state)
{
	char	*message_aux;

	if (!state)
		exit_with_internal_error();
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
		printf("\nInvalid process id sending acknowledge to client");
		return (0);
	}
	if (kill(process_id, SIGNAL_ACKNOWLEDGE) == -1)
	{
		printf("\nError sending ack. Errno: %d", errno);
		return (0);
	}
	return (1);
}

int	set_bit(char value, int bit_position)
{
	return (value | (0x01 << bit_position));
}

void	set_bit_to_char(t_state *state, t_signal signal)
{
	if (!state)
		exit_with_internal_error();
	if (signal == SIGNAL_SET_BIT_ONE)
		state->message_char = set_bit(
				state->message_char,
				state->n_bits_received);
	state->n_bits_received++;
}

void	reset_message_char(t_state *state)
{
	if (!state)
		exit_with_internal_error();
	state->message_char = 0;
	state->n_bits_received = 0;
}

void	reset_message(t_state *state)
{
	if (!state)
		exit_with_internal_error();
	state->message[0] = '\0';
	state->message_len = 0;
	reset_message_char(state);
}

int	is_char_completed(t_state *state)
{
	if (!state)
		exit_with_internal_error();
	if (state->n_bits_received == 8)
		return (1);
	return (0);
}

int	is_final_char(t_state *state)
{
	if (!state)
		exit_with_internal_error();
	if (state->message_char == FINAL_MESSAGE_CHAR)
		return (1);
	return (0);
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
		exit_with_internal_error();
	set_bit_to_char(state, signum);
	if (is_char_completed(state))
	{
		add_char_to_message(state);
		if (is_final_char(state))
		{
			printf("%s\n", state->message);
			reset_message(state);
		}
		reset_message_char(state);
	}
	if (usleep(100) == -1)
		printf("\nError sleeping");
	if (!send_acknowledge(siginfo->si_pid))
		printf("\nError sending acknowledge to client");
}

void	on_cleanup_signal_action_received(
	int signum, siginfo_t *siginfo, void *ucontext
)
{
	printf("\nServer finished successfully");
	// free memory
	exit(0);
}

void	show_process_pid(void)
{
	printf("\nProcess PID: %d\n", getpid());
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

void	setup_cleanup_signal_handler(void)
{
	struct sigaction	user_signal_action;

	user_signal_action.sa_sigaction = on_cleanup_signal_action_received;
	sigemptyset(&user_signal_action.sa_mask);
	user_signal_action.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &user_signal_action, NULL);
}

void	handle_signals(void)
{
	while (pause() == PAUSE_SUCCESS)
		;
}

int	main(void)
{	
	show_process_pid();
	setup_user_signal_handler();
	setup_cleanup_signal_handler();
	handle_signals();
	return (0);
}
