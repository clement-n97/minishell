/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:29:19 by rlefort           #+#    #+#             */
/*   Updated: 2025/12/18 13:07:37 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_or_create(t_env_set_args *args, t_env **env)
{
	if (args->curr)
	{
		free(args->curr->value);
		args->curr->value = ft_strdup(args->value);
	}
	else
	{
		args->curr = ft_new_env_var(args->name, args->value, NULL);
		if (args->curr)
		{
			if (args->prev)
				args->prev->next = args->curr;
			else
				*env = args->curr;
		}
	}
}

int	ft_set_env(char *name, char *value, t_env **env)
{
	t_env_set_args	args;
	int i;

	if (!env || !name || !name[0] || !value)
		return (1);
	if (ft_isalpha(name[0] || name[0] == '_'))
		return (1);
	i = 0;
	while (name[i] != 0)
	{
		if (ft_isalnum(name[i] || name[i] == '_'))
			return (1);
		i++;
	}
	args.curr = *env;
	args.prev = NULL;
	args.name = name;
	args.value = value;
	while (args.curr && ft_strcmp(name, args.curr->name))
	{
		args.prev = args.curr;
		args.curr = args.curr->next;
	}
	update_or_create(&args, env);
	return (0);
}

char	*ft_get_env_value(char *name, t_env **env)
{
	char	*value;
	t_env	*curr;

	if (!name || !name[0] || !env)
		return (NULL);
	curr = *env;
	value = NULL;
	while (curr)
	{
		if (curr->name && !ft_strcmp(curr->name, name))
		{
			value = curr->value;
			break ;
		}
		curr = curr->next;
	}
	return (value);
}

int	ft_rm_env(char *name, t_env **env)
{
	t_env	*prev;
	t_env	*curr;

	if (!name || !name[0] || !env)
		return (1);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(name, curr->name))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

t_env	*ft_initialize_env(void)
{
	char	*cwd;
	t_env	*env;

	env = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		env = ft_new_env_var("PWD", cwd, NULL);
		free(cwd);
	}
	ft_set_env("SHLVL", "1", &env);
	ft_set_env("PATH", getenv("PATH"), &env);
	ft_set_env("HOME", getenv("HOME"), &env);
	return (env);
}
