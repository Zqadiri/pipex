/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 00:38:49 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/12 11:43:46 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *src)
{
	int		size;
	char	*p;
	int		i;

	i = 0;
	size = 0;
	while (src[i] != '\0')
	{
		i++;
		size++;
	}
	size++;
	p = (char *)malloc(size * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		*(p + i) = src[i];
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
