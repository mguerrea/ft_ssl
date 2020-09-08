/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:34:00 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/05 12:51:21 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <stdio.h>

void	md5_string(char *string, t_opt opt)
{
	t_ctx			context;
	unsigned char	digest[16];
	unsigned int	len;

	len = ft_strlen(string);
	md5_init(&context);
	md5_update(&context, (unsigned char *)string, len);
	md5_final(digest, &context);
	digest_print("MD5 (\"%s\") = ", string, digest, opt);
}

void	md5_file(char *file, t_opt opt)
{
	int				fd;
	unsigned char	buff[1024];
	t_ctx			context;
	unsigned char	digest[16];
	int				len;

	if ((fd = open(file, O_RDONLY)) == -1 || read(fd, buff, 0) < 0)
		ft_printf("ft_ssl: md5: %s: No such file or directory\n", file);
	else
	{
		md5_init(&context);
		while ((len = read(fd, buff, 1024)) > 0)
			md5_update(&context, buff, len);
		md5_final(digest, &context);
		close(fd);
		digest_print("MD5 (%s) = ", file, digest, opt);
	}
}

void	md5_input(t_opt opt)
{
	unsigned char	buff[16];
	t_ctx			context;
	unsigned char	digest[16];
	unsigned int	len;
	int				i;

	md5_init(&context);
	while ((len = read(STDIN_FILENO, buff, 16)) > 0)
	{
		i = -1;
		md5_update(&context, buff, len);
		if (opt & INPUT)
			while (++i < (int)len)
				ft_putchar(buff[i]);
	}
	md5_final(digest, &context);
	digest_print("", "", digest, opt);
}

int		md5_parse(t_opt *opt, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] == '-' && ft_strcmp(argv[i - 1], "-s"))
	{
		if (ft_strcmp(argv[i], "-p") == 0)
			md5_input(*opt |= INPUT);
		else if (ft_strcmp(argv[i], "-r") == 0)
			*opt |= REV;
		else if (ft_strcmp(argv[i], "-q") == 0)
			*opt |= QUIET;
		else if (ft_strcmp(argv[i], "-s") == 0)
		{
			if (argv[++i])
				md5_string(argv[i], *opt);
			else
				ft_putendl_fd("-s: missing argument", 2);
		}
		i++;
	}
	return (i);
}

int		ft_md5(int argc, char **argv)
{
	int		i;
	t_opt	opt;

	opt = 0;
	g_hash_size = 16;
	i = md5_parse(&opt, argc, argv);
	if (i == argc && (argv[i - 1][0] == '-' || i == 1) && !(opt & INPUT))
		md5_input(opt);
	while (i < argc)
	{
		md5_file(argv[i], opt);
		i++;
	}
	return (0);
}
