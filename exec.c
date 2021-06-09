/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:07:27 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/09 18:45:31 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** dup2 takes an old file descriptor to be cloned as the first parameter 
** and the second parameter is the integer for a new file descriptor
*/

/*
** filedes[0] is used for reading from the pipe, 
** and filedes[1] is used for writing to the pipe
** redirect stdin to infile_fd 
** redirect stdout to write to the pipe 
*/

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

void	execute_cmd_1(t_pipex *p, t_parse *pr, char **envv)
{
	print_args(pr, p);
	dup2(p->infile_fd, 0);
	dup2(p->fd[1], 1);
	close(p->fd[0]);
	execve(p->cmd_1_path, pr->cmd_1, envv);
	perror ("Error");
	exit(1);
}

/*
** redirect stdin to read from the pipe
** redirect stdout to outfile_fd 
*/

void	execute_cmd_2(t_pipex *p, t_parse *pr, char **envv)
{
	dup2(p->fd[0], 0);
	dup2(p->outfile_fd, 1);
	close(p->fd[1]);
	execve(p->cmd_2_path, pr->cmd_2, envv);
	perror("Error");
	exit(1);
}

void	to_the_next_cmd(t_pipex *p, t_parse *pr, char **envv)
{
	p->pid = fork();
	if (p->pid < 0)
		error_code(4, p, pr);
	else if (p->pid == 0)
		execute_cmd_2(p, pr, envv);
}
