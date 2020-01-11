/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:19:23 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/11 22:13:05 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	**set_dir_array(char **array, int len)
{
	int	i;

	i = 0;
	if (!(array = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	array[len] = NULL;
	return (array);
}

void	free_array(char **array, int len)
{
	while (array[len])
		free(array[len--]);
	free(array);
}

char	**recursive_create_array(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;
	char			**dir_array;
	int				len;
	int				current;

	len = 0;
	if (!(dir = opendir(file)))
		return (NULL);
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' || (options->all &&
			(dir_read->d_name[0] == '.' && dir_read->d_name[1] != '.' &&
			dir_read->d_name[1] != '\0')))
			if (dir_read->d_type == 4)
				len++;
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (NULL);

	current = 0;
	dir_array = NULL;
	dir_array = set_dir_array(dir_array, len);
	if (dir_array == NULL)
		error_message("error malloc()", 1);
	if (!(dir = opendir(file)))
		return (NULL);
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' || (options->all &&
			(dir_read->d_name[0] == '.' && dir_read->d_name[1] != '.' &&
			dir_read->d_name[1] != '\0')))
			if (dir_read->d_type == 4)
			{
				dir_array[current] = ft_strdup(dir_read->d_name);
				current++;
			}
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (NULL);
	sort_ascii(dir_array, len);
	return (dir_array);
}

int		recursive(t_options *options, char *file)
{
	char			*file_for_r;
	char			**dir_array;
	int				i;

	dir_array = recursive_create_array(options, file);
	if (dir_array == NULL)
		return (error_message(file, 0));
	i = 0;
	while (dir_array[i])
	{
		update_path(options, file);
		set_path(options, dir_array[i]);
		ft_printf("\n%s:\n", options->cur_dir);
		file_for_r = ft_strdup(options->cur_dir);
		processing(options, file_for_r);
		free(file_for_r);
		i++;
	}
	free_array(dir_array, i);
	return (0);
}
