/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:12:43 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/20 12:16:44 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	set_type(t_list *node)
{
	if (!ft_strncmp(node->content, "echo", 10))
		node->type = echo_a;
	else if (!ft_strncmp(node->content, "cd", 10))
		node->type = cd_a;
	else if (!ft_strncmp(node->content, "pwd", 10))
		node->type = pwd_a;
	else if (!ft_strncmp(node->content, "export", 10))
		node->type = export_a;
	else if (!ft_strncmp(node->content, "unset", 10))
		node->type = unset_a;
	else if (!ft_strncmp(node->content, "env", 10))
		node->type = env_a;
	else if (!ft_strncmp(node->content, "exit", 10))
		node->type = exit_a;
	else if (!ft_strncmp(node->content, "\"", 1)
		|| !(!ft_strncmp(node->content, "\'", 1)))
		node->type = text_a;
	else
		node->type = command_a;
	return (set_type2(node));
}

int	set_type2(t_list *node)
{
	if (!ft_strncmp(node->content, "<", 2))
		node->type = re_in;
	else if (!ft_strncmp(node->content, ">", 2))
		node->type = re_out;
	else if (!ft_strncmp(node->content, "<<", 3))
		node->type = he_doc;
	else if (!ft_strncmp(node->content, ">>", 3))
		node->type = out_app;
	return (0);
}

void	define_type(t_shell *shell)
{
	t_list	*ptr;
	int		i;

	i = 0;
	if (!shell->lists)
		return ;
	while (shell->lists[i])
	{
		ptr = shell->lists[i];
		set_type(ptr);
		if (!ft_strncmp(ptr->content, "echo", 10) && ptr->next
			&& check_n_flag(ptr->next->content))
		{
			ptr = define_flag(ptr);
		}
		ptr = ptr->next;
		define_type_helper(ptr);
		i++;
	}
	ptr = NULL;
}

t_list	*define_flag(t_list *ptr)
{
	ptr->next->type = flag_a;
	return (ptr->next);
}

int	check_n_flag(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	c = str[i];
	while (str[i])
	{
		if (str[i] != c)
		{
			return (0);
		}
		i++;
	}
	if (c == 0)
		return (0);
	return (1);
}
