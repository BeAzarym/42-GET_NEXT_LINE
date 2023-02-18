/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:59:18 by cchabeau          #+#    #+#             */
/*   Updated: 2023/02/18 12:58:04 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	if (!s)
		return ;
	while (n--)
		*(char*)s++ = 0;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	len_str;
	char *str;
	int	len_s1;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_str = len_s1 + ft_strlen(s2);
	str = malloc(sizeof(char) * (len_str + 1));
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	free (s1 - len_s1);
	return (str - len_str);	
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = -1;
	while (src[++i] != '\0' && dstsize > 1)
	{
		dst[i] = src[i];
		dstsize--;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (len);
}