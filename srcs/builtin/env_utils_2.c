/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:03:37 by rlefort           #+#    #+#             */
/*   Updated: 2025/12/18 15:28:13 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env_var(char *name, char *value, t_env *next)
{
	t_env	*curr;

	curr = malloc(sizeof(t_env));
	if (!curr)
		return (NULL);
	curr->name = ft_strdup(name);
	if (value)
		curr->value = ft_strdup(value);
	if (!curr->name || !curr->value)
	{
		if (curr->name)
			free(curr->name);
		if (curr->value)
			free(curr->value);
		free(curr);
		return (NULL);
	}
	curr->next = next;
	return (curr);
}

void	ft_free_env(t_env **env)
{
	t_env	*prev;
	t_env	*curr;

	if (*env)
	{
		curr = *env;
		while (curr)
		{
			prev = curr;
			curr = curr->next;
			if (prev->name)
				free(prev->name);
			if (prev->value)
				free(prev->value);
			free(prev);
		}
	}
	free(env);
}

static int	ft_copy_env_tail(t_env **new, t_env **old)
{
	t_env	*curr_n;
	t_env	*curr_o;

	curr_n = *new;
	curr_o = *old;
	while (curr_o->next)
	{
		curr_o = curr_o->next;
		curr_n->next = ft_new_env_var(curr_o->name, curr_o->value, NULL);
		if (!curr_n->next)
			return (-1);
		curr_n = curr_n->next;
	}
	return (0);
}

t_env	**ft_copy_env(t_env **env)
{
	t_env	**new;
	t_env	*browser;

	new = malloc(sizeof(t_env *));
	if (!env || !new)
		return (NULL);
	browser = *env;
	if (!browser)
	{
		*new = NULL;
		return (new);
	}
	*new = ft_new_env_var(browser->name, browser->value, NULL);
	if (!*new)
	{
		ft_free_env(new);
		return (NULL);
	}
	if (ft_copy_env_tail(new, env))
	{
		ft_free_env(new);
		return (NULL);
	}
	return (new);
}

char	**ft_env_to_array(t_env **env)
{
	char	**result;
	int		count;

	if (!env)
		return (NULL);
	count = ft_count_env_vars(env);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	ft_fill_env_array(result, env);
	return (result);
}
