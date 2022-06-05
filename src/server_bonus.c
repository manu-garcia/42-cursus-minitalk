/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:33:06 by manu              #+#    #+#             */
/*   Updated: 2022/06/05 23:06:21 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// atoi exit
#include <unistd.h>	// pause usleep getpid
#include <errno.h>	// errno

#include "error.h"
#include "message.h"
#include "process.h"
#include "signals.h"
#include "state.h"
#include "state_char.h"
#include "state_message.h"
#include "ft_printf.h"

static void	handle_signals(void)
{
	while (pause() == PAUSE_SUCCESS)
		;
}

static void	on_cleanup_signal_action_received(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\nMemory clean-up");
		free_state_memory();
	}
	ft_printf("\nServer finished successfully\n");
	exit(0);
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
			ft_printf("%s\n", state->message);
			reset_message(state);
		}
		reset_message_char(state);
	}
	if (usleep(100) == -1)
		ft_printf("\nError sleeping");
	if (!send_acknowledge(siginfo->si_pid))
		ft_printf("\nError sending acknowledge to client");
}

int	main(void)
{
	show_process_pid();
	setup_user_signal_handler(on_user_signal_action_received);
	setup_cleanup_signal_handler(on_cleanup_signal_action_received);
	handle_signals();
	return (0);
}
