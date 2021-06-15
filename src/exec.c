/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:07:27 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/15 16:26:18 by zqadiri          ###   ########.fr       */
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
	if (p->cmd_1_path == NULL)
	{
		write (2, "pipex: ", 7);
		write(2, pr->cmd_1[0], ft_strlen(pr->cmd_1[0]));
		ft_putendl_fd(": command not found", 2);
		return ;
	}
	if (p->infile_fd == -1)
		return ;
	close(p->fd[0]);
	dup2(p->infile_fd, 0);
	dup2(p->fd[1], 1);
	if (execve(p->cmd_1_path, pr->cmd_1, envv))
	{
		// perror ("Error");
		free_struct(p, pr);
		exit(pr->exit_value);		
	}	
}

/*
** redirect stdin to read from the pipe
** redirect stdout to outfile_fd 
*/

void	execute_cmd_2(t_pipex *p, t_parse *pr, char **envv)
{
	if (p->cmd_2_path == NULL)
	{
		write (2, "pipex: ", 7);
		write(2, pr->cmd_2[0], ft_strlen(pr->cmd_2[0]));
		ft_putendl_fd(": command not found", 2);
	}
	close(p->fd[1]);
	dup2(p->fd[0], 0);
	dup2(p->outfile_fd, 1);
	if (execve(p->cmd_2_path, pr->cmd_2, envv))
	{
		free_struct(p, pr);
		exit(pr->exit_value);
	}
}

void	wait_child(t_pipex *p)
{
	close(p->fd[0]);
	close(p->fd[1]);
	waitpid(p->pid_1, p->status_1, WCONTINUED);
	waitpid(p->pid_2, p->status_2, WCONTINUED);
}

void	start_exec(t_pipex *p, t_parse *pr, char **envv)
{
	if (pipe(p->fd) < 0)
		error_code(1, p, pr);
	p->pid_1 = fork();
	if (p->pid_1 < 0)
		error_code(4, p, pr);
	else if (p->pid_1 == 0)
		execute_cmd_1(p, pr, envv);
	p->pid_2 = fork();
	if (p->pid_2 < 0)
		error_code(4, p, pr);
	if (p->pid_2 == 0)
		execute_cmd_2(p, pr, envv);
	else if (p->pid_1 > 0 && p->pid_2 > 0)
	{
		wait_child(p);
		if (p->cmd_2_path == NULL)
			pr->exit_value = 127;
		exit (pr->exit_value);
	}
}
