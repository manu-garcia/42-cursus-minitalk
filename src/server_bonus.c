/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:33:06 by manu              #+#    #+#             */
/*   Updated: 2022/06/01 19:57:27 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
	int signum, siginfo_t *siginfo, void *ucontext
)
{
	(void)siginfo;
	(void)ucontext;
	printf("Signal received (%d).!\n", signum);
	if (signum == SIGUSR1)
		printf("Received SIGUSR1!\n");
	if (signum == SIGUSR2)
		printf("Received SIGUSR2!\n");
}

void	show_server_pid(void)
{
	printf("Server PID2: %d\n", getpid());
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
