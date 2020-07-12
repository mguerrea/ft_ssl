/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:31:47 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/12 11:59:29 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_H
#define SHA_H

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

enum {
    SHA1_block_Size = 64, SHA224_block_Size = 64,
    SHA256_block_Size = 64, SHA384_block_Size = 128,
    SHA512_block_Size = 128,
    USHA_Max_block_Size = SHA512_block_Size,

    SHA1HashSize = 20, SHA224HashSize = 28, SHA256HashSize = 32,
    SHA384HashSize = 48, SHA512HashSize = 64,
    USHAMaxHashSize = SHA512HashSize,

    SHA1HashSizeBits = 160, SHA224HashSizeBits = 224,
    SHA256HashSizeBits = 256, SHA384HashSizeBits = 384,
    SHA512HashSizeBits = 512, USHAMaxHashSizeBits = SHA512HashSizeBits
};

typedef struct s_sha_ctx {
    uint32_t state[SHA256HashSize/4]; /* Message Digest */
    uint64_t bitlen;
    int_least16_t index;  /* block array index */
                                        /* 512-bit message blocks */
    uint8_t block[SHA256_block_Size];
} t_sha_ctx;

void sha256_update(t_sha_ctx *context, const uint8_t *message_array,
    unsigned int length);
void sha256_final(t_sha_ctx *context, uint8_t digest[], int HashSize);
void sha256_transform(t_sha_ctx *context);
uint32_t sigma(uint32_t x, int n);
uint32_t sha_ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t sha_maj(uint32_t x, uint32_t y, uint32_t z);

#endif