/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolgger <mvolgger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:38:38 by kbrauer           #+#    #+#             */
/*   Updated: 2024/07/21 18:18:11 by mvolgger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/minishell.h"

int	first_init(t_shell *shell, int argc, char **argv)
{
	if (argc != 1)
	{
		free(shell);
		exit (1);
	}
	argc = 0;
	argv = NULL;
	shell->exp_str = NULL;
	shell->env_line = NULL;
	shell->hname = NULL;
	shell->h_lines = 0;
	shell->flag = 0;
	shell->pid = NULL;
	shell->sig_flag = false;
	shell->cmd = NULL;
	return (0);
}

int	init_values(t_shell *shell)
{
	shell->env_arr = NULL;
	shell->lists = NULL;
	shell->last_return_value = 0;
	shell->n_pipes = 0;
	shell->heredoc_flag = 0;
	shell->del_flag = 0;
	shell->pid = NULL;
	return (0);
}

void	test_malloc(t_shell *shell)
{
	if (!shell)
		exit (0);
}

void	check_input_helper(t_shell *shell)
{
	ft_putstr_fd("minishell: error: invalid number of quotations\n", 2);
	set_return_value(shell, 0);
}

void	define_type_helper(t_list *ptr)
{
	while (ptr)
	{
		ptr->type = text_a;
		set_type2(ptr);
		ptr = ptr->next;
	}
}
