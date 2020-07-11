/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:31:47 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 17:20:20 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA_H
#define SHA_H

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

enum {
    SHA1_Message_Block_Size = 64, SHA224_Message_Block_Size = 64,
    SHA256_Message_Block_Size = 64, SHA384_Message_Block_Size = 128,
    SHA512_Message_Block_Size = 128,
    USHA_Max_Message_Block_Size = SHA512_Message_Block_Size,

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
    int_least16_t index;  /* Message_Block array index */
                                        /* 512-bit message blocks */
    uint8_t Message_Block[SHA256_Message_Block_Size];

    int Computed;                       /* Is the digest computed? */
    int Corrupted;                      /* Is the digest corrupted? */
} t_sha_ctx;

enum {
    shaSuccess = 0,
    shaNull,            /* Null pointer parameter */
    shaInputTooLong,    /* input data too long */
    shaStateError,      /* called Input after FinalBits or Result */
    shaBadParam         /* passed a bad parameter */
};

typedef enum e_opt
{
    REV = 1 << 0,
    QUIET = 1 << 1,
    INPUT = 1 << 2
}           t_opt;

int SHA256Input(t_sha_ctx *context, const uint8_t *message_array,
    unsigned int length);
int SHA224_256ResultN(t_sha_ctx *context,
    uint8_t Message_Digest[], int HashSize);
void sha256_transform(t_sha_ctx *context);

#endif