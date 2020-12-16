/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:52:41 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 18:25:27 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "utils.h"
#include "libft.h"
#include "md5.h"

#include <stdio.h>

void	pbkdf1_sha256(t_pbkdf *ctx)
{
	int i;
	t_sha_ctx context;
	unsigned char to_hash[1024];
	int len;

	i = 0;
    len = ft_strlen((char *)ctx->pass);
    len = (len > 1016) ? 1016 : len;
	ft_memcpy(to_hash, ctx->pass, len);
	ft_memcpy(to_hash + len, ctx->salt, 8);
	sha256_init(&context);
	sha256_update(&context, to_hash, len + 8);
	sha256_final(&context, to_hash, 32);
	while (++i < ctx->c)
	{
		sha256_init(&context);
		sha256_update(&context, to_hash, 32);
		sha256_final(&context, to_hash, 32);
	}
    ft_memcpy(ctx->key, to_hash, ctx->keylen / 8);
}

void	pbkdf1_md5(t_pbkdf *ctx)
{
	int i;
	t_ctx context;
	unsigned char to_hash[1024];
	int len;

	i = 0;
    len = ft_strlen((char *)ctx->pass);
    len = (len > 1016) ? 1016 : len;
	ft_memcpy(to_hash, ctx->pass, len);
	ft_memcpy(to_hash + len, ctx->salt, 8);
	md5_init(&context);
	md5_update(&context, to_hash, len + 8);
	md5_final(to_hash, &context);
	while (++i < ctx->c)
	{
		md5_init(&context);
		md5_update(&context, to_hash, 16);
		md5_final(to_hash, &context);
	}
    ft_memcpy(ctx->key, to_hash, ctx->keylen / 8);
}