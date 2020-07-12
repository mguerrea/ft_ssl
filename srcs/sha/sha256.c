/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:35:25 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/12 12:51:55 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "libft.h"
#include "ft_printf.h"

void	sha256_string(char *string, t_opt opt)
{
	t_sha_ctx		context;
	unsigned char	digest[SHA256HashSize];
	unsigned int	len;

	len = ft_strlen(string);
	sha256_init(&context);
	sha256_update(&context, (unsigned char *)string, len);
	sha256_final(&context, digest, SHA256HashSize);
	digest_print("SHA256 (\"%s\") = ", string, digest, opt);
}

void	sha256_input(t_opt opt)
{
	unsigned char	buff[16];
	t_sha_ctx		context;
	unsigned char	digest[SHA256HashSize];
	unsigned int	len;
	int				i;

	sha256_init(&context);
	while ((len = read(STDIN_FILENO, buff, 16)) > 0)
	{
		i = -1;
		sha256_update(&context, buff, len);
		if (opt & INPUT)
			while (++i < (int)len)
				ft_putchar(buff[i]);
	}
	sha256_final(&context, digest, SHA256HashSize);
	digest_print("", "", digest, opt);
}

void	sha256_file(char *file, t_opt opt)
{
	int				fd;
	unsigned char	buff[1024];
	t_sha_ctx		context;
	unsigned char	digest[32];
	unsigned int	len;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_printf("ft_ssl: sha256: %s: No such file or directory\n");
	else
	{
		sha256_init(&context);
		while ((len = read(fd, buff, 1024)) > 0)
			sha256_update(&context, buff, len);
		sha256_final(&context, digest, SHA256HashSize);
		close(fd);
		digest_print("SHA256 (%s) = ", file, digest, opt);
	}
}

int		sha256_parse(t_opt *opt, int argc, char **argv)
{
	int i;

	i = 2;
	while (i < argc && argv[i][0] == '-' && ft_strcmp(argv[i - 1], "-s"))
	{
		if (ft_strcmp(argv[i], "-p") == 0)
			sha256_input(*opt |= INPUT);
		else if (ft_strcmp(argv[i], "-r") == 0)
			*opt |= REV;
		else if (ft_strcmp(argv[i], "-q") == 0)
			*opt |= QUIET;
		else if (ft_strcmp(argv[i], "-s") == 0)
		{
			if (argv[++i])
				sha256_string(argv[i], *opt);
			else
				ft_putendl_fd("-s: missing argument", 2);
		}
		i++;
	}
	return (i);
}

int		ft_sha256(int argc, char **argv)
{
	int		i;
	t_opt	opt;

	opt = 0;
	g_hash_size = 32;
	i = sha256_parse(&opt, argc, argv);
	if (i == argc && (argv[i - 1][0] == '-' || i == 2) && !(opt & INPUT))
		sha256_input(opt);
	while (i < argc)
	{
		sha256_file(argv[i], opt);
		i++;
	}
	return (0);
}
