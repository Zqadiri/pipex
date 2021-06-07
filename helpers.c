/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:20:34 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/07 19:33:57 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./pipex.h"

// ! check memory LEAKS

char	*get_path(char **envv)
{
    char	**temp;
	char	*path;
	int		i;

	i = 0;
	while (envv[i])
	{
		temp = ft_split(envv[i], '=');
		if (!ft_strncmp("PATH", temp[0], 4))
		{
			path = ft_strdup(temp[1]);
			return (path);
		}
		i++;
	}
	return (NULL);
    // while (envv[i])
    // {
    //     printf("%s\n", envv[i]);
    //     i++;
    // }
}

