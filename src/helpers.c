/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 19:20:34 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/18 15:01:10 by zqadiri          ###   ########.fr       */
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
	pr->exit_value = 0;
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
		if (temp[i])
		{
			free(temp[i]);
			temp[i] = NULL;
		}
		i++;
	}
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
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
	printf("abs 1: %d\n", pr->is_absolute_1);
	printf("abs 2: %d\n", pr->is_absolute_2);
}
