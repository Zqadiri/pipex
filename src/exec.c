/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:07:27 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/20 14:02:33 by zqadiri          ###   ########.fr       */
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
	int	fd;

	fd = open(p->cmd_1_path, O_RDONLY);
	if (p->cmd_1_path == NULL || fd < 0)
	{
		write (2, "pipex: ", 7);
		write(2, pr->cmd_1[0], ft_strlen(pr->cmd_1[0]));
		ft_putendl_fd(": command not found", 2);
		exit (0);
	}
	p->infile_fd = open(p->infile, O_RDWR);
	if (p->infile_fd < 0)
	{
		print_error(p->infile);
		exit (0);
	}
	close(p->fd[0]);
	dup2(p->infile_fd, 0);
	dup2(p->fd[1], 1);
	close(p->fd[1]);
	if (execve(p->cmd_1_path, pr->cmd_1, envv))
		free_struct(p, pr);
}

/*
** redirect stdin to read from the pipe
** redirect stdout to outfile_fd 
*/

void	execute_cmd_2(t_pipex *p, t_parse *pr, char **envv)
{
	int	fd;

	p->outfile_fd = open(p->outfile, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (p->outfile_fd < 0)
	{
		print_error(p->outfile);
		exit (1);
	}
	fd = open(p->cmd_2_path, O_RDONLY);
	if (p->cmd_2_path == NULL || fd < 0)
	{
		write (2, "pipex: ", 7);
		write(2, pr->cmd_2[0], ft_strlen(pr->cmd_2[0]));
		ft_putendl_fd(": command not found", 2);
		exit (127);
	}
	close(p->fd[1]);
	dup2(p->outfile_fd, 1);
	dup2(p->fd[0], 0);
	close(p->fd[0]);
	if (execve(p->cmd_2_path, pr->cmd_2, envv))
		free_struct(p, pr);
}

void	start_exec(t_pipex *p, t_parse *pr, char **envv)
{
	int	status;

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
	close(p->fd[1]);
	close(p->fd[0]);
	waitpid(p->pid_1, &status, WCONTINUED);
	waitpid(p->pid_2, &status, WCONTINUED);
	pr->exit_value = WEXITSTATUS(status);
	exit (pr->exit_value);
}
