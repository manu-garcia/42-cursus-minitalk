/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:53:34 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/04 18:58:01 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// atoi exit malloc
#include <string.h>	// memset
#include "error.h"
#include "bit.h"
#include "state.h"

#define MESSAGE_BUFFER_SIZE	500

static t_state	*g_state;

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

void	free_state_memory(void)
{
	t_state	*state;

	state = get_state();
	if (!state)
		exit_with_internal_error();
	if (state->message)
	{
		free(state->message);
		state->message = NULL;
	}
	free(state);
	state = NULL;
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
