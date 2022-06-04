/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:09:41 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/04 18:45:42 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc
#include <string.h>	// memset
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include "communication.h"
#include "error.h"
#include "state.h"
#include "signals.h"

static int	send_acknowledge(int process_id)
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

static void	on_user_signal_action_received(
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

static void	on_cleanup_signal_action_received(int signum)
{
	if (signum == SIGINT)
	{
		printf("\nMemory clean-up");
		free_state_memory();
	}
	printf("\nServer finished successfully");
	exit(0);
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
	struct sigaction	signal_action;

	signal_action.sa_handler = on_cleanup_signal_action_received;
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = 0;
	sigaction(SIGINT, &signal_action, NULL);
}
