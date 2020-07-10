/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:34:00 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/10 16:29:12 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <stdio.h>

void md5_string (char *string)
{
  t_ctx context;
  unsigned char digest[16];
  unsigned int len;
  
  len = ft_strlen (string);
  md5_init (&context);
  md5_update (&context, (unsigned char *) string, len);
  md5_final (digest, &context);

  printf ("MD5 (\"%s\") = ", string);
  for (int i = 0; i < 16; i++)
    printf ("%02x", digest[i]);
  printf ("\n");
}

void md5_file(char *file)
{
    int fd;
    unsigned char buff[1024];
    t_ctx context;
    unsigned char digest[16];
  unsigned int len;

    if ((fd = open(file, O_RDONLY)) == -1)
      error_file(file);
    else
    {
      md5_init(&context);
      while ((len = read(fd, buff, 1024)) > 0)
        md5_update(&context, buff, len);
      md5_final(digest, &context);
      close(fd);
      printf ("MD5 (%s) = ", file);
  for (int i = 0; i < 16; i++)
    printf ("%02x", digest[i]);
  printf ("\n");
    }
    
}

void md5_input()
{
  
}

void md5_dispatch (int argc, char **argv)
{
  int i;
  t_opt opt;

  opt = 0;
  i = 2;
  while (i < argc && argv[i][0] == '-' && ft_strcmp(argv[i], "-s"))
  {
    if (ft_strcmp(argv[i], "-p") == 0)
      opt |= INPUT;
    else if (ft_strcmp(argv[i], "-r") == 0)
      opt |= REV;
    else if (ft_strcmp(argv[i], "-q") == 0)
      opt |= QUIET;
    i++;
  }
  if (i == argc || opt & INPUT)
    md5_input();
  while (i < argc)
  {
    if (ft_strcmp(argv[i], "-s") == 0 && argv[i + 1])
      md5_string(argv[++i]);
    else if (argv[i])
      md5_file(argv[i]);
    i++;
  }
}