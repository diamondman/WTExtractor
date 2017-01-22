CFLAGS=-std=gnu11
CFILES=multifh.c dataaccessors.c
WTCFILES=$(CFILES) wtextract_cli_main.c wld3_extract.c
PWTCFILES=$(CFILES) pwtdecode_cli_main.c pwt_decode.c
LDFLAGS=-luuid -lmspack -lmagic
WTBIN=./build/wtextract
PWTBIN=./build/pwtdecode

all: wtextract pwtdecode

build_mkdir:
	@mkdir -p build

wtextract: build_mkdir
	gcc $(CFLAGS) $(WTCFILES) $(LDFLAGS) -o $(WTBIN)

pwtdecode: build_mkdir
	gcc $(CFLAGS) $(PWTCFILES) -lm $(LDFLAGS) -o $(PWTBIN)

wtextract_memcheck: build_mkdir
	gcc $(CFLAGS) -g $(WTCFILES) $(LDFLAGS) -o $(WTBIN)
	valgrind --leak-check=yes $(WTBIN) ../sample_files/2cubes.wt

pwtdecode_memcheck: build_mkdir
	gcc $(CFLAGS) -g $(PWTCFILES) -lm $(LDFLAGS) -o $(PWTBIN)
	valgrind --leak-check=yes $(PWTBIN) ../sample_files/anim2cube.pwt
