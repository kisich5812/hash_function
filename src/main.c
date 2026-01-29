#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

Str* read_line();
int make_hash(Str* phrase, Flags* params, int start_num);
int extend(Str* phrase, int start_num);
int symbol_hash(int sym, int start_num);
int start_number(Str* phrase);

int main(int argc, char* argv[]) {
	Flags* params = process_flags(argc, argv);
	if (!params) return -1;
	Str* phrase = read_line();
	make_hash(phrase, params, start_number(phrase));
	
	for(int i = 0; i < params->len; i++)
		printf("%c", params->alph[phrase->str[i]]);
	printf("\n");	

	if(phrase->free) free(phrase->str);
	return 0;
}

Str* read_line() {
	Str* input_str = (Str*) calloc(1, sizeof(Str));
	printf("Введите фразу:\n");
	getline(&input_str->str, &input_str->len, stdin);
	input_str->len = strlen(input_str->str);
	input_str->str [input_str->len - 1] = 0;
	input_str->len--;
	return input_str;
}

int start_number(Str* phrase) {
	int sum = 0;
	for(int i = 0; i < phrase->len; i++)
		sum += phrase->str[i];
	sum = sum ^ 139;
	sum = sum % 47;
	return sum;
}

int make_hash(Str* phrase, Flags* params, int start_num) {
	size_t alph_len = strlen(params->alph);
	while (phrase->len < params->len)
		extend(phrase, start_num);

	phrase->str[0] = symbol_hash(phrase->str[0], start_num) % alph_len;
	for(int i = 1; i < phrase->len; i++) {
		if (i >= params->len)
			phrase->str[i % params->len] = (phrase->str[i % params->len] + phrase->str[i-1] + symbol_hash(phrase->str[i], start_num)) % alph_len;
		phrase->str[i] = (phrase->str[i-1] + symbol_hash(phrase->str[i], start_num)) % alph_len;
	}
	return 0;
}

int extend(Str* phrase, int start_num) {
	char* mid_str = (char*) calloc(phrase->len * 2, sizeof(char));
	for(int i = 0; i < phrase->len; i++) {
		int mid_value = symbol_hash(phrase->str[i], start_num);
		while(mid_value < 1000)
			mid_value *= 29;
		mid_str[2*i] = mid_value%100;
		mid_str[2*i+1] = (mid_value/100)%1000;
	}
	if(phrase->free) free(phrase->str);
	phrase->free = 1;
	phrase->len *= 2;
	phrase->str = mid_str;
}

int symbol_hash(int sym, int start_num) {
	int start = start_num;
	int rezult = start + sym;
	rezult = rezult ^ 147;
	rezult += rezult % 73;
	rezult *= 7;
	rezult = rezult ^ 23;
	return rezult;
}
