/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:23:08 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/04 18:46:41 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

typedef enum e_signal {
	SIGNAL_SET_BIT_ZERO = SIGUSR1,
	SIGNAL_SET_BIT_ONE = SIGUSR2,
	SIGNAL_ACKNOWLEDGE = SIGUSR2,
}	t_signal;

void	setup_user_signal_handler(void);
void	setup_cleanup_signal_handler(void);

#endif
