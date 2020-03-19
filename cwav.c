/* Read a .wav file
 * Spec:
 *   www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 *   www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Docs/riffmci.pdf
 *   soundfile.sapp.org/doc/WaveFormat
 * Kind of taking from this (esp. bit shift):
 *   www.truelogic.org/wordpress/2015/09/04/parsing-a-wav-file-in-c/ thanks, amit
 * File:
 *   https://freewavesamples.com/ensoniq-esq-1-brass-ensemble-c4
 */

#include <stdio.h>
#include <stdlib.h>
#include "cwav.h"

struct HEADER * read_header(FILE * fp, HEADER * header)
{
    int nread = 0;

    // ckID "RIFF"
    nread = fread(header->ckID, sizeof(header->ckID), 1, fp);
    for (int i=0; i<4; ++i)
    {
        printf("%c", header->ckID[i]);
    }
    printf("\n");

    // overall size
    nread = fread(&header->overall_size, sizeof(header->overall_size), 1, fp);
    printf("overall size: %i\n", header->overall_size);

    // WAVE chunks next, length n
    nread = fread(header->WAVE, sizeof(header->WAVE), 1, fp);
    printf("WAVE ID: ");
    for (int i=0; i<4; ++i)
    {
        printf("%c", header->WAVE[i]);
    }
    printf("\n");
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

    printf("Size of header: %li\n", sizeof(header_ptr));

    int nread = 0;

    char chunk_id[4]; // "fmt " includes \0
    nread = fread(chunk_id, sizeof(chunk_id), 1, fp);
    printf("Next chunk_id: %s\n", chunk_id);
    
    // memory management
    free(header_ptr);
    fclose(fp);

    return 0;
}
