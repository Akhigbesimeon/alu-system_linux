#include "hnm.h"

/**
 * main - Entry point for the ELF file processing program
 * @argc: The count of command-line arguments
 * @argv: The array of command-line arguments
 *
 * Return: 0 on successful execution, or 0 on error
 */
int main(int argc, char *argv[])
{
	char *file_path;
	FILE *file;
	Elf64_Ehdr elf_header;

	if (argc < 2)
	{
		printf("Il faut fournir un fichier ELF !\n");
		return (0);
	}

	file_path = argv[1];
	file = fopen(file_path, "rb");

	if (file == NULL)
	{
		printf("Il y a une erreur pour de l'ouverture du fichier\n");
		return (0);
	}

	fread(&elf_header, sizeof(Elf64_Ehdr), 1, file);

	if (elf_header.e_ident[EI_CLASS] == ELFCLASS32)
	{
		process_elf_file32(file_path);
	}
	else if (elf_header.e_ident[EI_CLASS] == ELFCLASS64)
	{
		process_elf_file64(file_path);
	}
	else
	{
		printf("Type de fichier ELF non pris en charge...\n");
	}

	fclose(file);
	return (0);
}
