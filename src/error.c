/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:36:48 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/04 18:57:05 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>	// malloc
#include <stdio.h>
#include "error.h"

void	exit_with_error_message(char *error_message, int exit_code)
{
	printf("\n%s\n", error_message);
	exit(exit_code);
}

void	exit_with_internal_error(void)
{
	exit_with_error_message(
		"Internal error getting comunication state",
		ERROR_INTERNAL);
}

void	exit_with_memory_error(void)
{
	exit_with_error_message(
		"Error not enough memory",
		ERROR_MEMORY);
}
