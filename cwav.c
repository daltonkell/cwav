
#include <stdio.h>
#include <stdlib.h>
#include "cwav.h"

/* Define read_header */
void read_header(FILE * fp, HEADER * header)
{
    int nread = 0;

    // ckID "RIFF"
    nread = fread(header->ckID, sizeof(header->ckID), 1, fp);

    // overall size
    nread = fread(&header->overall_size, sizeof(header->overall_size), 1, fp);

    // WAVE chunks next, length n
    nread = fread(header->WAVE, sizeof(header->WAVE), 1, fp);
}

/* Define print_header */
void print_header(HEADER * header_ptr)
{
    printf("---------- RIFF HEADER ----------\n");
    for (int i=0; i<4; ++i)
    {
        printf("%c", header_ptr->ckID[i]);
    }
    printf("\n");
    printf("overall size: %i\n", header_ptr->overall_size);
    printf("WAVE ID: ");
    for (int i=0; i<4; ++i)
    {
        printf("%c", header_ptr->WAVE[i]);
    }
    printf("\n");
    printf("---------------------------------\n");
    
}

int main()
{

    FILE * fp = fopen(
        "Ensoniq-ESQ-1-Brass-Ensemble-C4.wav",
        "rb"
    );

    if (fp==NULL)
    {
        printf("File couldn't be opened\n");
        return -1;
    }

    fseek(fp, 0, SEEK_SET);

    /* Header fields */
    HEADER * header_ptr = malloc(sizeof(HEADER)); // why can't allocate on stack?
    read_header(fp, header_ptr);

    // display header
    print_header(header_ptr);

    int nread = 0;
    char chunk_id[4]; // "fmt " includes \0
    nread = fread(chunk_id, sizeof(chunk_id), 1, fp);
    printf("Next chunk_id: %s\n", chunk_id);
    
    // memory management
    free(header_ptr);
    fclose(fp);

    return 0;
}
