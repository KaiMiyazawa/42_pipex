/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:37:41 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/09/29 14:36:29 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/pipex_bonus.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dest && !size)
		return (src_len);
	dest_len = ft_strlen(dest);
	i = 0;
	if (dest_len < size -1 && size > 0)
	{
		while (i < size - dest_len - 1 && src[i])
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		dest[i + dest_len] = '\0';
	}
	if (size <= dest_len)
		return (size + src_len);
	return (src_len + dest_len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size > 0)
	{
		while (count < size - 1 && src[count])
		{
			dest[count] = src[count];
			count++;
		}
		dest[count] = '\0';
	}
	while (src[count])
		count++;
	return (count);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	count;

	count = 0;
	if (s1 == NULL)
		return (0);
	while (count < n && (s1[count] != '\0' || s2[count] != '\0'))
	{
		if (s1[count] != s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return (0);
}

void	*ft_calloc(size_t n, size_t size)
{
	size_t	count;
	void	*result;

	count = 0;
	if (size != 0 && n > SIZE_MAX / size)
		return (NULL);
	result = (void *)malloc(n * size);
	if (!result)
		return (NULL);
	while (count < n * size)
	{
		*(char *)(result + count) = 0;
		count++;
	}
	return (result);
}
