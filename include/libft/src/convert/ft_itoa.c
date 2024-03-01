/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 16:28:48 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/01 19:26:56 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_count(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_fill(char *str, int len, long n)
{
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
}

static void	*mini_malloc(int size)
{
	void	*data;

	data = malloc(size);
	if (!data)
		exit(EXIT_FAILURE);
	return (data);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_count(n);
	str = (char *)mini_malloc(len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	ft_fill(str, len, n);
	return (str);
}
