/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:02:53 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/04 18:55:24 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include "signals.h"

typedef struct s_state {
	char	message_char;
	char	*message;
	int		message_len;
	int		message_buffer_size;
	int		n_bits_received;
}	t_state;

t_state	*get_state(void);
void	free_state_memory(void);
void	set_bit_to_char(t_state *state, t_signal signal);
int		is_char_completed(t_state *state);
void	add_char_to_message(t_state *state);
int		is_final_char(t_state *state);
void	reset_message(t_state *state);
void	reset_message_char(t_state *state);

#endif
