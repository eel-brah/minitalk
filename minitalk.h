/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:48:01 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/30 21:59:44 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include "libft/libft.h"
#include <signal.h>

typedef struct s_bit
{
	int	byte;
	int		size;
}	t_byte;