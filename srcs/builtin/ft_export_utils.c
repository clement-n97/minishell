/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:00:00 by clnicola          #+#    #+#             */
/*   Updated: 2026/01/05 11:19:20 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	char_index;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	char_index = 1;
	while (str[char_index])
	{
		if (!ft_isalnum(str[char_index]) && str[char_index] != '_')
			return (0);
		char_index++;
	}
	return (1);
}

int	export_single_var(char *arg, t_env **env)
{
	char	*eq_pos;
	char	*name;

	eq_pos = ft_strchr(arg, '=');
	if (eq_pos && eq_pos != arg)
	{
		name = ft_substr(arg, 0, (size_t)(eq_pos - arg));
		if (!name || !is_valid_identifier(name))
		{
			free(name);
			return (1);
		}
		ft_set_env(name, &eq_pos[1], env);
		free(name);
	}
	else if (!is_valid_identifier(arg))
		return (1);
	return (0);
}
