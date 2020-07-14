/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 13:15:26 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/14 18:24:24 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "libft.h"
#include "ft_printf.h"

void	sha224_string(char *string, t_opt opt)
{
	t_sha_ctx		context;
	unsigned char	digest[SHA224HashSize];
	unsigned int	len;

	len = ft_strlen(string);
	sha224_init(&context);
	sha256_update(&context, (unsigned char *)string, len);
	sha256_final(&context, digest, SHA224HashSize);
	digest_print("SHA224 (\"%s\") = ", string, digest, opt);
}

void	sha224_input(t_opt opt)
{
	unsigned char	buff[16];
	t_sha_ctx		context;
	unsigned char	digest[SHA224HashSize];
	unsigned int	len;
	int				i;

	sha224_init(&context);
	while ((len = read(STDIN_FILENO, buff, 16)) > 0)
	{
		i = -1;
		sha256_update(&context, buff, len);
		if (opt & INPUT)
			while (++i < (int)len)
				ft_putchar(buff[i]);
	}
	sha256_final(&context, digest, SHA224HashSize);
	digest_print("", "", digest, opt);
}

void	sha224_file(char *file, t_opt opt)
{
	int				fd;
	unsigned char	buff[1024];
	t_sha_ctx		context;
	unsigned char	digest[SHA224HashSize];
	unsigned int	len;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_printf("ft_ssl: sha224: %s: No such file or directory\n");
	else
	{
		sha224_init(&context);
		while ((len = read(fd, buff, 1024)) > 0)
			sha256_update(&context, buff, len);
		sha256_final(&context, digest, SHA224HashSize);
		close(fd);
		digest_print("SHA224 (%s) = ", file, digest, opt);
	}
}

int		sha224_parse(t_opt *opt, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] == '-' && ft_strcmp(argv[i - 1], "-s"))
	{
		if (ft_strcmp(argv[i], "-p") == 0)
			sha224_input(*opt |= INPUT);
		else if (ft_strcmp(argv[i], "-r") == 0)
			*opt |= REV;
		else if (ft_strcmp(argv[i], "-q") == 0)
			*opt |= QUIET;
		else if (ft_strcmp(argv[i], "-s") == 0)
		{
			if (argv[++i])
				sha224_string(argv[i], *opt);
			else
				ft_putendl_fd("-s: missing argument", 2);
		}
		i++;
	}
	return (i);
}

int		ft_sha224(int argc, char **argv)
{
	int		i;
	t_opt	opt;

	opt = 0;
	g_hash_size = 28;
	i = sha224_parse(&opt, argc, argv);
	if (i == argc && (argv[i - 1][0] == '-' || i == 1) && !(opt & INPUT))
		sha224_input(opt);
	while (i < argc)
	{
		sha224_file(argv[i], opt);
		i++;
	}
	return (0);
}
