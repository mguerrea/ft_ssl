/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:14:36 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/05 12:54:24 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "ssl.h"
#include "utils.h"

int			invalid_command(char *cmd)
{
	ft_printf("ft_ssl: Error: \'%s\' is an invalid command\n", cmd);
	ft_printf("\nStandard commands:\n");
	ft_printf("\nMessage Digest commands:\nmd5\nsha256\nsha224\n");
	ft_printf("\nCipher commands:\ndes\ndes-ecb\ndes-cbc\ndes-cfb\n");
	return (1);
}

static void	dispatcher(char **arr)
{
	int i;

	i = 0;
	while (g_commands[i].command)
	{
		if (!ft_strcmp(g_commands[i].command, arr[0]))
		{
			g_commands[i].algo(tablen(arr), arr);
			break ;
		}
		i++;
	}
	if (g_commands[i].command == NULL)
		invalid_command(arr[0]);
}

void		command_line(void)
{
	char	*line;
	char	**arr;
	int		i;

	line = NULL;
	ft_printf("ft_ssl> ");
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		i = 0;
		if (!ft_strcmp(line, "exit") || !(arr = split_quotes(line, ' ')))
			break ;
		if (*line)
			dispatcher(arr);
		ft_strdel(&line);
		free_tab(arr);
		ft_printf("ft_ssl> ");
	}
	if (line)
		ft_strdel(&line);
}

int			main(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 1)
		command_line();
	else
		dispatcher(&(argv[1]));
	return (0);
}
