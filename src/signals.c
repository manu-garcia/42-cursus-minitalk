/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:09:41 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/05 21:57:41 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc
#include <string.h>	// memset
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include "error.h"
#include "state.h"
#include "signals.h"

void	setup_user_signal_handler(
	void (*sa_sigaction_fn)(int, siginfo_t *, void *)
)
{
	struct sigaction	signal_action;

	signal_action.sa_sigaction = sa_sigaction_fn;
	signal_action.sa_flags = SA_SIGINFO;
	sigemptyset(&signal_action.sa_mask);
	sigaddset(&signal_action.sa_mask, SIGUSR1);
	sigaddset(&signal_action.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
}

void	setup_cleanup_signal_handler(void (*sa_handler_fn)(int))
{
	struct sigaction	signal_action;

	signal_action.sa_handler = sa_handler_fn;
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = 0;
	sigaction(SIGINT, &signal_action, NULL);
}
