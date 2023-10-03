/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 12:08:48 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/06 12:17:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

/*
	Convert a string into a base 10 integer.
	og function from 42: int	ft_atoi_base(const char *str, int base)
	but norm errors so...
*/

char	*check_sign(char *str, int sign)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	return (str);
}

int	ft_atoi_base(char *str, int base)
{
	int	i;
	int	result;
	int	sign;
	int	digit;

	i = 0;
	result = 0;
	sign = 1;
	digit = 0;
	check_sign(str, sign);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digit = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			digit = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			digit = str[i] - 'A' + 10;
		result = result * base + digit;
		i++;
	}
	return (result * sign);
}

// int	main()
// {
// 	printf("%d\n", ft_atoi_base("4f6a", 16));
// }
