/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:20:34 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/09 19:52:13 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *p, t_parse *pr)
{
	p->infile = NULL;
	p->infile_fd = 0;
	p->outfile = NULL;
	p->outfile_fd = 0;
	pr->is_absolute_1 = 0;
	pr->is_absolute_2 = 0;
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

void	free_struct(t_pipex *p, t_parse *pr)
{
	if (pr->cmd_1)
		free_d_pointer(pr->cmd_1);
	if (pr->cmd_2)
		free_d_pointer(pr->cmd_2);
	if (p->infile)
	{
		free(p->infile);
		p->infile = NULL;
	}
	if (p->outfile)
	{
		free(p->outfile);
		p->outfile = NULL;
	}
	if (p->path)
		free_d_pointer(p->path);
	close(p->infile_fd);
	close(p->outfile_fd);
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

int	error_code(int code, t_pipex *p, t_parse *pr)
{
	if (code == 1)
	{
		ft_putendl_fd("Pipe Failed!", 2);
		free_struct(p, pr);
		exit (EXIT_FAILURE);
	}
	if (code == 2)
	{
		ft_putendl_fd("PATH variable is missing!", 2);
		free_struct(p, pr);
		exit (EXIT_FAILURE);
	}
	if (code == 3)
	{
		perror ("Error:");
		// free_struct(p, pr);
		// exit (EXIT_FAILURE);
	}
	if (code == 4)
	{
		ft_putendl_fd("Fork Failed!", 2);
		// free_struct(p, pr);
		exit (EXIT_FAILURE);
	}
	return (1);
}
