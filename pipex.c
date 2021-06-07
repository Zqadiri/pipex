/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:20:17 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/07 18:45:30 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./pipex.h"

void    init_struct(t_index *m)
{
    
}

int error_code(int code)
{
    if (code == 1)
    {
        
    }
    return (1);
}

int parse_args(t_index *m)
{
    
}

int main(int argc, char **argv, char **envv)
{
    t_index *m;

    if (argc == 5)
    {
        m = malloc(sizeof(t_index));
        init_struct(m);
        if (pipe(m->fd) == -1)
            error_code(1);
        parse_args(m);
    }
    else
    {
        ft_putendl_fd("Syntax Error!", 2);
    }
    return (1);
}