/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:41:03 by cchabeau          #+#    #+#             */
/*   Updated: 2023/02/15 19:44:31 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main()
{
	char buff[500];
	int fd = open("test.txt", O_RDONLY);
	
	read(fd,buff,50);
	printf("|%s|\n",buff);
	
}