/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinet <abinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:06:30 by acrespy           #+#    #+#             */
/*   Updated: 2023/09/20 19:41:07 by abinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_whitespace(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static void	skip_whitespaces(const char **str)
{
	while (is_whitespace(**str))
		(*str)++;
}

int	ft_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	ft_atoi(const char *str)
{
	long int	res;
	int			i;

	res = 0;
	i = 1;
	skip_whitespaces(&str);
	if (*str == '-')
		i = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if ((res > (INT_MAX - *str + '0') / 10))
			return (0);
		res = (res * 10) + *str - '0';
		str++;
	}
	return (res * i);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*dest;
	long long		nb;

	nb = n;
	len = ft_len(n);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	if (nb < 0)
	{
		dest[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		dest[0] = '0';
	dest[len--] = '\0';
	while (nb)
	{
		dest[len] = nb % 10 + 48;
		nb /= 10;
		len--;
	}
	return (dest);
}
