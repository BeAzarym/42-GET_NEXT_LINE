/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:41:03 by cchabeau          #+#    #+#             */
/*   Updated: 2023/02/17 20:15:03 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main()
{
	char buff[BUFFER_SIZE];
	char str[BUFFER_SIZE];
	int fd = open("test.txt", O_RDONLY);
	read(fd,buff,BUFFER_SIZE);
	int eol = check_endline(buff);
	ft_bzero(str,eol);
	ft_strlcpy(str,buff,eol);
	printf("|%d|%s|\n",eol,str);
	
}