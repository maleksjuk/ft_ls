/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:38:00 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/09 19:44:07 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	processing_dir(t_options *options, t_info *list, char *file)
{
	int			count;

	options->flag_list = 0;
	if ((count = reading(list, file, options)) == 0)
		return (-1);
	return (count);
}
