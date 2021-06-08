/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:20:34 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/08 21:44:46 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
}

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

void	print_args(t_parse *pr, t_pipex *p)
{
	int	i;

	i = 0;
	printf("infile : %s\n", p->infile);
	printf("outfile : %s\n", p->outfile);
	while (pr->cmd_1[i])
	{
		printf("cmd_1 : %s\n", pr->cmd_1[i]);
		i++;
	}
	i = 0;
	while (pr->cmd_2[i])
	{
		printf("cmd_2 : %s\n", pr->cmd_2[i]);
		i++;
	}
	i = 0;
	while (p->path[i])
	{
		printf("path : %s\n", p->path[i]);
		i++;
	}
	printf("cmd_1_path : %s\n", p->cmd_1_path);
	printf("cmd_2_path : %s\n", p->cmd_2_path);
	
}
