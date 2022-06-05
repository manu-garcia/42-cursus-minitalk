/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_char.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:02:53 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/05 22:16:45 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_CHAR_H
# define STATE_CHAR_H

# include "signals.h"

void	set_bit_to_char(t_state *state, t_signal signal);
int		is_char_completed(t_state *state);
int		is_final_char(t_state *state);
void	reset_message_char(t_state *state);

#endif
