/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:00:45 by rlefort           #+#    #+#             */
/*   Updated: 2025/12/18 13:31:15 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_env **env)
{
	char	*name;
	int		i;
	int		j;
	int		ret;

	ret = 0;
	if (!env || !args || !args[0])
		return (1);
	i = 0;
	while (args[i])
	{
		if (!args[i][0] || (!ft_isalpha(args[i][0]) && args[i][0] != '_'))
			ret = 1;
		else
		{
			j = 0;
			while (args[i][j])
				if (!isalphanum(args[i][j]) && args[i][j++] != '_')
					ret = 1 ;
			if (!args[i][j])
				ft_rm_env(args[i], env);
		}
		i++;
	}
	return (ret);
}
