#ifndef HNM_H
#define HNM_H

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <ctype.h>

/* 32-bit ELF processing functions */
void process_elf_file32(char *file_path);
int read_elf_data(FILE *file, Elf32_Ehdr *elf_header,
		  Elf32_Shdr **section_headers, char *file_path);
int find_and_read_tables(FILE *file, Elf32_Shdr *section_headers,
			 Elf32_Ehdr *elf_header, Elf32_Sym **symbol_table,
			 char **string_table, Elf32_Shdr *symbol_table_header,
			 char *file_path);
void print_symbol_table32(Elf32_Shdr *section_header, Elf32_Sym *symbol_table,
			  char *string_table, Elf32_Shdr *section_headers);
char get_symbol_type(Elf32_Sym symbol, Elf32_Shdr *section_headers);

/* 64-bit ELF processing functions */
void process_elf_file64(char *file_path);
int read_elf_data64(FILE *file, Elf64_Ehdr *elf_header,
		    Elf64_Shdr **section_headers, char *file_path);
int find_and_read_tables64(FILE *file, Elf64_Shdr *section_headers,
			   Elf64_Ehdr *elf_header, Elf64_Sym **symbol_table,
			   char **string_table, Elf64_Shdr *symbol_table_header,
			   char *file_path);
void print_symbol_table64(Elf64_Shdr *section_header, Elf64_Sym *symbol_table,
			  char *string_table, Elf64_Shdr *section_headers);
char get_symbol_type64(Elf64_Sym symbol, Elf64_Shdr *section_headers);

#endif /* HNM_H */ 
