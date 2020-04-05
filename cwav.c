
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

/* Define read_chunk */
void read_chunk(FILE * fp, CHUNK * chunk)
{

    int nread = 0;
    nread = fread(chunk->chunk_id, sizeof(chunk->chunk_id), 1, fp);
    nread = fread(&chunk->chunk_size, sizeof(chunk->chunk_size), 1, fp);
    nread = fread(&chunk->fmt_code, sizeof(chunk->fmt_code), 1, fp);
    nread = fread(&chunk->n_channels, sizeof(chunk->n_channels), 1, fp);
    nread = fread(&chunk->samples_per_sec, sizeof(chunk->samples_per_sec), 1, fp);
    nread = fread(&chunk->avg_bytes_per_sec, sizeof(chunk->avg_bytes_per_sec), 1, fp);
    nread = fread(&chunk->block_align, sizeof(chunk->block_align), 1, fp);
    nread = fread(&chunk->bits_per_sample, sizeof(chunk->bits_per_sample), 1, fp);

    /* if PCM format, skip these last 4 fields */
    if (chunk->fmt_code!=1)
    {
        nread = fread(&chunk->cb_size, sizeof(chunk->cb_size), 1, fp);
        nread = fread(&chunk->valid_bits_per_sample, sizeof(chunk->valid_bits_per_sample), 1, fp);
        nread = fread(&chunk->channel_mask, sizeof(chunk->channel_mask), 1, fp);
        nread = fread(chunk->sub_format, sizeof(chunk->sub_format), 1, fp);
    }
}

/* Define print_chunk */
void print_chunk(CHUNK * chunk)
{
    for (int i=0; i<4; ++i)
    {
        printf("%c", chunk->chunk_id[i]);
    }
    printf("\n");

    printf("Size of chunk (bytes): %i\n", chunk->chunk_size);
    printf("Format code: %#x\n", chunk->fmt_code);
    printf("Number interleaved channels: %d\n", chunk->n_channels);
    printf("Sampling rate (blocks/sec): %d\n", chunk->samples_per_sec);
    printf("Data rate (avg bytes/sec): %d\n", chunk->avg_bytes_per_sec);
    printf("Data block size (bytes): %d\n", chunk->block_align);
    printf("Bits per sample: %d\n", chunk->bits_per_sample);

    if (chunk->fmt_code!=1)
    {
        printf("Extension size (0 or 22?): %#x\n", chunk->cb_size);
        printf("Valid bits per sample: %d\n", chunk->valid_bits_per_sample);
        printf("Speaker position mask: %d\n", chunk->channel_mask);

        printf("Sub format: ");
        for (int i=0; i<16; ++i)
        {
            printf("%c", chunk->sub_format[i]);
        }
        printf("\n");
    }

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

    // for now, read only a single chunk
    CHUNK * chunk_ptr = malloc(sizeof(CHUNK));
    read_chunk(fp, chunk_ptr);

    // displau chunk
    print_chunk(chunk_ptr);
    
    // if PCM format, proceed to data chunk

    // memory management
    free(header_ptr);
    free(chunk_ptr);
    fclose(fp);

    return 0;
}
