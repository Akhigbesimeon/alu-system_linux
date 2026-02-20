#include "hnm.h"
#include <ctype.h>

/**
 * get_symbol_type64 - Determines the symbol type character
 * @symbol: The ELF symbol structure
 * @section_headers: Array of section headers
 *
 * Return: Character representing the symbol type
 */
char get_symbol_type64(Elf64_Sym symbol, Elf64_Shdr *section_headers)
{
	char symbol_type = '?';
	Elf64_Shdr symbol_section;

	if (ELF64_ST_BIND(symbol.st_info) == STB_WEAK)
	{
		if (symbol.st_shndx == SHN_UNDEF)
			symbol_type = 'w';
		else if (ELF64_ST_TYPE(symbol.st_info) == STT_OBJECT)
			symbol_type = 'V';
		else
			symbol_type = 'W';
	}
	else if (symbol.st_shndx == SHN_UNDEF)
		symbol_type = 'U';
	else if (symbol.st_shndx == SHN_ABS)
		symbol_type = 'A';
	else if (symbol.st_shndx == SHN_COMMON)
		symbol_type = 'C';
	else if (symbol.st_shndx < SHN_LORESERVE)
	{
		symbol_section = section_headers[symbol.st_shndx];
		if (ELF64_ST_BIND(symbol.st_info) == STB_GNU_UNIQUE)
			symbol_type = 'u';
		else if (symbol_section.sh_type == SHT_NOBITS &&
			 symbol_section.sh_flags == (SHF_ALLOC | SHF_WRITE))
			symbol_type = 'B';
		else if (symbol_section.sh_type == SHT_PROGBITS)
		{
			if (symbol_section.sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
				symbol_type = 'T';
			else if (symbol_section.sh_flags == SHF_ALLOC)
				symbol_type = 'R';
			else if (symbol_section.sh_flags == (SHF_ALLOC | SHF_WRITE))
				symbol_type = 'D';
		}
		else if (symbol_section.sh_type == SHT_DYNAMIC)
			symbol_type = 'D';
		else
			symbol_type = 't';
	}
	return (symbol_type);
}

/**
 * print_symbol_table64 - Prints the symbol table for a 64-bit ELF file
 * @section_header: Pointer to the section header of the symbol table
 * @symbol_table: Pointer to the beginning of the symbol table
 * @string_table: Pointer to the string table
 * @section_headers: Pointer to the array of section headers
 *
 * Return: void
 */
void print_symbol_table64(Elf64_Shdr *section_header, Elf64_Sym *symbol_table,
			  char *string_table, Elf64_Shdr *section_headers)
{
	int i, symbol_count;
	char *symbol_name, symbol_type;
	Elf64_Sym symbol;

	symbol_count = section_header->sh_size / sizeof(Elf64_Sym);

	for (i = 0; i < symbol_count; i++)
	{
		symbol = symbol_table[i];
		symbol_name = string_table + symbol.st_name;

		if (symbol.st_name != 0 && ELF64_ST_TYPE(symbol.st_info) != STT_FILE)
		{
			symbol_type = get_symbol_type64(symbol, section_headers);
			if (ELF64_ST_BIND(symbol.st_info) == STB_LOCAL)
				symbol_type = tolower(symbol_type);

			if (symbol_type != 'U' && symbol_type != 'w')
				printf("%016lx %c %s\n", symbol.st_value, symbol_type, symbol_name);
			else
				printf("		 %c %s\n", symbol_type, symbol_name);
		}
	}
}

/**
 * read_elf_data64 - Reads and validates ELF header and section headers
 * @file: File pointer
 * @elf_header: Pointer to store ELF header
 * @section_headers: Pointer to store section headers pointer
 * @file_path: Path to the file being processed
 *
 * Return: 1 on success, 0 on failure
 */
int read_elf_data64(FILE *file, Elf64_Ehdr *elf_header,
		    Elf64_Shdr **section_headers, char *file_path)
{
	int is_little_endian, is_big_endian;

	fread(elf_header, sizeof(Elf64_Ehdr), 1, file);

	if (elf_header->e_ident[EI_CLASS] != ELFCLASS32 &&
	    elf_header->e_ident[EI_CLASS] != ELFCLASS64)
	{
		fprintf(stderr, "./hnm: %s: unsupported ELF file format\n", file_path);
		return (0);
	}

	is_little_endian = (elf_header->e_ident[EI_DATA] == ELFDATA2LSB);
	is_big_endian = (elf_header->e_ident[EI_DATA] == ELFDATA2MSB);

	if (!is_little_endian && !is_big_endian)
	{
		fprintf(stderr, "./hnm: %s: unsupported ELF file endianness\n", file_path);
		return (0);
	}

	*section_headers = malloc(elf_header->e_shentsize * elf_header->e_shnum);
	if (*section_headers == NULL)
	{
		fprintf(stderr, "./hnm: %s: memory allocation error\n", file_path);
		return (0);
	}

	fseek(file, elf_header->e_shoff, SEEK_SET);
	fread(*section_headers, elf_header->e_shentsize, elf_header->e_shnum, file);

	return (1);
}

/**
 * find_and_read_tables64 - Locates and reads symbol and string tables
 * @file: File pointer
 * @section_headers: Array of section headers
 * @elf_header: ELF header structure
 * @symbol_table: Pointer to store symbol table pointer
 * @string_table: Pointer to store string table pointer
 * @symbol_table_header: Pointer to store symbol table header
 * @file_path: Path to the file being processed
 *
 * Return: 1 on success, 0 on failure
 */
int find_and_read_tables64(FILE *file, Elf64_Shdr *section_headers,
			   Elf64_Ehdr *elf_header, Elf64_Sym **symbol_table,
			   char **string_table, Elf64_Shdr *symbol_table_header,
			   char *file_path)
{
	int i, symbol_table_index = -1, string_table_index;
	Elf64_Shdr string_table_header;

	for (i = 0; i < elf_header->e_shnum; i++)
	{
		if (section_headers[i].sh_type == SHT_SYMTAB)
		{
			symbol_table_index = i;
			break;
		}
	}

	if (symbol_table_index == -1)
	{
		fprintf(stderr, "./hnm: %s: no symbols\n", file_path);
		return (0);
	}

	*symbol_table_header = section_headers[symbol_table_index];
	*symbol_table = malloc(symbol_table_header->sh_size);

	fseek(file, symbol_table_header->sh_offset, SEEK_SET);
	fread(*symbol_table, symbol_table_header->sh_size, 1, file);

	string_table_index = symbol_table_header->sh_link;
	string_table_header = section_headers[string_table_index];

	*string_table = malloc(string_table_header.sh_size);

	fseek(file, string_table_header.sh_offset, SEEK_SET);
	fread(*string_table, string_table_header.sh_size, 1, file);

	return (1);
}

/**
 * process_elf_file64 - Processes a 64-bit ELF file
 * @file_path: Path to the ELF file to be processed
 *
 * Return: void
 */
void process_elf_file64(char *file_path)
{
	FILE *file;
	Elf64_Ehdr elf_header;
	Elf64_Shdr *section_headers = NULL;
	Elf64_Sym *symbol_table = NULL;
	char *string_table = NULL;
	Elf64_Shdr symbol_table_header;

	file = fopen(file_path, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "./hnm: %s: failed to open file\n", file_path);
		return;
	}

	if (!read_elf_data64(file, &elf_header, &section_headers, file_path))
	{
		fclose(file);
		return;
	}

	if (!find_and_read_tables64(file, section_headers, &elf_header, &symbol_table,
				    &string_table, &symbol_table_header, file_path))
	{
		fclose(file);
		free(section_headers);
		return;
	}

	print_symbol_table64(&symbol_table_header, symbol_table,
			     string_table, section_headers);

	fclose(file);
	free(section_headers);
	free(symbol_table);
	free(string_table);
}
