/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:15:58 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 09:20:08 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	int			fd;
	const char	*nonexit = "nonexit.txt";

	fd = open(nonexit, O_RDONLY);
	if (fd < 0)
	{
		perror(nonexit);
		exit(EXIT_FAILURE);
	}
	return (0);
}
