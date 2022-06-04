/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:08:01 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/04 18:41:02 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// printf
#include <unistd.h>	// pause usleep getpid

void	show_process_pid(void)
{
	printf("\nProcess PID: %d\n", getpid());
}
