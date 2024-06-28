#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <glib.h>
#include "macho/macho64.h"

#define SAFE_FREE(point) {if (point) {free(point); point = NULL;}}

#define FILE_NAME ""
char *p_file_name = FILE_NAME;


long get_file_size(const char *filename)
{
    struct stat st = {0};

    if (lstat(filename, &st) == 0)
    {
        return st.st_size;
    }

    return -1;
}

void parse_load_command(FILE *p_file, GList *list)
{
    for (GList *node = g_list_first(list); node != NULL; node = g_list_next(node))
    {
        printf("-----------------------------------------------\r\n");
        struct load_command_info *lc_info = (struct load_command_info*)node->data;
        printf("addr: %llx -> cmd: %u(%x), cmdsize: %u(%x) \r\n",
               lc_info->offset,
               lc_info->st_load_command.cmd,
               lc_info->st_load_command.cmd,
               lc_info->st_load_command.cmdsize,
               lc_info->st_load_command.cmdsize);

        int j = 0;

        for (; j < get_arr_st_lc_info_size(); j ++)
        {
            if (lc_info->st_load_command.cmd == arr_st_lc_info[j].lc)
            {
                arr_st_lc_info[j].p_func_addr(p_file, lc_info, arr_st_lc_info[j]);
                break;
            }
        }

        if (get_arr_st_lc_info_size() == j)
        {
            printf("type: unk...\r\n");
        }
    }
}

void parse_magic64(uint64_t offset, uint32_t endian)
{
    FILE *p_file = fopen(p_file_name, "rb");

    if (p_file == NULL)
    {
        printf("文件打开失败");
        return;
    }

    fseeko(p_file, (off_t)offset, SEEK_SET);

    struct mach_header_64 st_mach_header_64 = {0};
    struct load_command *p_st_load_command = NULL;

    printf("file name: %s\r\n", p_file_name);
    long l_file_size = get_file_size(p_file_name);
    printf("file size:%ld\r\n", l_file_size);

    fread(&st_mach_header_64, sizeof(struct mach_header_64), 1, p_file);

    printf("mach_header_64 size: %lx \r\n", sizeof(struct mach_header_64));
    printf("magic: %x \r\n", st_mach_header_64.magic);
    printf("cpu_type_t: %x \r\n", st_mach_header_64.cputype);
    for (int i = 0; i < get_header_cpu_type_info_size(); i ++)
    {
        if (st_mach_header_64.cputype == arr_st_header_cpu_type[i].cpu_type)
        {
            printf("cpu_type: %s\r\n", arr_st_header_cpu_type[i].p_cpu_type_name);
        }
    }
    printf("cpu_subtype_t: %x \r\n", st_mach_header_64.cpusubtype);

    printf("filetype: %x, %s \r\n", st_mach_header_64.filetype, arr_st_header_file_type[st_mach_header_64.filetype].p_file_type_name);
    printf("ncmds: %x \r\n", st_mach_header_64.ncmds);
    printf("sizeofcmds: %x \r\n", st_mach_header_64.sizeofcmds);
    printf("flags: %x, header_flag_info names: \r\n", st_mach_header_64.flags);
    for (int i = 0; i < get_header_flag_info_size(); i ++)
    {
        if (arr_st_header_flag_info[i].flag & st_mach_header_64.flags)
        {
            printf("%s(%x) ", arr_st_header_flag_info[i].p_flag_name, arr_st_header_flag_info[i].flag);
        }
    }
    printf("\r\n");
    printf("reserved: %x \r\n", st_mach_header_64.reserved);

    p_st_load_command = (struct load_command *)malloc(sizeof(struct load_command) * st_mach_header_64.ncmds);
    if (p_st_load_command == NULL)
    {
        return;
    }

    printf("--------------------\r\n");

    GList *list = NULL;

    for (int i = 0; i < st_mach_header_64.ncmds; i ++)
    {
        long addr = ftell(p_file);
        fread(p_st_load_command + i, sizeof(struct load_command), 1, p_file);

        struct load_command_info *lc_info = (struct load_command_info*)malloc(sizeof(struct load_command_info));
        lc_info->offset = addr;
        lc_info->st_load_command.cmd = p_st_load_command[i].cmd;
        lc_info->st_load_command.cmdsize = p_st_load_command[i].cmdsize;
        list = g_list_append(list, lc_info);

        fseeko(p_file, (off_t)(p_st_load_command[i].cmdsize - sizeof(struct load_command)), SEEK_CUR);
    }

    parse_load_command(p_file, list);

    g_list_free_full(list, g_free);

    SAFE_FREE(p_st_load_command);

    fclose(p_file);
    p_file = NULL;
}

/**
 * 获得文件的 magic 类型
 *
 * @return 返回 -1 说明打开失败，正常返回 magic 类型
 */
uint32_t get_file_magic(uint32_t offset)
{
    FILE *p_file = NULL;

    p_file = fopen(p_file_name, "rb");

    if (p_file == NULL)
    {
        printf("文件打开失败");
        return -1;
    }

    fseeko(p_file, offset, SEEK_SET);
    uint32_t magic = 0;
    fread(&magic, sizeof(uint32_t), 1, p_file);

    if (p_file)
    {
        fclose(p_file);
        p_file = NULL;
    }

    return magic;
}

void __attribute__((constructor)) init (void)
{
    printf("\033[41m\033[37m\033[1m 欢迎使用 Parse Mach-O 命令行工具 code by Netor0x86 \033[0m\r\n");
}

void parse_fat_header(uint32_t endian)
{
    FILE *p_file = NULL;

    p_file = fopen(p_file_name, "rb");

    if (p_file == NULL)
    {
        printf("文件打开失败");
        return;
    }

    struct fat_header fat_header = {0};
    fread(&fat_header, sizeof(struct fat_header), 1, p_file);

    uint32_t nfat_arch = big_endian_to_little_endian_uint32(fat_header.nfat_arch, endian);

    struct fat_arch *p_fat_arch = (struct fat_arch *)malloc(
            sizeof(struct fat_arch) * nfat_arch);
    if (p_fat_arch == NULL)
    {
        return ;
    }

    fread(p_fat_arch, sizeof(struct fat_arch), nfat_arch, p_file);

    printf("nfat_arch number is : %d \r\n", nfat_arch);
    for (int i = 0; i < nfat_arch; i ++)
    {
        printf("cputype: %d(%x) cpusubtype: %d(%x)"
               "offset: %d(%x) size: %d(%x)"
               "align: %d(%x) \r\n",
               big_endian_to_little_endian_uint32(p_fat_arch[i].cputype, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].cputype, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].cpusubtype, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].cpusubtype, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].offset, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].offset, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].size, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].size, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].align, endian),
               big_endian_to_little_endian_uint32(p_fat_arch[i].align, endian));
    }

    for (int i = 0; i < nfat_arch; i ++)
    {
        uint32_t magic = get_file_magic(big_endian_to_little_endian_uint32(p_fat_arch[i].offset, endian));
        switch (magic)
        {
            case MH_MAGIC:
                printf("MH_MAGIC\r\n");
                break;
            case MH_CIGAM:
                printf("MH_CIGAM\r\n");
                break;
            case MH_MAGIC_64:
                printf("MH_MAGIC_64\r\n");
                parse_magic64(big_endian_to_little_endian_uint32(p_fat_arch[i].offset, endian), LITTLE_ENDIAN);
                break;
            case MH_CIGAM_64:
                printf("MH_CIGAM_64\r\n");
                parse_magic64(big_endian_to_little_endian_uint32(p_fat_arch[i].offset, endian), BIG_ENDIAN);
                break;
        }
    }

    free(p_fat_arch);
    p_fat_arch = NULL;

    fclose(p_file);
    p_file = NULL;
}

void parse_fat_header_64(uint32_t endian)
{
    FILE *p_file = NULL;

    p_file = fopen(p_file_name, "rb");

    if (p_file == NULL)
    {
        printf("文件打开失败");
        return;
    }

    struct fat_header fat_header = {0};
    fread(&fat_header, sizeof(struct fat_header), 1, p_file);

    struct fat_arch_64 *p_fat_arch_64 = (struct fat_arch_64 *)malloc(sizeof(struct fat_arch_64) * fat_header.nfat_arch);
    if (p_fat_arch_64 == NULL)
    {
        return ;
    }

    fread(p_fat_arch_64, sizeof(struct fat_arch_64), fat_header.nfat_arch, p_file);
    for (int i = 0; i < fat_header.nfat_arch; i ++)
    {
        printf("cputype: %d(%x) cpusubtype: %d(%x)"
               "offset: %llu(%llx) size: %llu(%llx)"
               "align: %d(%x) reserved: %d(%x) \r\n",
               p_fat_arch_64[i].cputype, p_fat_arch_64[i].cputype,
               p_fat_arch_64[i].cpusubtype, p_fat_arch_64[i].cpusubtype,
               p_fat_arch_64[i].offset, p_fat_arch_64[i].offset,
               p_fat_arch_64[i].size, p_fat_arch_64[i].size,
               p_fat_arch_64[i].align, p_fat_arch_64[i].align,
               p_fat_arch_64[i].reserved, p_fat_arch_64[i].reserved);
    }

    free(p_fat_arch_64);
    p_fat_arch_64 = NULL;

    fclose(p_file);
    p_file = NULL;
}

void parse_magic(uint64_t offset, uint32_t endian)
{

}

int main(int argc, char *argv[])
{
    /* 解析命令行传来的文件 */
    if (argc == 2)
    {
        p_file_name = argv[1];
    }

    uint32_t magic = get_file_magic(0);

    /* 判断文件类型 */
    switch (magic)
    {
        case FAT_MAGIC:
            parse_fat_header(LITTLE_ENDIAN);
            break;
        case FAT_CIGAM:
            parse_fat_header(BIG_ENDIAN);
            break;
        case FAT_MAGIC_64:
            parse_fat_header_64(LITTLE_ENDIAN);
            break;
        case FAT_CIGAM_64:
            parse_fat_header_64(BIG_ENDIAN);
            break;
        case MH_MAGIC:
            parse_magic(0, LITTLE_ENDIAN);
            break;
        case MH_CIGAM:
            parse_magic(0, BIG_ENDIAN);
            break;
        case MH_MAGIC_64:
            parse_magic64(0, LITTLE_ENDIAN);
            break;
        case MH_CIGAM_64:
            parse_magic64(0, BIG_ENDIAN);
            break;
            break;
        default:
            printf("不是 Mach-O 文件格式\r\n");
            return -1;
    }

    return 0;
}
