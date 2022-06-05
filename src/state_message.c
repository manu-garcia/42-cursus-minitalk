/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:53:34 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/05 23:51:49 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// exit malloc
#include <string.h>	// strncpy
#include "error.h"
#include "state.h"
#include "state_char.h"
#include "ft_memcpy.h"

#define MESSAGE_BUFFER_SIZE	500

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
		ft_memcpy(state->message, message_aux, state->message_len);
		free(message_aux);
	}
	state->message[state->message_len] = state->message_char;
	state->message_len++;
}

void	reset_message(t_state *state)
{
	if (!state)
		exit_with_internal_error();
	state->message[0] = '\0';
	state->message_len = 0;
	reset_message_char(state);
}
