/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:34:18 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/04 18:42:17 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>	// errno
#include <stdio.h>	// printf
#include <unistd.h>	// pause usleep getpid

#include "bit.h"
#include "communication.h"
#include "signals.h"
#include "error.h"

static int	send_user_signal(int process_pid, t_signal signal)
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

static void	send_char(int process_id, char c)
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
