/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:19:23 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/17 20:19:33 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		recursive(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;

	dir = NULL;
	dir_read = NULL;
	if ((dir = opendir(file)) == NULL)
	{
		perror("opendir\n");
		return (1);
	}
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' ||
			(dir_read->d_name[0] == '.' && options->all))
			if (dir_read->d_type == 4)
			{
				set_path(options, dir_read->d_name);
				ft_printf("\n%s:\n", options->cur_dir);
				processing(options, options->cur_dir);
				options->cur_dir[ft_strlen(options->cur_dir) -
					ft_strlen(dir_read->d_name) - 1] = '\0';
			}
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir\n");
	return (0);
}
