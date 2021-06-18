/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:53:34 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/18 15:33:30 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	print_error(char *file_error)
{
	write (2, "pipex: ", 7);
	write(2, file_error, ft_strlen(file_error));
	perror(" ");
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
		exit (EXIT_FAILURE);
	}
	if (code == 4)
	{
		ft_putendl_fd("Fork Failed!", 2);
		exit (1);
	}
	if (code == 5)
	{
		ft_putendl_fd("Syntax Error!", 2);
		exit (EXIT_FAILURE);
	}
	return (1);
}
