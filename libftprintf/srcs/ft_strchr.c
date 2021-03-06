/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:31:16 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/06 17:31:17 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (1)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
}
