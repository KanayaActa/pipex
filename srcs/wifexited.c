/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wifexited.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:51:30 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 13:53:03 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	wifexited(int status)
{
	return ((status & 0x7F) == 0);
}