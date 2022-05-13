#include <stdio.h>

void print_array(int *array, int length);
void copy_array(int *original, int *copy_of_array, int length);
void flip_array(int *array, int *copy_array, int length);
void convert_decimal_to_binary_representation(unsigned int a, int *binary_representation);
double pow(double base, double power);
char convert_binary_to_character(int *binary, int number_of_bits);
void initialize_array(int **array, unsigned long length);
unsigned long number_of_characters_in_file(FILE *txt_file);
bool is_full_character(int i, int number_of_bits_in_each_character);
bool is_last_iteration(int iteration_number, int number_of_iterations);
void reset_array_to_zeros(int *array, unsigned long length);
int number_of_bits_in_last_chararcter(int i, int number_of_bits_in_each_character);
void put_converted_characters_in_file(FILE *txt_file, int *binary_representation_of_characters, int number_of_bits_in_each_character, int ascii_value_difference,unsigned long  number_of_real_bits_in_txt);
void reset_zero_after_realloc(int *array, int old_size, int new_size);
bool is_initialization_done(int i,int number_of_characters_in_file,int index);
int* initialize_array_of_binary_representations_of_characters(FILE *base_file, unsigned long number_of_characters_in_file, int ascii_value_difference, int number_of_bits_in_each_character);
