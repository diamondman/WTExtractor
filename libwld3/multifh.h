struct mspack_system multi_system;

const char *create_filename(const char *filename);
const char *create_filename_from_handle(FILE *fh);
const char *create_filename_from_descriptor(int fd);
const char *create_filename_from_memory(void *data, size_t length);

void set_filename_printable_name(const char *filename, const char *name);

void free_filename(const char *filename);
