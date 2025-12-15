/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:49:48 by rlefort           #+#    #+#             */
/*   Updated: 2025/12/15 15:00:14 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// change the current path to the one specified
int	ft_cd(char *path, t_env **env)
{
	int		check;
	char	*cwd;

	if (!path || !path[0])
		return (1);
	check = chdir(path);
	if (check == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	ft_set_env("OLDPWD", ft_get_env_value("PWD", env), env);
	cwd = getcwd(NULL, 0);
	ft_set_env("PWD", cwd, env);
	free(cwd);
	return (0);
}
