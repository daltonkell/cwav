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
    char chunk_id[4]; // "fmt "; NOTE ennd char is blank, NOT \0
    int chunk_size;   // 16, 18, 40
} CHUNK;


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

/* Read bytes from a .wav file for one chunk of a .wav file
 * into a CHUNK struct.
 *
 * Args:
 *   FILE * fp: pointer to open .wav file
 *   CHUNK * chunk: pointer to CHUNK struct
 *
 * Returns:
 *   void
 */
void read_chunk(FILE * fp, CHUNK * chunk);

/* Print chunk information */
void print_chunk(CHUNK * chunk);
