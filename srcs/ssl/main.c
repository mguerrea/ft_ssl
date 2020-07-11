/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:14:36 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 16:12:23 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"

int		usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (1);
}

int		invalid_command(char *cmd)
{
	ft_printf("ft_ssl: Error \'%s\' is an invalid command\n", cmd);
	ft_printf("\nStandard commands:\n");
	ft_printf("\nMessage Digest commands:\nmd5\n");
	ft_printf("\nCipher commands:\n");
	return (1);
}

int		main(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 1)
		return (usage());
	while (g_commands[i].command)
	{
		if (!ft_strcmp(g_commands[i].command, argv[1]))
			return (g_commands[i].algo(argc, argv));
		i++;
	}
	return (invalid_command(argv[1]));
}
