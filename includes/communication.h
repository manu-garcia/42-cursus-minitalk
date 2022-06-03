/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   communication.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:32:38 by manu              #+#    #+#             */
/*   Updated: 2022/06/03 19:56:50 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMUNICATION_H
# define COMMUNICATION_H

# include <signal.h>

# define PAUSE_SUCCESS		-1
# define FINAL_MESSAGE_CHAR	'\0'

typedef enum e_signal {
	SIGNAL_SET_BIT_ZERO = SIGUSR1,
	SIGNAL_SET_BIT_ONE = SIGUSR2,
	SIGNAL_ACKNOWLEDGE = SIGUSR2,
}	t_signal;

#endif