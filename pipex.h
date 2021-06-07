/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:20:21 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/07 20:53:13 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_parse
{
	char	**cmd_1;
	char	**cmd_2;
}	t_parse;

typedef struct s_pipex
{
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	int		fd[2];
	char	**path;
}	t_pipex;

char	*get_path(char **envv);
void	print_args(t_parse *pr, t_pipex *p);
void	free_struct(t_pipex *p, t_parse *pr);

#endif
