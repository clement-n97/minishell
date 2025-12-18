/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:59:54 by rlefort           #+#    #+#             */
/*   Updated: 2025/12/18 13:01:08 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_var_line(t_env *var)
{
	char	*var_line;
	size_t	size;

	size = 11 + ft_strlen(var->name) + 1 + ft_strlen(var->value) + 2;
	var_line = calloc(sizeof(char), size);
	ft_strlcat(var_line, "declare -x ", size);
	ft_strlcat(var_line, var->name, size);
	ft_strlcat(var_line, "=", size);
	ft_strlcat(var_line, var->value, size);
	ft_strlcat(var_line, "\n", size);
	return (var_line);
}

static char	*ft_export_output(t_env **env)
{
	char	*env_vars;
	char	*var_line;
	char	*tmp;
	t_env	*curr;

	if (!env)
		return (NULL);
	curr = *env;
	env_vars = calloc(1, 1);
	while (curr)
	{
		if (curr->name && curr->name[0])
		{
			var_line = build_var_line(curr);
			tmp = ft_strjoin(env_vars, var_line);
			free(env_vars);
			free(var_line);
			if (!tmp)
				return (NULL);
			env_vars = tmp;
		}
		curr = curr->next;
	}
	return (env_vars);
}

char	*ft_export_noargs(t_env **env)
{
	t_env	**sorted_env;
	int		is_sorted;
	char	*output;
	t_env	*curr;

	sorted_env = ft_copy_env(env);
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		curr = *sorted_env;
		while (curr && curr->next)
		{
			if (ft_strcmp(curr->name, curr->next->name) > 0)
			{
				is_sorted = 0;
				ft_swap_env(sorted_env, curr);
			}
			curr = curr->next;
		}
	}
	output = ft_export_output(sorted_env);
	ft_free_env(sorted_env);
	return (output);
}

static int	export_single_var(char *arg, t_env **env)
{
	char	*eq_pos;
	char	*name;
	int		ret;

	ret = 0;
	eq_pos = ft_strchr(arg, '=');
	if (eq_pos && eq_pos != arg)
	{
		name = ft_substr(arg, 0, (size_t)(eq_pos - arg));
		if (name)
		{
			if (ft_set_env(name, &eq_pos[1], env))
				ret = 1;
			free(name);
		}
	}
	return (ret);
}

int	ft_export(char **args, t_env **env)
{
	int	index;
	int	ret;

	if (!env || !args || !args[0])
		return ;
	index = 0;
	while (args[index])
	{
		if (args[index] && args[index][0])
			export_single_var(args[index], env);
		index++;
	}
}
