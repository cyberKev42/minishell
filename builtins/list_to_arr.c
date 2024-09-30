/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:30:03 by mvolgger          #+#    #+#             */
/*   Updated: 2024/07/20 15:54:58 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/builtins.h"

int	ft_listsize(t_env *myenv)
{
	int		i;
	t_env	*temp;

	i = 0;
	if (!myenv)
		return (0);
	temp = myenv;
	while (myenv != NULL)
	{
		i++;
		myenv = myenv->next;
	}
	myenv = temp;
	return (i);
}

char	*join_key_value(t_env *temp, t_shell *data)
{
	char	*str;
	char	*keytemp;

	str = NULL;
	keytemp = ft_strjoin(data, temp->key_value->key, "=");
	if (temp->key_value->value)
		str = ft_strjoin(data, keytemp, temp->key_value->value);
	else
		return (keytemp);
	free(keytemp);
	return (str);
}

char	**transform_list_to_arr(t_shell *data, t_env *myenv)
{
	char	**arr;
	t_env	*temp;
	int		i;
	int		j;

	i = ft_listsize(myenv);
	j = 0;
	temp = myenv;
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (arr == NULL)
		free_exit(data, 1);
	arr[i] = NULL;
	while (j < i)
	{
		arr[j] = join_key_value(temp, data);
		if (!arr[j])
			free_exit(data, 1);
		temp = temp->next;
		j++;
	}
	return (arr);
}

void	env_duplicate(t_shell *data, char **envp)
{
	int		i;

	i = 0;
	if (!envp || !envp[i])
		return (handle_empty_env(data));
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			create_shlvl(data, envp[i]);
			i++;
		}
		append_node(data, NULL, NULL, envp[i]);
		i++;
	}
	if (check_missing_env(data) == -1)
		handle_empty_env(data);
}

char	*get_key(t_shell *data, char *str)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		free_exit(data, 138);
	key[i] = '\0';
	while (j < i)
	{
		key[j] = str[j];
		j++;
	}
	return (key);
}
