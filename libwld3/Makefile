CFLAGS=-std=gnu11
CFILES=main.c wld3_extract.c multifh.c
LDFLAGS=-luuid -lmspack

all:
	@mkdir -p build
	gcc $(CFLAGS) $(CFILES) $(LDFLAGS) -o build/wttext

memcheck:
	@mkdir -p build
	gcc $(CFLAGS) -g $(CFILES) $(LDFLAGS) -o build/wttext
	valgrind --leak-check=yes ./build/wttext ../sample_files/2cubes.wt
