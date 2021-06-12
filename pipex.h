/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:20:21 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/12 16:25:45 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "utils/utils.h"

typedef struct s_parse
{
	char	**cmd_1;
	char	**cmd_2;
	int		is_absolute_1;
	int		is_absolute_2;
}	t_parse;

typedef struct s_pipex
{
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	int		fd[2];
	char	**path;
	char	*cmd_1_path;
	char	*cmd_2_path;
	int		pid;
}	t_pipex;

char	*get_path(char **envv);
void	free_struct(t_pipex *p, t_parse *pr);
void	execute_cmd_1(t_pipex *p, t_parse *pr, char **envv);
void	execute_cmd_2(t_pipex *p, t_parse *pr, char **envv);
void	to_the_next_cmd(t_pipex *p, t_parse *pr, char **envv);
int		error_code(int code, t_pipex *p, t_parse *pr);
void	init_struct(t_pipex *p, t_parse *pr);
void	print_args(t_parse *pr, t_pipex *p);
int		print_error(t_pipex *pr);
void	free_d_pointer(char **temp);

#endif
