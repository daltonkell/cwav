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
