/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:34:18 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/05 23:05:51 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>	// errno
#include <unistd.h>	// pause usleep getpid

#include "bit.h"
#include "signals.h"
#include "error.h"
#include "ft_printf.h"

static int	send_user_signal(int process_pid, t_signal signal)
{
	if (kill(process_pid, signal) == -1)
	{
		ft_printf("\nError sending signal. Errno: %d", errno);
		return (1);
	}
	if (pause() != PAUSE_SUCCESS)
		ft_printf("\nError in pause");
	if (usleep(100) == -1)
		ft_printf("\nError sleeping");
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
		ft_printf("\nNothing to be sent");
		return ;
	}
	while (*str)
	{
		send_char(process_id, *str);
		str++;
	}
	send_char(process_id, FINAL_MESSAGE_CHAR);
}

int	send_acknowledge(int process_id)
{
	if (!process_id)
	{
		ft_printf("\nInvalid process id sending acknowledge");
		return (0);
	}
	if (kill(process_id, SIGNAL_ACKNOWLEDGE) == -1)
	{
		ft_printf("\nError sending ack. Errno: %d", errno);
		return (0);
	}
	return (1);
}
