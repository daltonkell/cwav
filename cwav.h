#include <stdio.h>

typedef struct
{
    char ckID[4];              // chunk ID "RIFF"
    unsigned int overall_size; // size (4+n)
    unsigned char WAVE[4];     // "WAVE"
} HEADER;

typedef struct
{
    // TODO add fields
    char chunk_id[4]; // "fmt "
} FMT_CHUNK;


/* Read the header information from a .wav file into a HEADER struct
 *
 * Args:
 *   FILE * fp      : pointer to open .wav file
 *   HEADER * header: pointer to HEADER struct
 *
 * Returns:
 *   void
 */
void read_header(FILE * fp, HEADER * header);

/* Print the contents of a HEADER struct
 *
 * Args:
 *   HEADER * hp: pointer to HEADER struct
 *
 * Returns:
 *   void
 */
void print_header(HEADER * header_ptr);
