/* An implementation of the mspack_system interface which can access many
 * things:
 * - regular disk files
 * - already opened stdio FILE* file pointers
 * - open file descriptors
 * - blocks of memory
 *
 * Heavily based on:
 * https://github.com/kyz/libmspack/blob/master/libmspack/test/multifh.c
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <mspack.h>

/* definitions */

#define MTYPE_DISKFILE  (0x01)
#define MTYPE_STDIOFH   (0x02)
#define MTYPE_FILEDESC  (0x03)
#define MTYPE_MEMORY    (0x04)

struct m_filename {
  unsigned char type;   /* one of MTYPE_DISKFILE, STDIOFH, FILEDESC or MEMORY */
  const char *filename; /* the user-friendly printable filename (may be NULL) */
  union {
    const char *diskfile; /* char *filename      for MTYPE_DISKFILE */
    FILE *stdiofh;        /* FILE *existing_fh   for MTYPE_STDIOFH */
    int filedesc;         /* int file_descriptor for MTYPE_FILEDESC */
    struct {
      unsigned char *data;
      size_t length;
    } memory;
  } x;
};

struct m_file {
  struct m_filename *file; /* pointer back to the m_filename data */
  union {
    FILE *fh;        /* only used in DISKFILE, STDIOFH and FILEDESC types */
    size_t position; /* only used in MEMORY types */
  } x;
};

/* ------------------------------------------------------------------------ */
/* mspack_system implementation */

static void *m_alloc(struct mspack_system *self, size_t bytes) {
  return malloc(bytes);
}

static void m_free(void *buffer) {
  free(buffer);
}

static void m_copy(void *src, void *dest, size_t bytes) {
  memcpy(dest, src, bytes);
}

/* A message printer that prints to stderr */
static void m_msg(struct m_file *file, const char *format, ...) {
  va_list ap;
  if (file && file->file && file->file->filename) {
    fprintf(stderr, "%s: ", file->file->filename);
  }
  va_start(ap, format);
  vfprintf(stderr, format, ap);
  va_end(ap);
  fputc((int) '\n', stderr);
  fflush(stderr);
}


static struct m_file *m_open_mem(struct mspack_system *self,
				 struct m_filename *fn, int mode)
{
  struct m_file *fh;

  /* validate arguments of the filename */
  if (!fn->x.memory.data)   return NULL;
  if (!fn->x.memory.length) return NULL;

  if ((fh = (struct m_file *) m_alloc(self, sizeof(struct m_file)))) {
    fh->x.position = (mode == MSPACK_SYS_OPEN_APPEND) ?
      fn->x.memory.length : 0;
    fh->file = fn;
  }
  return fh;
}

static struct m_file *m_open_file(struct mspack_system *self,
				  struct m_filename *fn, int mode)
{
  struct m_file *fh;
  const char *fmode;
  int fd;

  switch (mode) {
  case MSPACK_SYS_OPEN_READ:   fmode = "rb";  break;
  case MSPACK_SYS_OPEN_WRITE:  fmode = "wb";  break;
  case MSPACK_SYS_OPEN_UPDATE: fmode = "r+b"; break;
  case MSPACK_SYS_OPEN_APPEND: fmode = "ab";  break;
  default: return NULL;
  }

  /* validate the arguments in the provided filename */
  switch (fn->type) {
  case MTYPE_DISKFILE: if (!fn->x.diskfile)    return NULL; break;
  case MTYPE_STDIOFH:  if (!fn->x.stdiofh)     return NULL; break;
  case MTYPE_FILEDESC: if (fn->x.filedesc < 0) return NULL; break;
  }

  /* allocate memory for the file handle */
  if (!(fh = (struct m_file *) m_alloc(self, sizeof(struct m_file)))) return NULL;

  /* open or duplicate the filehandle */
  switch (fn->type) {
  case MTYPE_DISKFILE:
    fh->x.fh = fopen(fn->x.diskfile, fmode);
    break;

  case MTYPE_STDIOFH:
    fd = fileno(fn->x.stdiofh);
    fh->x.fh = (fd >= 0) ? fdopen(fd, fmode) : NULL;
    break;

  case MTYPE_FILEDESC:
    fh->x.fh = fdopen(fn->x.filedesc, fmode);
    break;
  }

  /* validate the new stdio filehandle */
  if (fh->x.fh) {
    fh->file = fn;
  }
  else {
    free(fh);
    fh = NULL;
  }

  return fh;
}

static struct m_file *m_open(struct mspack_system *self,
			     struct m_filename *fn, int mode)
{
  if (!self || !fn) return NULL;

  switch (fn->type) {
  case MTYPE_DISKFILE:
  case MTYPE_STDIOFH:
  case MTYPE_FILEDESC:
    return m_open_file(self, fn, mode);

  case MTYPE_MEMORY:
    return m_open_mem(self, fn, mode);
  }
  return NULL;
}

static void m_close(struct m_file *fh) {
  if (!fh || !fh->file) return;
  if (fh->file->type != MTYPE_MEMORY) fclose(fh->x.fh);
  m_free(fh);
}


static int m_read(struct m_file *fh, void *buffer, int bytes) {
  if (!fh || !fh->file || !buffer || bytes < 0) return -1;

  if (fh->file->type == MTYPE_MEMORY) {
    int count = fh->file->x.memory.length - fh->x.position;
    if (count > bytes) count = bytes;
    if (count > 0) {
      m_copy(&fh->file->x.memory.data[fh->x.position], buffer, (size_t) count);
    }
    fh->x.position += count;
    return count;
  }
  else {
    size_t count = fread(buffer, 1, (size_t) bytes, fh->x.fh);
    if (!ferror(fh->x.fh)) return (int) count;
  }
  return -1;
}


static int m_write(struct m_file *fh, void *buffer, int bytes) {
  if (!fh || !fh->file || !buffer || bytes < 0) return -1;

  if (fh->file->type == MTYPE_MEMORY) {
    int count = fh->file->x.memory.length - fh->x.position;
    if (count > bytes) count = bytes;
    if (count > 0) {
      m_copy(buffer, &fh->file->x.memory.data[fh->x.position], (size_t) count);
    }
    fh->x.position += count;
    return count;
  }
  else {
    size_t count = fwrite(buffer, 1, (size_t) bytes, fh->x.fh);
    if (!ferror(fh->x.fh)) return (int) count;
  }
  return -1;
}


static int m_seek(struct m_file *fh, off_t offset, int mode) {
  if (!fh || !fh->file) return 1;

  if (fh->file->type == MTYPE_MEMORY) {
    switch (mode) {
    case MSPACK_SYS_SEEK_START:
      break;
    case MSPACK_SYS_SEEK_CUR:
      offset += (off_t) fh->x.position;
      break;
    case MSPACK_SYS_SEEK_END:
      offset += (off_t) fh->file->x.memory.length;
      break;
    default:
      return 1;
    }

    if (offset < 0) return 1;
    if (offset > (off_t) fh->file->x.memory.length) return 1;
    fh->x.position = (size_t) offset;
    return 0;
  }

  /* file IO based method */
  switch (mode) {
  case MSPACK_SYS_SEEK_START: mode = SEEK_SET; break;
  case MSPACK_SYS_SEEK_CUR:   mode = SEEK_CUR; break;
  case MSPACK_SYS_SEEK_END:   mode = SEEK_END; break;
  default: return 1;
  }
#if HAVE_FSEEKO
  return fseeko(fh->x.fh, offset, mode);
#else
  return fseek(fh->x.fh, offset, mode);
#endif
}


static off_t m_tell(struct m_file *fh) {
  if (!fh || !fh->file) return -1;
  if (fh->file->type == MTYPE_MEMORY) {
    return (off_t) fh->x.position;
  }
#if HAVE_FSEEKO
  return (off_t) ftello(fh->x.fh);
#else
  return (off_t) ftell(fh->x.fh);
#endif
}


struct mspack_system multi_system = {
  (struct mspack_file * (*)(struct mspack_system *, const char *, int)) &m_open,
  (void (*)(struct mspack_file *)) &m_close,
  (int (*)(struct mspack_file *, void *, int)) &m_read,
  (int (*)(struct mspack_file *, void *, int)) &m_write,
  (int (*)(struct mspack_file *, off_t, int)) &m_seek,
  (off_t (*)(struct mspack_file *)) &m_tell,
  (void (*)(struct mspack_file *, const char *, ...))  &m_msg,
  &m_alloc,
  &m_free,
  &m_copy,
  NULL
};

/* ------------------------------------------------------------------------ */
/* constructors and destructor */

const char *create_filename(const char *filename) {
  struct m_filename *fn;

  if (!filename) return NULL; /* filename must not be null */

  if ((fn = (struct m_filename *) malloc(sizeof(struct m_filename)))) {
    fn->type = MTYPE_DISKFILE;
    fn->filename = filename; /* pretty-printable filename */
    fn->x.diskfile = filename;
  }
  return (const char *) fn;
}

const char *create_filename_from_handle(FILE *fh) {
  struct m_filename *fn;

  if (!fh) return NULL; /* file handle must not be null */

  if ((fn = (struct m_filename *) malloc(sizeof(struct m_filename)))) {
    fn->type = MTYPE_STDIOFH;
    fn->filename = NULL; /* pretty-printable filename */
    fn->x.stdiofh = fh;
  }
  return (const char *) fn;
}

const char *create_filename_from_descriptor(int fd) {
  struct m_filename *fn;

  if (fd < 0) return NULL; /* file descriptor must be valid */

  if ((fn = (struct m_filename *) malloc(sizeof(struct m_filename)))) {
    fn->type = MTYPE_FILEDESC;
    fn->filename = NULL; /* pretty-printable filename */
    fn->x.filedesc = fd;
  }
  return (const char *) fn;
}

const char *create_filename_from_memory(void *data, size_t length) {
  struct m_filename *fn;

  if (!data) return NULL; /* data pointer must not be NULL */
  if (length == 0) return NULL; /* length must not be zero */

  if ((fn = (struct m_filename *) malloc(sizeof(struct m_filename)))) {
    fn->type = MTYPE_MEMORY;
    fn->filename = NULL; /* pretty-printable filename */
    fn->x.memory.data   = (unsigned char *) data;
    fn->x.memory.length = length;
  }
  return (const char *) fn;
}

void set_filename_printable_name(const char *filename, const char *name) {
  struct m_filename *fn = (struct m_filename *) filename;
  if (!fn) return;
  /* very basic validation of structure */
  if ((fn->type < MTYPE_DISKFILE) || (fn->type > MTYPE_MEMORY)) return;
  fn->filename = name;
}

void free_filename(const char *filename) {
  free((void *) filename);
}
