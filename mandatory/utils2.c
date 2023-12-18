/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:57:12 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/01 14:43:46 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/pipex.h"

void	close_e(int fd, t_pipex *p)
{
	if (close(fd) == FAILED)
	{
		print_error(strerror(errno), "close", 1, p);
	}
}

void	dup2_e(int fd1, int fd2, t_pipex *p)
{
	if (dup2(fd1, fd2) == FAILED)
	{
		print_error(strerror(errno), "dup2", 1, p);
	}
}

void	wait_e(int *exit_status, t_pipex *p, int pid)
{
	if (waitpid(pid, exit_status, 0) == FAILED)
	{
		print_error(strerror(errno), "wait", 1, p);
	}
}

void	wait_all(t_pipex *p, int pid1, int pid2)
{
	wait_e(NULL, p, pid1);
	wait_e(&p->exit_status, p, pid2);
}

void	free_cmd_path(t_pipex *p)
{
	int	count;

	count = -1;
	while (p->cmd_path[++count])
		free(p->cmd_path[count]);
	free(p->cmd_path);
}
