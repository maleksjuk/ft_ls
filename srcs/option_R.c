/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:19:23 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/09 21:02:21 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		recursive(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;
	char			*file_for_r;

	if (!(dir = opendir(file)))
	{
		perror(file);
		return (1);
	}
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' || (options->all &&
			(dir_read->d_name[0] == '.' && dir_read->d_name[1] != '.' &&
			dir_read->d_name[1] != '\0')))
			if (dir_read->d_type == 4)
			{
				update_path(options, file);
				set_path(options, dir_read->d_name);
				ft_printf("\n%s:\n", options->cur_dir);
				file_for_r = ft_strdup(options->cur_dir);
				processing(options, file_for_r);
				free(file_for_r);
			}
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir -R");
	return (0);
}
