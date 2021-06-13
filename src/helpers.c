/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:20:34 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/13 16:55:04 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_struct(t_pipex *p, t_parse *pr)
{
	p->infile = NULL;
	p->infile_fd = 0;
	p->outfile = NULL;
	p->outfile_fd = 0;
	pr->is_absolute_1 = 0;
	pr->is_absolute_2 = 0;
	p->pid_1 = 0;
	p->pid_2 = 0;
}

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
			free_d_pointer(temp);
			return (path);
		}
		free_d_pointer(temp);
		free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

void	free_d_pointer(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	free(temp);
	temp = NULL;
}
