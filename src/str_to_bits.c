/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:19:14 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/01 16:06:11 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static char	*char_to_bits(char c)
{
	char	*p;
	int		i;

	p = malloc(9 * sizeof(char));
	if (!p)
		return (NULL);
	p[8] = 0;
	i = 0;
	while (i < 8)
	{
		if (c & 0b10000000)
			p[i] = '1';
		else
			p[i] = '0';
		c <<= 1;
		i++;
	}
	return (p);
}

static void	*str_realloc(char *ptr, size_t newSize)
{
	char	*new;

	new = ft_calloc(newSize, sizeof(char));
	if (!new)
		return (NULL);
	if (ptr)
		ft_strlcpy(new, ptr, newSize);
	free(ptr);
	return (new);
}

static void	*free_them(char *p1, char *p2)
{
	free(p1);
	free(p2);
	return (NULL);
}

static char	*last_bit(char *bits, size_t size)
{
	char	*c;
	char	*tmp;

	c = char_to_bits(0);
	if (!c)
		return (free_them(c, bits));
	size += 8;
	tmp = str_realloc(bits, size);
	if (!tmp)
		return (free_them(c, bits));
	bits = tmp;
	ft_strlcat(bits, c, size);
	free(c);
	return (bits);
}

char	*str_to_bits(char *str)
{
	char	*c;
	char	*bits;
	char	*tmp;
	size_t	size;

	if (!str)
		return (NULL);
	bits = NULL;
	size = 1;
	while (*str)
	{
		c = char_to_bits(*str);
		if (!c)
			return (free_them(c, NULL));
		size += 8;
		tmp = str_realloc(bits, size);
		if (!tmp)
			return (free_them(c, bits));
		bits = tmp;
		ft_strlcat(bits, c, size);
		free(c);
		str++;
	}
	return (last_bit(bits, size));
}
