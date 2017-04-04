
#ifndef VOEAPI
#define VOEAPI
 
struct mount_point
{
    void *fs_address;
    struct file (*open_file)(void*,char*);
}; 

struct multiboot
{
   int flags;
   int mem_lower;
   int mem_upper;
   int boot_device;
   int cmdline;
   int mods_count;
   int mods_addr;
   int num;
   int size;
   int addr;
   int shndx;
   int mmap_length;
   int mmap_addr;
   int drives_length;
   int drives_addr;
   int config_table;
   int boot_loader_name;
   int apm_table;
   int vbe_control_info;
   int vbe_mode_info;
   int vbe_mode;
   int vbe_interface_seg;
   int vbe_interface_off;
   int vbe_interface_len;
}  __attribute__((packed)); 

struct kernel_structure
{
    struct mount_point mount_points[16];
    struct multiboot *multiboot;
    void* ramdisk_address;
};

struct fs_api{
	int (*get_size)(void*);
	char (*read_byte)(void*,int);
};

struct file{
	void *file_address;
	struct fs_api *fs_api_address;
};


struct voe_api{
	short (*malloc)(short);
	void (*clear_memory)(short,short);
	struct kernel_structure *ks;
	void (*putc)(char);
	struct file (*file_open)(struct mount_point,char*);
	char (*isExist)(struct file);
	int (*file_get_size)(struct file);
	char (*file_read_byte)(struct file,int);
	unsigned int (*load_VOE)(struct file);
	void (*voe_jump)(unsigned int ,unsigned int ,unsigned int ,int);
};

struct voe_descriptor{
	char cmdline[100];
	struct voe_api *api;
	void *mailbox;
	void *cache;
	char reversed[3984];
}; 

#endif
