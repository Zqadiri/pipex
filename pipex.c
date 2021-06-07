/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:20:17 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/07 19:33:18 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./pipex.h"

void    init_struct(t_pipex *p)
{
    p->infile = NULL;
    p->infile_fd = 0;
    p->outfile = NULL;
    p->outfile_fd = 0;
}

int error_code(int code)
{
    if (code == 1)
    {
        ft_putendl_fd("Pipe Failed", 2);
        exit (EXIT_FAILURE);
    }
    return (1);
}

// ! ./pipex file1 cmd1 cmd2 file2
// !    0      1    2    3     4

// * ./pipex infile "ls -l" "wc -l" outfile

int parse_args(t_pipex *p, char **argv, char **envv)
{
    t_parse pr;

    p->infile = ft_strdup(argv[1]);
    p->outfile = ft_strdup(argv[4]);
    pr.cmd_1 = ft_split(argv[2], ' ');
    pr.cmd_2 = ft_split(argv[3], ' ');
    p->path = get_path(envv);
    return (1);
}

int main(int argc, char **argv, char **envv)
{
    t_pipex *p;

    if (argc == 5)
    {
        p = malloc(sizeof(t_pipex));
        init_struct(p);
        if (pipe(p->fd) < 0)
            error_code(1);
        parse_args(p, argv, envv);
    }
    else
    {
        ft_putendl_fd("Syntax Error!", 2);
    }
    return (1);
}