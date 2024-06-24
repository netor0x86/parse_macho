/**
 * Created by Netor0x86 on 2024/6/20.
 */

#ifndef CSTUDY_MACHO_H
#define CSTUDY_MACHO_H
#include <mach-o/loader.h>
#include <mach/machine.h>
#include <mach-o/nlist.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <capstone/capstone.h>

/** header 的 filetype 的说明 */
struct header_file_type_info
{
    /* file_type 的类型 */
    uint32_t file_type;
    /* file_type 的名称 */
    char *p_file_type_name;
    /* file_type 的描述 */
    char *p_desc;
};

extern struct header_file_type_info arr_st_header_file_type[];

/** header 的 flag 的说明 */
struct header_flag_info
{
    /* flag 的类型 */
    uint32_t flag;
    /* flag 的名称 */
    char *p_flag_name;
    /* flag 的描述 */
    char *p_desc;
};

extern struct header_flag_info arr_st_header_flag_info[];
int get_header_flag_info_size();

/**
 * 下面是关于 load_command 的处理
 */

/** 声明一个结构体，后面进行定义 */
struct lc_info;

struct load_command_info
{
    uint64_t offset;
    struct load_command st_load_command;
};

/** 各种类型 load_command 的处理函数 */
void parse_segment_command_64(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);

void parse_lc_symtab(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
void parse_lc_dysymtab(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
/** LC_ID_DYLINKER LC_LOAD_DYLINKER LC_DYLD_ENVIRONMENT */
void parse_lc_id_dylinker(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
void parse_lc_uuid(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
void parse_lc_build_version(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
void parse_lc_source_version(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
void parse_lc_main(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
/** LC_ID_DYLIB LC_LOAD_DYLIB LC_LOAD_WEAK_DYLIB LC_REEXPORT_DYLIB */
void parse_lc_id_dylib(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
/**
 * LC_CODE_SIGNATURE LC_SEGMENT_SPLIT_INFO
 * LC_FUNCTION_STARTS LC_DATA_IN_CODE
 * LC_DYLIB_CODE_SIGN_DRS LC_ATOM_INFO
 * LC_LINKER_OPTIMIZATION_HINT LC_DYLD_EXPORTS_TRIE
 * LC_DYLD_CHAINED_FIXUPS
 */
void parse_lc_code_signature(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
/**
 * LC_IDFVMLIB LC_LOADFVMLIB
 */
void parse_lc_idfvmlib(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
/**
 * LC_DYLD_INFO LC_DYLD_INFO_ONLY
 */
void parse_lc_dyld_info(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);
/**
 * LC_VERSION_MIN_MACOSX LC_VERSION_MIN_IPHONEOS LC_VERSION_MIN_WATCHOS LC_VERSION_MIN_TVOS
 */
void parse_lc_version_min_macosx(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info);


/** 定义函数指针，应用指向各个 load_command 处理函数 */
typedef void (*load_command_parse_proc)(FILE *, struct load_command_info *, struct lc_info);

/** load_command 的信息 */
struct lc_info
{
    /* load_command 类型 */
    uint32_t lc;
    /* Load_command 名称 */
    char *p_lc_name;
    /* load_command 描述 */
    char *p_desc;
    /* load_command 对应的处理函数 */
    load_command_parse_proc p_func_addr;
};

extern struct lc_info arr_st_lc_info[];
int get_arr_st_lc_info_size();

#endif //CSTUDY_MACHO_H
