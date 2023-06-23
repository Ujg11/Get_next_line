#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	char arr[] = "HOLA";

	char res = strlen(arr);
	char res2 = ft_strlen(arr);
	printf("%d\n%d\n", res, res2);
	// Abre el archivo que deseas leer
	fd = open("arxiu.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}

	// Llama a la función get_next_line para leer líneas del archivo
	int i = -1;
	while (++i < 8)
	{
		line = get_next_line(fd);
		//printf("Línea leída: %s\n", line);
		printf("%s\n", line);
		free(line);
	}

	// Cierra el archivo
	close(fd);
	return (0);
}
