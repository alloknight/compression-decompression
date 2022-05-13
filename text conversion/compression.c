#include "convert_text.c"
#include "compression.h"
#define ASCII_VALUE_DIFFERENCE_FOR_COMPRESSION -97

void put_number_of_junk_bits(FILE *compressed,unsigned long number_of_characters_in_original){
	unsigned long number_of_real_bits_in_original = number_of_characters_in_original * FIVE_BITS;
	char junk_bits = BYTE -(number_of_real_bits_in_original % BYTE);
    junk_bits = junk_bits % BYTE;
    
	putc(junk_bits,compressed);
}

void compress(FILE *original, FILE *compressed){
    unsigned long number_of_characters_in_original = number_of_characters_in_file(original);
	int *characters_of_txt_in_binary = NULL;
    int number_of_bits_in_txt = number_of_characters_in_original * FIVE_BITS;
    put_number_of_junk_bits(compressed,number_of_characters_in_original);
   
    characters_of_txt_in_binary = initialize_array_of_binary_representations_of_characters(original, number_of_characters_in_original, ASCII_VALUE_DIFFERENCE_FOR_COMPRESSION, FIVE_BITS);
    fseek(compressed,1,SEEK_SET);
    put_converted_characters_in_file(compressed, characters_of_txt_in_binary, BYTE, 0,number_of_bits_in_txt);
    free(characters_of_txt_in_binary);
}

int main()
{
    FILE *original = NULL;
    FILE *compressed = NULL;

    compressed = fopen("compressed", "w");
    original = fopen("original.txt", "r");
    
    compress(original,compressed);


    fclose(compressed);
    fclose(original);
    return 0;
}