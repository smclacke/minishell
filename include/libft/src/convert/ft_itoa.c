/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 16:28:48 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/13 20:06:43 by smclacke      ########   odam.nl         */
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

char	*ft_itoa(int n)
{
	char		*str;
	int			len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_count(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	ft_fill(str, len, n);
	return (str);
}
