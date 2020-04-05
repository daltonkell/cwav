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
    char chunk_id[4]; // "fmt "; NOTE end char is blank, NOT \0
    int chunk_size;   // 16, 18, 40

    /* Standard format codes:
     *   0x0001 (WAVE_FORMAT_PCM)
     *   0x0003 (WAVE_FORMAT_IEEE_FLOAT)
     *   0x0006 (WAVE_FORMAT_ALAW)
     *   0x0007 (WAVE_FORMAT_MULAW)
     *   0xFFFE (WAVE_FORMAT_EXTENSIBLE) -> determined by SubFormat
     */
    short int fmt_code;

    short int n_channels;            // number of interleaved channels
    int samples_per_sec;             // sampling rate of blocks/second
    int avg_bytes_per_sec;           // data rate
    short int block_align;           // data block size in bytes
    short int bits_per_sample;       // bits per sample
    short int cb_size;               // size of extension (0 or 22)
    short int valid_bits_per_sample; // num valid bits
    int channel_mask;                // speaker position mask
    char sub_format[16];             // GUID, including data fmt code
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
