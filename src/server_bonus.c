/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:33:06 by manu              #+#    #+#             */
/*   Updated: 2022/06/04 18:57:34 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "error.h"
#include "process.h"
#include "signals.h"

void	handle_signals(void)
{
	while (pause() == PAUSE_SUCCESS)
		;
}

int	main(void)
{
	show_process_pid();
	setup_user_signal_handler();
	setup_cleanup_signal_handler();
	handle_signals();
	return (0);
}
