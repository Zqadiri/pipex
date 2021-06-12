/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:07:27 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/12 11:51:34 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	execute_cmd_1(t_pipex *p, t_parse *pr, char **envv)
{
	if (p->infile_fd == -1)
		return ;
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
	if (p->outfile_fd == -1)
		return ;
	dup2(p->fd[0], 0);
	dup2(p->outfile_fd, 1);
	close(p->fd[1]);
	execve(p->cmd_2_path, pr->cmd_2, envv);
	perror("Error");
	exit(1);
}
