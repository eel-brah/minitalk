/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:39:41 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/30 19:51:19 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*char_to_bits(char c)
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

void	*str_realloc(char *ptr, size_t newSize)
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

void	*free_them(char *p1, char *p2)
{
	free(p1);
	free(p2);
	return (NULL);
}

char	*str_to_bits(char *str)
{
	char	*c;
	char	*bits;
	char	*tmp;
	size_t	size;

	bits = NULL;
	size = 1;
	while (str && *str)
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
	return (bits);
}

char	*bits_to_str(char *bits)
{
	char	*str;
	size_t	size;
	int		i;
	int		j;

	size = ft_strlen(bits);
	size /= 8;
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 1;
	while (*bits)
	{
		if (*bits == '1')
			str[i] = str[i] | (128 / j);
		j *= 2;
		bits++;
		if (j > 128)
		{
			j = 1;
			i++;
		}
	}
	str[i] = 0;
	return (str);
}

int main()
{
	char c;
	char *p = "ￚ ▀ ￮ hi 🧑";
	char *p2;

	p = str_to_bits(p);
	printf("%s\n", p);
	p2 = bits_to_str(p);
	printf("%s\n", p2);
	free(p);
	free(p2);
}