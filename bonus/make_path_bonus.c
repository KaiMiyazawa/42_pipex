/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:42:57 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/09/29 13:11:53 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/pipex_bonus.h"

static char	*cmd_join(char *filepath, char *cmd)
{
	size_t	size;
	char	*result;
	size_t	f_size;

	f_size = ft_strlen(filepath);
	size = f_size + ft_strlen(cmd) + 2;
	result = (char *)malloc(size * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, filepath, f_size + 1);
	ft_strlcat(result, "/", f_size + 2);
	ft_strlcat(result, cmd, size);
	return (result);
}

char	*make_path(char **filepath, char *cmd)
{
	int		count;
	char	*path;

	count = 0;
	while (filepath[count])
	{
		path = cmd_join(filepath[count], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		count++;
	}
	return (NULL);
}
