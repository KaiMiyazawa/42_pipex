/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 01:39:38 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/01 15:31:42 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<fcntl.h>
# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include<sys/wait.h>
# include<errno.h>
# include<stdbool.h>

# define FAILED -1

typedef struct s_pipex
{
	char	**cmd_path;

	int		fd_infile;
	int		fd_outfile;

	char	*infile;
	char	*outfile;

	int		ac;
	char	**envp;
	char	**av;

	int		exit_status;
}				t_pipex;

//main
void	print_error(char *error_msg, char *addition, bool exit, t_pipex *p);

//ft_split
char	**ft_split(char const *s, char c);

//make_path
char	*make_path(char **filepath, char *cmd);

//pipex
void	pipex(t_pipex *p);

//utils
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t n, size_t size);

//utils2
void	close_e(int fd, t_pipex *pfd);
void	dup2_e(int fd1, int fd2, t_pipex *p);
void	wait_e(int *exit_status, t_pipex *p, int pid);
void	wait_all(t_pipex *p, int pid1, int pid2);
void	free_cmd_path(t_pipex *p);

#endif