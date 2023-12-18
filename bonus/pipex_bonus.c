/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:33:00 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/01 15:12:20 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/pipex_bonus.h"

static void	close_pipe(t_pipex *p, int count, int *fd_pipe)
{
	if (count != p->ac - 2)
	{
		dup2_e(fd_pipe[0], STDIN_FILENO, p);
		close_e(fd_pipe[0], p);
		close_e(fd_pipe[1], p);
	}
}

static void	do_excute(char *pre_cmd, char *envp[], char **filepath, t_pipex *p)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(pre_cmd, ' ');
	if (!cmd)
		print_error(strerror(errno), NULL, 1, p);
	if (execve(pre_cmd, cmd, envp) != FAILED)
		exit(EXIT_FAILURE);
	path = make_path(filepath, cmd[0]);
	if (execve(path, cmd, envp) == FAILED)
	{
		print_error("command not found", cmd[0], 0, p);
		exit(1);
	}
}

static void	set_stdin_fd(int count, t_pipex *p)
{
	if (count == 0)
	{
		p->fd_infile = open(p->infile, O_RDONLY);
		if (p->fd_infile < 0)
			print_error(strerror(errno), p->infile, 1, p);
		close_e(STDIN_FILENO, p);
		dup2_e(p->fd_infile, STDIN_FILENO, p);
		close_e(p->fd_infile, p);
	}
}

static void	set_stdout_fd(t_pipex *p, int count, int *fd_pipe)
{
	if (count == p->ac - 4)
	{
		p->fd_outfile = open(p->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (p->fd_outfile < 0)
			print_error(strerror(errno), p->outfile, 1, p);
		dup2_e(p->fd_outfile, STDOUT_FILENO, p);
		close_e(p->fd_outfile, p);
	}
	else
	{
		close_e(STDOUT_FILENO, p);
		dup2_e(fd_pipe[1], STDOUT_FILENO, p);
		close_e(fd_pipe[1], p);
	}
}

void	pipex(t_pipex *p)
{
	int		count;
	int		pid;
	int		fd_pipe[2];

	count = -1;
	while (++count < p->ac - 3)
	{
		if (pipe(fd_pipe))
			print_error(strerror(errno), "pipe", 1, p);
		pid = fork();
		if (pid < 0)
			print_error(strerror(errno), "fork", 1, p);
		if (pid == 0)
		{
			set_stdin_fd(count, p);
			set_stdout_fd(p, count, fd_pipe);
			do_excute(p->av[count + 2], p->envp, p->cmd_path, p);
		}
		else
			close_pipe(p, count, fd_pipe);
	}
	wait_all(p);
}
