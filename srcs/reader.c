/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:22:26 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/02 17:02:32 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	reading_no_dir(t_info *list, char name[1024], t_options *options, int i)
{
	char	*tmp;

	tmp = list[i].name;
	list[i].name = ft_strdup(name);
	// free(tmp);
	if (list[i].flag_link)
		options->cur_dir = ft_strdup("\0");
	set_path(options, NULL, name);
	if (get_list_params(options->cur_dir, list, i))
		return (0);
	options->cur_dir[ft_strlen(options->cur_dir) - ft_strlen(name) - 1] = '\0';
	if (list[i].name[0] != '.' || options->all)
		options->count++;
	return (0);
}

int	reading(t_info *list, char *file, t_options *options)
{
	DIR				*dir;
	struct dirent	*dir_read;
	int				i;

	dir = NULL;
	dir_read = NULL;
	i = 0;
	if ((dir = opendir(file)) == NULL)
		error_message("opendir_reading");
	dir_read = readdir(dir);
	i = 0;
	while (dir_read != NULL)
	{
		reading_no_dir(list, dir_read->d_name, options, i);
		i++;
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		perror("closedir_reading");
	return (i);
}
