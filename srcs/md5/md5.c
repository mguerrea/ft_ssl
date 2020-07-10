/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:34:00 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/10 18:22:15 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <stdio.h>

void md5_string (char *string, t_opt opt)
{
  t_ctx context;
  unsigned char digest[16];
  unsigned int len;
  
  len = ft_strlen (string);
  md5_init (&context);
  md5_update (&context, (unsigned char *) string, len);
  md5_final (digest, &context);

  // ft_printf ("MD5 (\"%s\") = ", string);
  md5_print("MD5 (\"%s\") = ", string, digest, opt);
  // ft_printf ("\n");
}

void md5_file(char *file, t_opt opt)
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
   //   ft_printf ("MD5 (%s) = ", file);
      md5_print("MD5 (%s) = ", file, digest, opt);
  // md5_print(digest);
  //ft_printf ("\n");
    }
}

void md5_input(t_opt opt)
{
  unsigned char buff[16];
    t_ctx context;
    unsigned char digest[16];
  unsigned int len;
  int i;

  md5_init(&context);
  while((len = read(STDIN_FILENO, buff, 16)) > 0)
  {
      i = -1;
    md5_update(&context, buff, len);
    if (opt & INPUT)
      while (++i < (int)len)
        ft_putchar(buff[i]);
  }
  md5_final(digest, &context);
  md5_print("", "", digest, opt);
//  md5_print(digest);
//  ft_putchar('\n');
}

void md5_dispatch (int argc, char **argv)
{
  int i;
  t_opt opt;

  opt = 0;
  i = 2;
  while (i < argc && argv[i][0] == '-' && ft_strcmp(argv[i - 1], "-s"))
  {
    if (ft_strcmp(argv[i], "-p") == 0)
      md5_input(opt |= INPUT);
    else if (ft_strcmp(argv[i], "-r") == 0)
      opt |= REV;
    else if (ft_strcmp(argv[i], "-q") == 0)
      opt |= QUIET;
    else if (ft_strcmp(argv[i], "-s") == 0)
    {
      if (argv[++i])
        md5_string(argv[i], opt);
      else
        ft_putendl_fd("-s: missing argument", 2);
    }
    i++;
  }
  if (i == argc) // || opt & INPUT)
    md5_input(opt);
  while (i < argc)
  {
    md5_file(argv[i], opt);
    i++;
  }
}