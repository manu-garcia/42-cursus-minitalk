/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:02:53 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/05 22:17:37 by manu             ###   ########.fr       */
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

#endif
