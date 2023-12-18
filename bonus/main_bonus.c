/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 01:08:03 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/01 15:27:04 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/pipex_bonus.h"

void	add_str(char *s1, char *s2)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (s1[count] != '\0')
		count++;
	while (s2[count2] != '\0')
		s1[count++] = s2[count2++];
	s1[count] = '\0';
}

void	print_error(char *error_msg, char *addition, bool exit_flag, t_pipex *p)
{
	char	*error;
	int		size;

	size = 7 + ft_strlen(error_msg) + 1 + 1;
	if (addition != NULL)
		size += 2 + ft_strlen(addition);
	error = (char *)ft_calloc(sizeof(char), size);
	if (!error)
		perror(strerror(errno));
	ft_strlcpy(error, "pipex: ", 8);
	add_str(error, error_msg);
	if (addition != NULL)
	{
		add_str(error, ": ");
		add_str(error, addition);
	}
	add_str(error, "\n");
	if (write(2, error, size) == FAILED)
		perror(strerror(errno));
	free(error);
	if (exit_flag == 1)
	{
		free_cmd_path(p);
		exit(1);
	}
}

static void	check_arg_p_init(int argc, char *argv[], char **envp, t_pipex *p)
{
	if (argc < 5)
		print_error("Invalid argments.\npass 4 argments tp program.",
			NULL, 1, p);
	p->ac = argc;
	p->infile = argv[1];
	p->outfile = argv[argc - 1];
	p->envp = envp;
	p->av = argv;
	p->exit_status = 0;
}

static void	no_path_case(t_pipex *p)
{
	p->cmd_path = (char **)malloc(sizeof(char *) * 2);
	if (!(p->cmd_path))
		print_error(strerror(errno), "malloc", 1, p);
	p->cmd_path[0] = (char *)malloc(sizeof(char) * 2);
	if (!(p->cmd_path[0]))
	{
		free(p->cmd_path);
		print_error(strerror(errno), "malloc", 1, p);
	}
	p->cmd_path[0][0] = '.';
	p->cmd_path[0][1] = '\0';
	p->cmd_path[1] = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		count;
	t_pipex	p;

	check_arg_p_init(argc, argv, envp, &p);
	count = 0;
	while (ft_strncmp(p.envp[count], "PATH=", 5) != 0)
		count++;
	if (p.envp[count] == NULL)
		no_path_case(&p);
	else
		p.cmd_path = ft_split(p.envp[count] + 5, ':');
	pipex(&p);
	free_cmd_path(&p);
	if (p.exit_status != 0)
		exit(EXIT_FAILURE);
	return (0);
}
