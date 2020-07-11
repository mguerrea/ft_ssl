/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:35:25 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 17:20:44 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "libft.h"
#include "ft_printf.h"

void    sha256_init(t_sha_ctx *context)
{
  context->index  = 0;
  context->bitlen = 0;

  context->state[0] = 0x6a09e667;
  context->state[1] = 0xbb67ae85;
  context->state[2] = 0x3c6ef372;
  context->state[3] = 0xa54ff53a;
  context->state[4] = 0x510e527f;
  context->state[5] = 0x9b05688c;
  context->state[6] = 0x1f83d9ab;
  context->state[7] = 0x5be0cd19;

  context->Computed  = 0;
  context->Corrupted = 0;
}

void	sha256_string(char *string, t_opt opt)
{
	t_sha_ctx			context;
	 unsigned char	digest[SHA256HashSize];
	unsigned int	len;
    int i;

    (void)opt;
    i = 0;
	len = ft_strlen(string);
	sha256_init(&context);
    SHA256Input(&context, (unsigned char *)string, len);
    SHA224_256ResultN(&context, digest, SHA256HashSize);
    while (i < 32)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
	// md5_update(&context, (unsigned char *)string, len);
	// md5_final(digest, &context);
	// md5_print("MD5 (\"%s\") = ", string, digest, opt);
}

void    sha256_file(char *file)
{
    int				fd;
	unsigned char	buff[1024];
	t_sha_ctx			context;
	unsigned char	digest[32];
	unsigned int	len;
    int i = 0;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_printf("%s: No such file or directory\n");
	else
	{
		sha256_init(&context);
		while ((len = read(fd, buff, 1024)) > 0)
			SHA256Input(&context, buff, len);
		SHA224_256ResultN(&context, digest, SHA256HashSize);
		close(fd);
        while (i < 32)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
		// md5_print("MD5 (%s) = ", file, digest, opt);
	}
}

int     ft_sha256(int argc, char **argv)
{
    (void)argc;
    sha256_file(argv[2]);
//    sha256_string(argv[2], 0);
    return (0);
}