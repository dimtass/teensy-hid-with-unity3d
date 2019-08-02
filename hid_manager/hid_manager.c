#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "hid.h"

#define HID_RAW_BUFF_SIZE 64

int main(int argc, char* argv[])
{
	int i, r, num, fd;
	char * membuf;
    const char *filepath = "/tmp/hid-shared-buffer";
	int debug_enabled = 0;

	if (argc > 1) {
		debug_enabled = atoi(argv[1]);
		if (debug_enabled)
			printf("Denug mode enabled...\n");
	}
	else {
		printf("Debug mode disabled...\n");
	}

	if ((fd = open(filepath, O_CREAT|O_RDWR, (mode_t)00700)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
	printf("Open shared memfile\n");

    membuf = mmap(NULL, HID_RAW_BUFF_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    if (membuf == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
	memset(membuf, 0, HID_RAW_BUFF_SIZE);

	// C-based example is 16C0:0480:FFAB:0200
	r = rawhid_open(1, 0x16C0, 0x0480, 0xFFAB, 0x0200);
	if (r <= 0) {
		// Arduino-based example is 16C0:0486:FFAB:0200
		r = rawhid_open(1, 0x16C0, 0x0486, 0xFFAB, 0x0200);
		if (r <= 0) {
			printf("no rawhid device found\n");
			return -1;
		}
	}
	printf("found rawhid device\n");

	while (1) {
		// check if any Raw HID packet has arrived
		num = rawhid_recv(0, membuf, HID_RAW_BUFF_SIZE, 220);
		if (num < 0) {
			printf("\nerror reading, device went offline\n");
			rawhid_close(0);
			return 0;
		}
		if ((num > 0) && debug_enabled) {

			printf("\nrecv %d bytes:\n", num);
			for (i=0; i<num; i++) {
				printf("%02X ", membuf[i] & 255);
				if (i % 16 == 15 && i < num-1) printf("\n");
			}
			printf("\n");
		}
		if (msync(membuf, HID_RAW_BUFF_SIZE, MS_SYNC) == -1) {
			perror("Error sync to disk");
		}
	}

    if (munmap(membuf, HID_RAW_BUFF_SIZE) == -1) {
        close(fd);
        perror("Error un-mmapping");
        exit(EXIT_FAILURE);
    }

    close(fd);
}
