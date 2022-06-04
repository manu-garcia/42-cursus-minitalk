/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:15:56 by manugarc          #+#    #+#             */
/*   Updated: 2022/06/04 17:35:52 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	set_bit(char value, int bit_position)
{
	return (value | (0x01 << bit_position));
}

int	is_bit_set(char value, int bit_position)
{
	return ((value) & (1 << bit_position));
}
