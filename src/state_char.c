/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:53:34 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/05 22:12:38 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "bit.h"
#include "state.h"

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
