
#include "fpgacl_memory.h"

void *ptr;
unsigned page_offset;
unsigned page_size;

struct read_write_data_command_struct {
    void*    user_buffer_virtual_address;
    void*    kernel_buffer_physical_address;
    u32      size;
};
typedef struct read_write_data_command_struct read_write_data_command_type;


int file_desc_memalloc;

void fpgacl_open() {

	file_desc_memalloc = open(DEVICE_NAME_MEMALLOC, O_RDWR);
	if (file_desc_memalloc < 0) {
		printf("Can't open device file :%s\n", DEVICE_NAME_MEMALLOC);
		exit(-1);
	}

	page_size=sysconf(_SC_PAGESIZE);

}



long int fpgacl_malloc(unsigned long int size) {

	long int physical_address;

	physical_address = ioctl ( file_desc_memalloc, FPGACL_MEMALLOC, size);
	printf("fpgacl_malloc: value = %d, address = 0x%X\n", size, (u32)physical_address);
	return physical_address;
}

void fpgacl_free(unsigned long int physical_address) {

	ioctl ( file_desc_memalloc, FPGACL_MEMFREE, physical_address);
}



long int fpgacl_memwrite(void *src, u32 *dst, unsigned long int size) {

	unsigned long int i = 0;
	u32 src_add = (u32)src;
	u32 physical_address = (u32)dst;
	read_write_data_command_type* rd_command = (read_write_data_command_type*)malloc(sizeof(read_write_data_command_type));
	rd_command->user_buffer_virtual_address    = src;
	rd_command->kernel_buffer_physical_address = dst;
	rd_command->size = size;

	write(file_desc_memalloc, rd_command, 0);


/*
	u32 src_add = (u32)src;
	u32 physical_address = (u32)dst;

	getVirtualAddress(physical_address, size);
	memcpy((void *)(ptr + page_offset), (void *)src_add, size);
*/
}

long int fpgacl_memread(void *dst, u32 *src, unsigned long int size) {


	read_write_data_command_type* rd_command = (read_write_data_command_type*)malloc(sizeof(read_write_data_command_type));
	rd_command->user_buffer_virtual_address    = dst;
	rd_command->kernel_buffer_physical_address = src;
	rd_command->size = size;

	read(file_desc_memalloc, rd_command, 0);
/*
	u32 dst_add = (u32)dst;
	u32 physical_address = (u32)src;

	getVirtualAddress(physical_address, size);
	memcpy((void *)dst_add, (void *)(ptr + page_offset), size);
*/

}

u32 getVirtualAddress(u32 physical_address, u32 size) {

	int fd;
	unsigned page_addr;

	void *ptr_sta, *ptr_ddr;


	/* Open /dev/mem file */
	fd = open ("/dev/mem", O_RDWR);
	if (fd < 1) {
		perror("error 1\n");
		return -1;
	}


	page_addr = (physical_address & (~(page_size-1)));
	page_offset = physical_address - page_addr;
	ptr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, page_addr);

	close(fd);

	return 0;
}


void fpgacl_close() {

	close(file_desc_memalloc);

}
