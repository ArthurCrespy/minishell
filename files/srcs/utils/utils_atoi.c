/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:06:30 by acrespy           #+#    #+#             */
/*   Updated: 2023/05/26 11:06:30 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
