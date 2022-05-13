#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "convert_text.h"
#define FIVE_BITS 5
#define BYTE 8
#define BASE_OF_BINARY 2

void copy_array(int *original, int *copy_of_array, int length)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		copy_of_array[i] = original[i];
	}
}

void flip_array(int *array, int *copy_array, int length)
{
	int i = 0;
	int j = 0;
	for (i = (length - 1); i >= 0; i--)
	{
		array[i] = copy_array[j];
		j++;
	}
}

void convert_decimal_to_binary_representation(unsigned int a, int *binary_representation)
{
	unsigned int temp_digit = 0;
	int copy_binary_representation[BYTE] = {0};
	int i = 0;
	do
	{
		temp_digit = a % 2;
		a = a / 2;
		binary_representation[i] = temp_digit;
		i++;
	} while (a != 0);

	copy_array(binary_representation, copy_binary_representation, BYTE);
	flip_array(binary_representation, copy_binary_representation, BYTE);
}

double pow(double base, double power)
{
	int i = 0;
	double result = base;

	if (power == 0)
	{
		return 1;
	}
	for (i = 0; i < power - 1; i++)
	{
		result *= base;
	}
	return result;
}

char convert_binary_to_character(int *binary, int number_of_bits)
{
	int ascii_value = 0;
	int power = number_of_bits - 1;
	int temp_multiplier = 0;
	char result = '\0';
	int i = 0;
	for (i = 0; i < number_of_bits; i++)
	{
		temp_multiplier = pow(BASE_OF_BINARY, power);
		ascii_value += binary[i] * temp_multiplier;
		power--;
	}
	result = (char)ascii_value;
	return result;
}

void initialize_array(int **array, unsigned long length)
{
	*array = (int *)calloc(length, sizeof(int));
}

unsigned long number_of_characters_in_file(FILE *txt_file)
{
	unsigned long counter = 0;
	char temp_char = getc(txt_file);
	if (txt_file == NULL)
	{
		return 0;
	}
	while (temp_char != EOF)
	{
		counter++;
		temp_char = getc(txt_file);
	}
	rewind(txt_file);
	return counter;
}

bool is_full_character(int i, int number_of_bits_in_each_character)
{
	if ((i == number_of_bits_in_each_character))
	{
		return true;
	}
	return false;
}

bool is_last_iteration(int iteration_number, int number_of_iterations)
{
	if (iteration_number + 1 == number_of_iterations)
	{
		return true;
	}
	return false;
}

void reset_array_to_zeros(int *array, unsigned long length)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		array[i] = 0;
	}
}

int number_of_bits_in_last_chararcter(int i, int number_of_bits_in_each_character)
{
	if ((i + 1) % number_of_bits_in_each_character == 0)
	{
		return number_of_bits_in_each_character;
	}
	return (i + 1) % number_of_bits_in_each_character;
}

void put_converted_characters_in_file(FILE *txt_file, int *binary_representation_of_characters, int number_of_bits_in_each_character, int ascii_value_difference,unsigned long  number_of_real_bits_in_txt)
{
	unsigned char temp_character = '\0';
	int number_of_bits_in_final_chararcter = 0;
	int index_of_temp_chararcter_in_bits = 0;
	int temp_character_in_bits[BYTE] = {0};
	int i = 0;

	for (i = 0; i < number_of_real_bits_in_txt; i++)
	{
		temp_character_in_bits[index_of_temp_chararcter_in_bits] = binary_representation_of_characters[i];
		index_of_temp_chararcter_in_bits++;


		if (is_full_character(index_of_temp_chararcter_in_bits, number_of_bits_in_each_character))
		{
			
			temp_character = convert_binary_to_character(temp_character_in_bits, number_of_bits_in_each_character) + ascii_value_difference;
			putc(temp_character, txt_file);

			reset_array_to_zeros(temp_character_in_bits, number_of_bits_in_each_character);
			index_of_temp_chararcter_in_bits = 0;
			
			if(is_last_iteration(i,number_of_real_bits_in_txt)){
				return;
			}
			temp_character = '\0';
		}
		else if (is_last_iteration(i, number_of_real_bits_in_txt))
		{
			number_of_bits_in_final_chararcter = number_of_bits_in_last_chararcter(i, number_of_bits_in_each_character);
			temp_character = convert_binary_to_character(temp_character_in_bits, number_of_bits_in_final_chararcter) + ascii_value_difference;
			putc(temp_character, txt_file);
			temp_character = '\0';
		}
		
	}
	fseek(txt_file,0,SEEK_SET);
}

int* initialize_array_of_binary_representations_of_characters(FILE *base_file, unsigned long number_of_characters_in_file, int ascii_value_difference, int number_of_bits_in_each_character)
{
	unsigned char temp_char = '\0';
	unsigned int ascii_value_of_temp_character = 0;
	int *characters_of_txt_in_binary = NULL;

	int temp_char_in_binary[BYTE] = {0};
	int index_characters_of_txt_in_binary = 0;
	int i = 0;
	int j = 0;

	initialize_array(&characters_of_txt_in_binary,number_of_characters_in_file * number_of_bits_in_each_character);
	for (i = 0; i < number_of_characters_in_file; i++)
	{
		temp_char = getc(base_file);
		ascii_value_of_temp_character = (unsigned int)(temp_char + ascii_value_difference);
		convert_decimal_to_binary_representation(ascii_value_of_temp_character, temp_char_in_binary);
		for (j = 0; j < number_of_bits_in_each_character; j++)
		{
			index_characters_of_txt_in_binary = (i * number_of_bits_in_each_character) + j;
			if (number_of_bits_in_each_character == FIVE_BITS)
			{
				characters_of_txt_in_binary[index_characters_of_txt_in_binary] = temp_char_in_binary[j + 3];
			}
			else
			{
				characters_of_txt_in_binary[index_characters_of_txt_in_binary] = temp_char_in_binary[j];
			}			
		}
		reset_array_to_zeros(temp_char_in_binary, BYTE);
	}
	fseek(base_file,0,SEEK_SET);
	return characters_of_txt_in_binary;
}

