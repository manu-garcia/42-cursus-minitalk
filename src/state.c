/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:53:34 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/06 00:06:28 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// exit malloc
#include <string.h>	// memset
#include "error.h"
#include "state.h"
#include "ft_memory.h"

static t_state	*g_state;

t_state	*get_state(void)
{
	if (!g_state)
	{
		g_state = (t_state *) malloc(sizeof(t_state));
		if (!g_state)
			exit_with_memory_error();
		ft_memset(g_state, 0, sizeof(t_state));
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
