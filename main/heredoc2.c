/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:09:53 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/20 13:30:48 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	cmd_is_null_or_del(char *cmd, int fd, char *arg, t_shell *shell)
{
	if (!cmd)
	{
		exit_helper(shell, arg, 2);
		write(fd, "", 1);
		return (1);
	}
	if (ft_strncmp(cmd, arg, ft_strlen(cmd) + 1) == 0)
	{
		free(cmd);
		return (1);
	}
	return (0);
}

int	no_del(t_shell *shell, t_list *ptr)
{
	int	i;

	i = 0;
	if (!ptr->next)
	{
		ft_putstr_fd("minishell: syntax error near \
unexpected token `", 2);
		if (ptr->content[2] == '|' && ptr->content[3] == 0)
			write(2, "|", 1);
		else if (ptr->content[2] == '|' && ptr->content[3] == '|')
			write(2, "||", 2);
		else
			write(2, "newline", 7);
		write(2, "'\n", 2);
		return (set_return_value(shell, 2), 2);
	}
	return (0);
}

void	handle_node(t_shell *shell, t_list *ptr, char *tmp)
{
	ptr->content = ft_strdup(shell, "<");
	ptr->type = re_in;
	free(ptr->next->content);
	ptr->next->content = tmp;
}

void	set_flag_and_num_lines(int *flag, int *num_lines)
{
	*flag = 0;
	*num_lines = 0;
}

char	*check_g_var(t_shell *shell, int fd)
{
	int		fd_new;
	char	*hname_new;

	shell->heredoc_flag = 1;
	g_var = 0;
	close(fd);
	hname_new = add_hname(shell);
	fd_new = open(hname_new, O_RDWR | O_CREAT | O_TRUNC, 0644);
	negative_fd(shell, fd_new);
	write(fd_new, "\0", 1);
	close(fd_new);
	return (hname_new);
}
