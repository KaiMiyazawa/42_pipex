/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:57:12 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/01 15:12:11 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/pipex_bonus.h"

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

void	wait_e(int *exit_status, t_pipex *p)
{
	if (wait(exit_status) == FAILED)
	{
		print_error(strerror(errno), "wait", 1, p);
	}
}

void	wait_all(t_pipex *p)
{
	int	count;

	count = -1;
	while (++count < p->ac - 3)
		wait_e(&p->exit_status, p);
}

void	free_cmd_path(t_pipex *p)
{
	int	count;

	count = -1;
	while (p->cmd_path[++count])
		free(p->cmd_path[count]);
	free(p->cmd_path);
}
