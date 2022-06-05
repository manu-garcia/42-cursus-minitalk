/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_message.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:02:53 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/05 22:17:26 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_MESSAGE_H
# define STATE_MESSAGE_H

# include "signals.h"

void	add_char_to_message(t_state *state);
void	reset_message(t_state *state);

#endif
