/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:53:03 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/01 15:19:50 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h> 
# include <stdlib.h>
# include <unistd.h>

# define HELP_MESSAGE "Usage: ./pipex [FILE]\n"

void	is_valid_args(int argc);

#endif
