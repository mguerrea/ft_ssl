/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:29:33 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 15:54:59 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "utils.h"

void rsa_opt_init(t_rsa_opt *opt)
{
    (*opt).check = 0;
    (*opt).fd[0] = STDIN_FILENO;
    (*opt).fd[1] = STDOUT_FILENO;
    (*opt).noout = 0;
    (*opt).text = 0;
    (*opt).pubin = 0;
    (*opt).pubout = 0;
    (*opt).modulus = 0;
    (*opt).format[0] = PEM;
    (*opt).format[1] = PEM;
    (*opt).pass[0] = NULL;
    (*opt).pass[1] = NULL;
    (*opt).des = 0;
}

int rsa_parsing(t_rsa_opt *opt, int argc, char **argv)
{
    int i;

    rsa_opt_init(opt);
    i = 1;
    while (i < argc)
    {
        if (ft_strcmp(argv[i], "-out") == 0 && argv[i + 1])
            if (((*opt).fd[1] = open(argv[i + 1], 01101, 0666)) == -1)
                return (error_file(argv[i + 1], "rsa"));
        if (ft_strcmp(argv[i], "-in") == 0 && argv[i + 1])
            if (((*opt).fd[0] = open(argv[i + 1], O_RDONLY)) == -1)
                return (error_file(argv[i + 1], "rsa"));
        if (ft_strcmp(argv[i], "-text") == 0)
            (*opt).text = 1;
        if (ft_strcmp(argv[i], "-noout") == 0)
            (*opt).noout = 1;
        if (ft_strcmp(argv[i], "-pubout") == 0)
            (*opt).pubout = 1;
        if (ft_strcmp(argv[i], "-pubin") == 0)
            (*opt).pubin = 1;
        if (ft_strcmp(argv[i], "-modulus") == 0)
            (*opt).modulus = 1;
        if (ft_strcmp(argv[i], "-inform") == 0 && argv[i + 1])
            if (ft_strcmp(argv[i + 1], "DER") == 0)
                (*opt).format[0] = DER;
        if (ft_strcmp(argv[i], "-outform") == 0 && argv[i + 1])
            if (ft_strcmp(argv[i + 1], "DER") == 0)
                (*opt).format[1] = DER;
        if (ft_strcmp(argv[i], "-passin") == 0 && argv[i + 1])
            (*opt).pass[0] = argv[i + 1];
        if (ft_strcmp(argv[i], "-passout") == 0 && argv[i + 1])
            (*opt).pass[1] = argv[i + 1];
        if (ft_strcmp(argv[i], "-des") == 0)
            (*opt).des = 1;
        i++;
    }
    return (0);
}