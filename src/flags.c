#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "flags.h"

int _string_to_int(char* str);
int _print_help();

Flags* process_flags(int val_args, char** args) {
	Flags* f = (Flags*) calloc(1, sizeof(Flags));
	if (!f) return fprintf(stderr, "Ошибка выделения памяти!\n"), NULL;
	f->alph = (char*)DEFAULT_ALPH;
	f->len = DEFAULT_LEN;
	
	for (int i = 0; i<val_args; i++) {
		if (strcmp(args[i], "--alph") == 0) {
			if (i+1 < val_args)
				f->alph = args[i+1];
			else 
				return fprintf(stderr, "Не задан алфавит!\n"), NULL;
		}
		else if (strcmp(args[i], "--len") == 0) {
			if (i+1 < val_args) {
				f->len = _string_to_int(args[i+1]);
				if(f->len<0)
					return fprintf(stderr, "Некорректно задана длина!\n"), NULL;
			}
			else 
				return fprintf(stderr, "Не задана длина!\n"), NULL;
		}
		else if (strcmp(args[i], "--help") == 0)
			return _print_help(), NULL;
	}
	return f;
}

int _string_to_int(char* str) {
	int rez = 0;
	int str_len = strlen(str);
	for(int i = 0; i<str_len; i++) {
		if(isdigit(str[i]))
			rez = rez*10 + str[i] - '0';
		else
			return -1;
	}
	return rez;
}

int _print_help() {
	printf("--len <number>\t\tЗадать длину хэша\n"\
			"--alph <symbols>\tЗадать символы для записи хэша\n"\
			"--help\t\t\tПоказать эту справку\n");
	return 0;
}
