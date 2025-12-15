/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:07:44 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 13:07:45 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_path(char *cmd)
{
	if (cmd[0] == '/' || ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static char	*search_in_path(char **path, char *cmd)
{
	char	*temp;
	char	*full_path;
	int		i;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*ft_get_cmd(char **env, char *cmd)
{
	char	**path;
	char	*result;

	if (!cmd || !*cmd)
		exit(1);
	result = check_path(cmd);
	if (result)
		return (result);
	path = ft_split(ft_get_path(env), ':');
	if (!path)
		return (NULL);
	result = search_in_path(path, cmd);
	ft_free_tabs(path);
	return (result);
}
