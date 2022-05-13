#include "convert_text.c"
#define ASCII_VALUE_DIFFERENCE_FOR_DECOMPRESSION 97

void decompress(FILE *compressed, FILE *decompressed){
    unsigned long number_of_characters_in_compressed = number_of_characters_in_file(compressed) -1 ;
	int *characters_of_txt_in_binary = NULL;
    int number_of_junk_bits = getc(compressed);
    int number_of_real_bits_in_decompressed = ((number_of_characters_in_compressed) * BYTE) - number_of_junk_bits;

    fseek(compressed,1,SEEK_SET);
    characters_of_txt_in_binary = initialize_array_of_binary_representations_of_characters(compressed, number_of_characters_in_compressed, 0, BYTE);

	put_converted_characters_in_file(decompressed, characters_of_txt_in_binary, FIVE_BITS, ASCII_VALUE_DIFFERENCE_FOR_DECOMPRESSION,number_of_real_bits_in_decompressed);
    free(characters_of_txt_in_binary);
}

int main()
{
    FILE *compressed = NULL;
    FILE *decompressed = NULL;

    compressed = fopen("compressed", "r");
    decompressed = fopen("decompressed.txt", "w");

    decompress(compressed,decompressed);

    fclose(compressed);
    fclose(decompressed);
    return 0;
}