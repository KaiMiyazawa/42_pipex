/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:33:00 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/01 14:35:37 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/pipex.h"

static void	do_excute(char *pre_cmd, char *envp[], char **filepath, t_pipex *p)
{
	char	*path;
	char	**cmd;
	int		count;

	cmd = ft_split(pre_cmd, ' ');
	if (!cmd)
		print_error(strerror(errno), NULL, 1, p);
	if (execve(pre_cmd, cmd, envp) != FAILED)
		exit(EXIT_FAILURE);
	path = make_path(filepath, cmd[0]);
	if (execve(path, cmd, envp) == FAILED)
	{
		print_error("command not found", cmd[0], 0, p);
		count = 0;
		while (cmd[count])
		{
			free(cmd[count]);
			count++;
		}
		free(cmd);
		free(path);
		exit(1);
	}
}

static void	child1(t_pipex *p, int *fd_pipe)
{
	p->fd_infile = open(p->infile, O_RDONLY);
	if (p->fd_infile < 0)
		print_error(strerror(errno), p->infile, 1, p);
	close_e(STDIN_FILENO, p);
	dup2_e(p->fd_infile, STDIN_FILENO, p);
	close_e(p->fd_infile, p);
	close_e(STDOUT_FILENO, p);
	dup2_e(fd_pipe[1], STDOUT_FILENO, p);
	close_e(fd_pipe[1], p);
	do_excute(p->av[2], p->envp, p->cmd_path, p);
}

static void	child2(t_pipex *p)
{
	p->fd_outfile = open(p->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (p->fd_outfile < 0)
		print_error(strerror(errno), p->outfile, 1, p);
	dup2_e(p->fd_outfile, STDOUT_FILENO, p);
	close_e(p->fd_outfile, p);
	do_excute(p->av[3], p->envp, p->cmd_path, p);
}

static void	close_pipe(int *fd_pipe, t_pipex *p)
{
	dup2_e(fd_pipe[0], STDIN_FILENO, p);
	close_e(fd_pipe[0], p);
	close_e(fd_pipe[1], p);
}

void	pipex(t_pipex *p)
{
	int		pid1;
	int		pid2;
	int		fd_pipe[2];

	if (pipe(fd_pipe))
		print_error(strerror(errno), "pipe", 1, p);
	pid1 = fork();
	if (pid1 < 0)
		print_error(strerror(errno), "fork", 1, p);
	if (pid1 == 0)
		child1(p, fd_pipe);
	else
		close_pipe(fd_pipe, p);
	pid2 = fork();
	if (pid2 < 0)
		print_error(strerror(errno), "fork", 1, p);
	if (pid2 == 0)
		child2(p);
	wait_all(p, pid1, pid2);
}
