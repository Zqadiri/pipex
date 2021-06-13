/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:07:27 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/13 16:53:03 by zqadiri          ###   ########.fr       */
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
	(void)p;
	(void)pr;
	if (check_cmd_path(p->cmd_1_path) < 0)
		return ;
	if (p->infile_fd == -1)
		return ;
	dup2(p->infile_fd, 0);
	dup2(p->fd[1], 1);
	close(p->fd[0]);
	execve(p->cmd_1_path, pr->cmd_1, envv);
	perror ("Error");
	free_struct(p, pr);
	exit(1);
}

/*
** redirect stdin to read from the pipe
** redirect stdout to outfile_fd 
*/

void	execute_cmd_2(t_pipex *p, t_parse *pr, char **envv)
{
	(void)p;
	(void)pr;
	if (check_cmd_path(p->cmd_2_path) < 0)
		return ;
	if (p->outfile_fd == -1)
		return ;
	dup2(p->fd[0], 0);
	dup2(p->outfile_fd, 1);
	close(p->fd[1]);
	execve(p->cmd_2_path, pr->cmd_2, envv);
	perror("Error");
	free_struct(p, pr);
	exit(1);
}

void	fork_child(t_pipex *p, t_parse *pr)
{
	p->pid_2 = fork();
	if (p->pid_2 < 0)
		error_code(4, p, pr);
}

void	wait_child(t_pipex *p)
{
	waitpid(p->pid_1, p->status_1, WCONTINUED);
	waitpid(p->pid_2, p->status_2, WCONTINUED);
}

void	start_exec(t_pipex *p, t_parse *pr, char **envv)
{
	if (pipe(p->fd) < 0)
		error_code(1, p, pr);
	p->pid_1 = fork();
	if (p->pid_1 < 0 || p->pid_2 < 0)
		error_code(4, p, pr);
	else if (p->pid_1 == 0)
		execute_cmd_1(p, pr, envv);
	fork_child(p, pr);
	if (p->pid_2 == 0)
		execute_cmd_2(p, pr, envv);
	else if (p->pid_1 > 0 && p->pid_2 > 0)
		wait_child(p);
}
