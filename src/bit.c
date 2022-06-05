/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:15:56 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/05 22:27:48 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	set_bit(char value, int bit_position)
{
	return (value | (1 << bit_position));
}

int	is_bit_set(char value, int bit_position)
{
	return ((value) & (1 << bit_position));
}
