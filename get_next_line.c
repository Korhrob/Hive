#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

#define BUFFER_SIZE 2

static struct s_read_buffer buffer;

void	init_buffer(int fd)
{
	if (fd <= 0) // invalid fd
		return;
	if (buffer.str != 0) // buffer already exists
		return;
	printf("INIT BUFFER, size %u\n", BUFFER_SIZE); // Debug
	buffer.index = 0;
	buffer.bytes = 0;
	buffer.str = malloc(BUFFER_SIZE);
	if (buffer.str == 0) // malloc fail
		return;
	buffer.bytes = read(fd, buffer.str, BUFFER_SIZE);
	if (buffer.bytes <= 0) // Read fail
	{
		free(buffer.str);
		printf("Nothing to read\n"); // Debug
	}
}

void	free_buffer()
{
	if (buffer.bytes < BUFFER_SIZE) // change to guard clause
	{
		// Debug print
		printf("- END OF FILE -\ncur index %u, bytes read %u, expected bytes %u\n", buffer.index, buffer.bytes, BUFFER_SIZE);
		free(buffer.str);
		buffer.bytes = 0;
	}
}

char	copy_to(char *dest, char chr)
{
	char *temp;

	temp = malloc(strlen(dest) + 2);
	// copy dest temp
	// copy chr to temp
	// add null terminator
	free(dest);
	dest = temp;
	return (chr);
}

char	*get_next_line(int fd)
{
	char	*output;
	char	last_char;

	init_buffer(fd);
	if (buffer.bytes == 0) // could squeeze into init_buffer
		return (0);
	while (buffer.index < BUFFER_SIZE)
	{
		last_char = buffer.str[buffer.index++];
		write(1, &last_char, 1); // copy_to(output, last_char);
		if (buffer.index >= BUFFER_SIZE)
		{
			buffer.bytes = read(fd, buffer.str, BUFFER_SIZE);
			if (buffer.bytes > 0)
				buffer.index = 0;
			else
				break; // end of file
		}
		if (last_char == '\n' || last_char == 0)
			break;
	}
	free_buffer();
	return (0);
}

int	main(void)
{

	int		fd;
	char	*str;

	printf("--start program, BUFFER_SIZE=%d--\n\n", BUFFER_SIZE);

	fd = open("text.txt", O_RDONLY);

	for (int i = 0; i < 5; i++)
	{
		//printf("\nline %i:", i);
		str = get_next_line(fd);
	}

	printf("\n\n--program mid point--\n\n");

	for (int i = 0; i < 5; i++)
	{
		//printf("\nline %i:", i);
		str = get_next_line(fd);
	}

	printf("\n\n--program ended--\n\n");

	close(fd);

}
