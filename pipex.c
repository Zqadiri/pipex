/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:20:17 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/09 19:51:30 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_path(t_pipex *p, char	*cmd, char **final_path)
{
	char	*temp;
	char	*possible_path;
	char	*pfree;
	int		i;
	int		fd;

	i = -1;
	while (p->path[++i])
	{
		temp = ft_strjoin(p->path[i], "/");
		pfree = temp;
		possible_path = ft_strjoin(temp, cmd);
		free(temp);
		fd = open(possible_path, O_RDONLY);
		if (fd > 0)
		{
			*final_path = ft_strdup(possible_path);
			free(possible_path);
			possible_path = NULL;
			return (1);
		}
		free(possible_path);
		possible_path = NULL;
	}
	return (0);
}

int	check_cmd_path(t_pipex *p, t_parse *pr)
{
	int	ret;

	ret = -1;
	if (*pr->cmd_1 == NULL || *pr->cmd_2 == NULL)
		error_code(2, p, pr);
	if (!ft_strncmp(pr->cmd_1[0], "/", 1))
		pr->is_absolute_1 = 1;
	if (!ft_strncmp(pr->cmd_2[0], "/", 1))
		pr->is_absolute_2 = 1;
	if (!pr->is_absolute_1)
		find_path(p, pr->cmd_1[0], &p->cmd_1_path);
	if (p->cmd_1_path == NULL)
		p->cmd_1_path = ft_strdup(pr->cmd_1[0]);
	if (!pr->is_absolute_2)
		find_path(p, pr->cmd_2[0], &p->cmd_2_path);
	if (p->cmd_2_path == NULL)
		p->cmd_2_path = ft_strdup(pr->cmd_2[0]);
	return (1);
}

int	parse_args(t_pipex *p, char **argv, char **envv, t_parse *pr)
{
	char	*pth;

	pth = get_path(envv);
	p->infile = ft_strdup(argv[1]);
	p->outfile = ft_strdup(argv[4]);
	p->infile_fd = open(p->infile, O_RDWR);
	if (p->infile_fd < 0)
		error_code(3, p, pr);
	p->outfile_fd = open(p->outfile, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (p->outfile_fd < 0)
		error_code(3, p, pr);
	// print_args(pr, p);
	pr->cmd_1 = ft_split(argv[2], 32);
	pr->cmd_2 = ft_split(argv[3], 32);
	p->path = ft_split(pth, ':');
	if (p->path == NULL)
		error_code (2, p, pr);
	free(pth);
	//if (!pr->cmd_1)
		//printf("heelo");
	check_cmd_path(p, pr);
	return (1);
}

int	main(int argc ,char **argv, char **envv)
{
	(void)envv;
	(void)argv;
	
	t_pipex	*p;
	t_parse	*pr;
	// write(1, &argc, 1);
	// write(1, "\n", 1);
	// printf("%d\n", argc);
	if (argc == 5)
	{
		p = malloc(sizeof(t_pipex));
		pr = malloc(sizeof(t_parse));
		init_struct(p, pr);
		parse_args(p, argv, envv, pr);
		if (pipe(p->fd) < 0)
			error_code(1, p, pr);
		p->pid = fork();
		if (p->pid < 0)
			error_code(4, p, pr);
		else if (p->pid == 0)
			execute_cmd_1(p, pr, envv);
		to_the_next_cmd(p, pr, envv);
		free_struct(p, pr);
	}
	else
	 	ft_putendl_fd("Syntax Error!", 2);
	return (1);
}
