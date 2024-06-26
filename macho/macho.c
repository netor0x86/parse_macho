//
// Created by apple on 2024/6/20.
//
#include <strings.h>
#include "macho.h"

/** header 的 cputype 的说明 */
struct header_cpu_type_info arr_st_header_cpu_type[] =
{
    {CPU_TYPE_ANY, "CPU_TYPE_ANY", ""},

    {CPU_TYPE_VAX, "CPU_TYPE_VAX", ""},

    {CPU_TYPE_MC680x0, "CPU_TYPE_MC680x0", ""},
    {CPU_TYPE_X86, "CPU_TYPE_X86", ""},
    {CPU_TYPE_I386, "CPU_TYPE_I386", "compatibility"},
    {CPU_TYPE_X86_64, "CPU_TYPE_X86_64", ""},

    {CPU_TYPE_MC98000, "CPU_TYPE_MC98000", ""},
    {CPU_TYPE_HPPA, "CPU_TYPE_HPPA", ""},
    {CPU_TYPE_ARM, "", ""},
    {CPU_TYPE_ARM64, "CPU_TYPE_ARM64", ""},
    {CPU_TYPE_ARM64_32, "CPU_TYPE_ARM64_32", ""},
    {CPU_TYPE_MC88000, "CPU_TYPE_MC88000", ""},
    {CPU_TYPE_SPARC, "CPU_TYPE_SPARC", ""},
    {CPU_TYPE_I860, "CPU_TYPE_I860", ""},

    {CPU_TYPE_POWERPC, "CPU_TYPE_POWERPC", ""},
    {CPU_TYPE_POWERPC64, "CPU_TYPE_POWERPC64", ""},
};

int get_header_cpu_type_info_size()
{
    return sizeof(arr_st_header_cpu_type) / sizeof(struct header_flag_info);
}

/** header 的 cpusubtype 的说明 */
//struct header_cpu_sub_type_info arr_st_header_cpu_sub_type[] =
//{
//    {CPU_SUBTYPE_MASK, "CPU_SUBTYPE_MASK", "mask for feature flags"},
//    {CPU_SUBTYPE_LIB64, "CPU_SUBTYPE_LIB64", "64 bit libraries"},
//    {CPU_SUBTYPE_PTRAUTH_ABI, "CPU_SUBTYPE_PTRAUTH_ABI", "pointer authentication with versioned ABI"},
//
//    {CPU_SUBTYPE_ANY, "CPU_SUBTYPE_ANY", ""},
//
//    {CPU_SUBTYPE_MULTIPLE, "CPU_SUBTYPE_MULTIPLE", ""},
//    {CPU_SUBTYPE_LITTLE_ENDIAN, "CPU_SUBTYPE_LITTLE_ENDIAN", ""},
//    {CPU_SUBTYPE_BIG_ENDIAN, "CPU_SUBTYPE_BIG_ENDIAN", ""},
//
//    {CPU_SUBTYPE_VAX_ALL, "CPU_SUBTYPE_VAX_ALL", ""},
//    {CPU_SUBTYPE_VAX780, "CPU_SUBTYPE_VAX780", ""},
//    {CPU_SUBTYPE_VAX785, "CPU_SUBTYPE_VAX785", ""},
//    {CPU_SUBTYPE_VAX750, "CPU_SUBTYPE_VAX750", ""},
//    {CPU_SUBTYPE_VAX730, "CPU_SUBTYPE_VAX730", ""},
//    {CPU_SUBTYPE_UVAXI, "CPU_SUBTYPE_UVAXI", ""},
//    {CPU_SUBTYPE_UVAXII, "CPU_SUBTYPE_UVAXII", ""},
//    {CPU_SUBTYPE_VAX8200, "CPU_SUBTYPE_VAX8200", ""},
//    {CPU_SUBTYPE_VAX8500, "CPU_SUBTYPE_VAX8500", ""},
//    {CPU_SUBTYPE_VAX8600, "CPU_SUBTYPE_VAX8600", ""},
//    {CPU_SUBTYPE_VAX8650, "CPU_SUBTYPE_VAX8650", ""},
//    {CPU_SUBTYPE_VAX8800, "CPU_SUBTYPE_VAX8800", ""},
//    {CPU_SUBTYPE_UVAXIII, "CPU_SUBTYPE_UVAXIII", ""},
//
//    {CPU_SUBTYPE_MC680x0_ALL, "CPU_SUBTYPE_MC680x0_ALL", ""},
//    {CPU_SUBTYPE_MC68030, "CPU_SUBTYPE_MC68030", "compat"},
//    {CPU_SUBTYPE_MC68040, "CPU_SUBTYPE_MC68040", ""},
//    {CPU_SUBTYPE_MC68030_ONLY, "CPU_SUBTYPE_MC68030_ONLY", ""},
//
//    {CPU_SUBTYPE_I386_ALL, "CPU_SUBTYPE_I386_ALL", ""},
//    {CPU_SUBTYPE_386, "CPU_SUBTYPE_386", ""},
//    {CPU_SUBTYPE_486, "CPU_SUBTYPE_486", ""},
//    {CPU_SUBTYPE_486SX, "CPU_SUBTYPE_486SX", ""},
//    {CPU_SUBTYPE_586, "CPU_SUBTYPE_586", ""},
//    {CPU_SUBTYPE_PENT, "CPU_SUBTYPE_PENT", ""},
//    {CPU_SUBTYPE_PENTPRO, "CPU_SUBTYPE_PENTPRO", ""},
//    {CPU_SUBTYPE_PENTII_M3, "CPU_SUBTYPE_PENTII_M3", ""},
//    {CPU_SUBTYPE_PENTII_M5, "CPU_SUBTYPE_PENTII_M5", ""},
//    {CPU_SUBTYPE_CELERON, "CPU_SUBTYPE_CELERON", ""},
//};
//
//int get_header_cpu_sub_type_info_size()
//{
//    return sizeof(arr_st_header_cpu_sub_type) / sizeof(struct header_cpu_sub_type_info);
//}

/** header 的 filetype 的说明 */
struct header_file_type_info arr_st_header_file_type[] =
{
    {},
    {MH_OBJECT, "MH_OBJECT", "relocatable object file"},
    {MH_EXECUTE, "MH_EXECUTE", "demand paged executable file"},
    {MH_FVMLIB, "MH_FVMLIB", "fixed VM shared library file"},
    {MH_CORE, "MH_CORE", "core file"},
    {MH_PRELOAD, "MH_PRELOAD", "preloaded executable file"},
    {MH_DYLIB, "MH_DYLIB", "dynamically bound shared library"},
    {MH_DYLINKER, "MH_DYLINKER", "dynamic link editor"},
    {MH_BUNDLE, "MH_BUNDLE", "dynamically bound bundle file"},
    {MH_DYLIB_STUB, "MH_DYLIB_STUB", "shared library stub for static linking only, no section contents"},
    {MH_DSYM, "MH_DSYM", "companion file with only debug sections"},
    {MH_KEXT_BUNDLE, "MH_KEXT_BUNDLE", "x86_64 kexts"},
    {MH_FILESET, "MH_FILESET", "a file composed of other Mach-Os to be run in the same userspace sharing a single linkedit"},
    {MH_GPU_EXECUTE, "MH_GPU_EXECUTE", "gpu program"},
    {MH_GPU_DYLIB, "MH_GPU_DYLIB", "gpu support functions"}
};

/** header 的 flag 的说明 */
struct header_flag_info arr_st_header_flag_info[] =
{
    {MH_NOUNDEFS, "MH_NOUNDEFS", "the object file has no undefined references"},
    {MH_INCRLINK, "MH_INCRLINK", "the object file is the output of an incremental link against a base file and can't be link edited again"},
    {MH_DYLDLINK, "MH_DYLDLINK", "the object file is input for the dynamic linker and can't be staticly link edited again"},
    {MH_BINDATLOAD, "MH_BINDATLOAD", "the object file's undefined references are bound by the dynamic linker when loaded"},
    {MH_PREBOUND, "MH_PREBOUND", "the file has its dynamic undefined references prebound"},
    {MH_SPLIT_SEGS, "MH_SPLIT_SEGS", "the file has its read-only and read-write segments split"},
    {MH_LAZY_INIT, "MH_LAZY_INIT", "he shared library init routine is to be run lazily via catching memory faults to its writeable segments (obsolete)"},
    {MH_TWOLEVEL, "MH_TWOLEVEL", "the image is using two-level name space bindings"},
    {MH_FORCE_FLAT, "MH_FORCE_FLAT", "the executable is forcing all images to use flat name space bindings"},
    {MH_NOMULTIDEFS, "MH_NOMULTIDEFS", "this umbrella guarantees no multiple defintions of symbols in its sub-images so the two-level namespace hints can always be used"},
    {MH_NOFIXPREBINDING, "MH_NOFIXPREBINDING", "do not have dyld notify the prebinding agent about this executable"},
    {MH_PREBINDABLE, "MH_PREBINDABLE", "the binary is not prebound but can have its prebinding redone. only used when MH_PREBOUND is not set"},
    {MH_ALLMODSBOUND, "MH_ALLMODSBOUND", "indicates that this binary binds to all two-level namespace modules of its dependent libraries. only used when MH_PREBINDABLE and MH_TWOLEVEL are both set"},
    {MH_SUBSECTIONS_VIA_SYMBOLS, "MH_SUBSECTIONS_VIA_SYMBOLS", "safe to divide up the sections into sub-sections via symbols for dead code stripping"},
    {MH_CANONICAL, "MH_CANONICAL", "the binary has been canonicalized via the unprebind operation"},
    {MH_WEAK_DEFINES, "MH_WEAK_DEFINES", "the final linked image contains external weak symbols"},
    {MH_BINDS_TO_WEAK, "MH_BINDS_TO_WEAK", "the final linked image uses weak symbols"},
    {MH_ALLOW_STACK_EXECUTION, "MH_ALLOW_STACK_EXECUTION", "When this bit is set, all stacks in the task will be given stack execution privilege.  Only used in MH_EXECUTE filetypes"},
    {MH_ROOT_SAFE, "MH_ROOT_SAFE", "When this bit is set, the binary declares it is safe for use in processes with uid zero"},
    {MH_SETUID_SAFE, "MH_SETUID_SAFE", "When this bit is set, the binary declares it is safe for use in processes when issetugid() is true"},
    {MH_NO_REEXPORTED_DYLIBS, "MH_NO_REEXPORTED_DYLIBS", "When this bit is set on a dylib, the static linker does not need to examine dependent dylibs to see if any are re-exported"},
    {MH_PIE, "MH_PIE", "When this bit is set, the OS will load the main executable at a random address.  Only used in MH_EXECUTE filetypes"},
    {MH_DEAD_STRIPPABLE_DYLIB, "MH_DEAD_STRIPPABLE_DYLIB", "Only for use on dylibs.  When linking against a dylib that has this bit set, the static linker will automatically not create a LC_LOAD_DYLIB load command to the dylib if no symbols are being referenced from the dylib"},
    {MH_HAS_TLV_DESCRIPTORS, "MH_HAS_TLV_DESCRIPTORS", "Contains a section of type S_THREAD_LOCAL_VARIABLES"},
    {MH_NO_HEAP_EXECUTION, "MH_NO_HEAP_EXECUTION", "When this bit is set, the OS will run the main executable with a non-executable heap even on platforms (e.g. i386) that don't require it. Only used in MH_EXECUTE filetypes"},
    {MH_APP_EXTENSION_SAFE, "MH_APP_EXTENSION_SAFE", "The code was linked for use in an application extension"},
    {MH_NLIST_OUTOFSYNC_WITH_DYLDINFO, "MH_NLIST_OUTOFSYNC_WITH_DYLDINFO", "The external symbols listed in the nlist symbol table do not include all the symbols listed in the dyld info"},
    {MH_SIM_SUPPORT, "MH_SIM_SUPPORT", "Allow LC_MIN_VERSION_MACOS and LC_BUILD_VERSION load commands with the platforms macOS, macCatalyst, iOSSimulator, tvOSSimulator and watchOSSimulator"},
    {MH_IMPLICIT_PAGEZERO, "MH_IMPLICIT_PAGEZERO", "main executable has no __PAGEZERO segment.  Instead, loader (xnu) will load program high and block out all memory below it"},
    {MH_DYLIB_IN_CACHE, "MH_DYLIB_IN_CACHE", "Only for use on dylibs. When this bit is set, the dylib is part of the dyld shared cache, rather than loose in the filesystem"}
};

int get_header_flag_info_size()
{
    return sizeof(arr_st_header_flag_info) / sizeof(struct header_flag_info);
}

/** load_command 的信息以及对应的处理方法 */
struct lc_info arr_st_lc_info[] =
{
    {LC_SEGMENT, "LC_SEGMENT", "segment of this file to be mapped"},
    {LC_SYMTAB, "LC_SYMTAB", "link-edit stab symbol table info", &parse_lc_symtab},
    {LC_SYMSEG, "LC_SYMSEG", "link-edit gdb symbol table info (obsolete)"},
    {LC_THREAD, "LC_THREAD", "thread"},
    {LC_UNIXTHREAD, "LC_UNIXTHREAD", "unix thread (includes a stack)"},
    {LC_LOADFVMLIB, "LC_LOADFVMLIB", "load a specified fixed VM shared library", &parse_lc_idfvmlib},
    {LC_IDFVMLIB, "LC_IDFVMLIB", "fixed VM shared library identification", &parse_lc_idfvmlib},
    {LC_IDENT, "LC_IDENT", "object identification info (obsolete)"},
    {LC_FVMFILE, "LC_FVMFILE", "fixed VM file inclusion (internal use)"},
    {LC_PREPAGE, "LC_PREPAGE", "prepage command (internal use)"},
    {LC_DYSYMTAB, "LC_DYSYMTAB", "dynamic link-edit symbol table info", &parse_lc_dysymtab},
    {LC_LOAD_DYLIB, "LC_LOAD_DYLIB", "load a dynamically linked shared library", &parse_lc_id_dylib},
    {LC_ID_DYLIB, "LC_ID_DYLIB", "dynamically linked shared lib ident", &parse_lc_id_dylib},
    {LC_LOAD_DYLINKER, "LC_LOAD_DYLINKER", "load a dynamic linker", &parse_lc_id_dylinker},
    {LC_ID_DYLINKER, "LC_ID_DYLINKER", "dynamic linker identification", &parse_lc_id_dylinker},
    {LC_PREBOUND_DYLIB, "LC_PREBOUND_DYLIB", "modules prebound for a dynamically"},
    {LC_ROUTINES, "LC_ROUTINES", "image routines"},
    {LC_SUB_FRAMEWORK, "LC_SUB_FRAMEWORK", "sub framework"},
    {LC_SUB_UMBRELLA, "LC_SUB_UMBRELLA", "sub umbrella"},
    {LC_SUB_CLIENT, "LC_SUB_CLIENT", "sub client"},
    {LC_SUB_LIBRARY, "LC_SUB_LIBRARY", "sub library"},
    {LC_TWOLEVEL_HINTS, "LC_TWOLEVEL_HINTS", "two-level namespace lookup hints"},
    {LC_PREBIND_CKSUM, "LC_PREBIND_CKSUM", "prebind checksum"},
    {LC_LOAD_WEAK_DYLIB, "LC_LOAD_WEAK_DYLIB", "", &parse_lc_id_dylib},
    {LC_SEGMENT_64, "LC_SEGMENT_64", "64-bit segment of this file to be mapped", &parse_segment_command_64},
    {LC_ROUTINES_64, "LC_ROUTINES_64", "64-bit image routines"},
    {LC_UUID, "LC_UUID", "the uuid", &parse_lc_uuid},
    {LC_RPATH, "LC_RPATH", "runpath additions", &parse_lc_rpath},
    {LC_CODE_SIGNATURE, "LC_CODE_SIGNATURE", "local of code signature", &parse_lc_code_signature},
    {LC_SEGMENT_SPLIT_INFO, "LC_SEGMENT_SPLIT_INFO", "local of info to split segments", &parse_lc_code_signature},
    {LC_REEXPORT_DYLIB, "LC_REEXPORT_DYLIB", "load and re-export dylib", &parse_lc_id_dylib},
    {LC_LAZY_LOAD_DYLIB, "LC_LAZY_LOAD_DYLIB", "delay load of dylib until first use"},
    {LC_ENCRYPTION_INFO, "LC_ENCRYPTION_INFO", "encrypted segment information"},
    {LC_DYLD_INFO, "LC_DYLD_INFO", "compressed dyld information", &parse_lc_dyld_info},
    {LC_DYLD_INFO_ONLY, "LC_DYLD_INFO_ONLY", "compressed dyld information only", &parse_lc_dyld_info},
    {LC_LOAD_UPWARD_DYLIB, "LC_LOAD_UPWARD_DYLIB", "load upward dylib"},
    {LC_VERSION_MIN_MACOSX, "LC_VERSION_MIN_MACOSX", "build for MacOSX min OS version", &parse_lc_version_min_macosx},
    {LC_VERSION_MIN_IPHONEOS, "LC_VERSION_MIN_IPHONEOS", "build for iPhoneOS min OS version", &parse_lc_idfvmlib},
    {LC_FUNCTION_STARTS, "LC_FUNCTION_STARTS", "compressed table of function start addresses", &parse_lc_code_signature},
    {LC_DYLD_ENVIRONMENT, "LC_DYLD_ENVIRONMENT", "string for dyld to treat like environment variable", &parse_lc_id_dylinker},
    {LC_MAIN, "LC_MAIN", "replacement for LC_UNIXTHREAD", &parse_lc_main},
    {LC_DATA_IN_CODE, "LC_DATA_IN_CODE", "table of non-instructions in __text", &parse_lc_code_signature},
    {LC_SOURCE_VERSION, "LC_SOURCE_VERSION", "source version used to build binary", &parse_lc_source_version},
    {LC_DYLIB_CODE_SIGN_DRS, "LC_DYLIB_CODE_SIGN_DRS", "Code signing DRs copied from linked dylibs", &parse_lc_code_signature},
    {LC_ENCRYPTION_INFO_64, "LC_ENCRYPTION_INFO_64", "64-bit encrypted segment information"},
    {LC_LINKER_OPTION, "LC_LINKER_OPTION", "linker options in MH_OBJECT files"},
    {LC_LINKER_OPTIMIZATION_HINT, "LC_LINKER_OPTIMIZATION_HINT", "optimization hints in MH_OBJECT files", &parse_lc_code_signature},
    {LC_VERSION_MIN_TVOS, "LC_VERSION_MIN_TVOS", "build for AppleTV min OS version", &parse_lc_version_min_macosx},
    {LC_VERSION_MIN_WATCHOS, "LC_VERSION_MIN_WATCHOS", "build for Watch min OS version", &parse_lc_version_min_macosx},
    {LC_NOTE, "LC_NOTE", "arbitrary data included within a Mach-O file"},
    {LC_BUILD_VERSION, "LC_BUILD_VERSION", "build for platform min OS version", &parse_lc_build_version},
    {LC_DYLD_EXPORTS_TRIE, "LC_DYLD_EXPORTS_TRIE", "used with linkedit_data_command, payload is trie", &parse_lc_code_signature},
    {LC_DYLD_CHAINED_FIXUPS, "LC_DYLD_CHAINED_FIXUPS", "used with linkedit_data_command", &parse_lc_code_signature},
    {LC_FILESET_ENTRY, "LC_FILESET_ENTRY", "used with fileset_entry_command"},
    {LC_ATOM_INFO, "LC_ATOM_INFO", "used with linkedit_data_command", &parse_lc_code_signature},
};

int get_arr_st_lc_info_size()
{
    return sizeof(arr_st_lc_info) / sizeof(struct lc_info);
}

void parse_segment_command_64(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct segment_command_64 segment_command64 = {0};

    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&segment_command64),
          sizeof(struct segment_command_64),
          1,
          p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);

    if (segment_command64.nsects == 0)
    {
        return ;
    }

    struct section_64 *p_section_64 = NULL;
    p_section_64 = (struct section_64*)malloc(sizeof(struct section_64) * segment_command64.nsects);

    if (p_section_64 == NULL)
    {
        return ;
    }

    fread(p_section_64, sizeof(struct section_64) * segment_command64.nsects, 1, p_file);

    for (int i = 0; i < segment_command64.nsects; i ++)
    {
        printf("sectname name: %s segname: %s \r\n", p_section_64[i].sectname, p_section_64[i].segname);
        if (p_section_64[i].offset != 0 && p_section_64[i].flags & S_ATTR_SOME_INSTRUCTIONS && ((p_section_64[i].flags & 0xff | S_REGULAR) == 0))
        {
            uint8_t *code = (uint8_t*)malloc(sizeof(uint8_t) * p_section_64[i].size);
            uint64_t code_len = p_section_64[i].size;
            fseeko(p_file, p_section_64[i].offset, SEEK_SET);

            fread(code, sizeof(char*) * p_section_64[i].size, 1, p_file);

            csh handle;
            cs_err err;

            // 初始化 Capstone 引擎
            if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
                printf("Failed to initialize Capstone!\n");
                return ;
            }

            cs_insn *insn = NULL;
            cs_option(handle, CS_OPT_SKIPDATA, CS_OPT_SYNTAX_NOREGNAME);

            uint64_t cnt = 0;

            while (cnt < code_len)
            {
                size_t count = cs_disasm(handle, code + cnt, code_len - cnt, p_section_64[i].offset + cnt, 10, &insn);
                if (count > 0) {
                    // 打印反汇编结果
                    size_t j;
                    for (j = 0; j < count; j++) {
                        printf("0x%llx:\t%s\t%s\n", insn[j].address, insn[j].mnemonic, insn[j].op_str);
                        cnt = insn[j].address - p_section_64[i].offset + insn[j].size;
                    }

                    // 释放分配的内存
                    cs_free(insn, count);
                } else {
                    printf("Failed to disassemble code!\n");
                    break;
                }
            }

            // 关闭 Capstone 引擎
            cs_close(&handle);
        }
        else if (p_section_64[i].offset != 0 && p_section_64[i].flags & S_CSTRING_LITERALS)
        {
            uint8_t *code = (uint8_t*)malloc(sizeof(uint8_t) * p_section_64[i].size);

            fseeko(p_file, p_section_64[i].offset, SEEK_SET);
            fread(code, sizeof(char*) * p_section_64[i].size, 1, p_file);

            uint64_t size = 0;
            while (size < p_section_64[i].size)
            {
                if (*((char*)(code + size)) == '\0')
                {
                    size ++;
                    continue;
                }
                size_t len = strlen((const char*)code + size);
                printf("%s \r\n", code + size);
                size += (len + 1);
            }

            printf("\r\n");
        }
    }

    free(p_section_64);
    p_section_64 = NULL;
}

void parse_lc_symtab_string(FILE *p_file, uint32_t n_strx, uint32_t stroff)
{
    /* 保存文件指针偏移 */
    off_t pos = ftello(p_file);

    fseeko(p_file, n_strx + stroff, SEEK_SET);
    size_t mal_size = 50;
    char *p_str = (char*)malloc(mal_size);
    if (p_str == NULL)
    {
        /* 恢复文件指针偏移 */
        fseeko(p_file, pos, SEEK_SET);
        return;
    }

    uint32_t cnt = 0;
    do
    {
        fread(p_str + cnt, 1, 1, p_file);

        if (*(p_str + cnt) == '\0')
        {
            printf("str: %s\r\n", p_str);
            break;
        }

        if (cnt >= mal_size * 2 / 3)
        {
            mal_size *= 2;
            p_str = (char*)realloc(p_str,mal_size);
            if (p_str == NULL)
            {
                /* 恢复文件指针偏移 */
                fseeko(p_file, pos, SEEK_SET);
                return;
            }
        }

        cnt ++;
    } while(1);

    free(p_str);
    p_str = NULL;

    /* 恢复文件指针偏移 */
    fseeko(p_file, pos, SEEK_SET);
}

void parse_lc_symtab(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct symtab_command symtab_command = {0};
    size_t read_size = -1;
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    read_size = fread((char *)(&symtab_command), sizeof(struct symtab_command), 1, p_file);
    if (read_size != 1)
    {
        printf("fread symtab_command error.\r\n");
        return;
    }
    printf("symtab_command.nsyms : %d \r\n", symtab_command.nsyms);
    fseeko(p_file, symtab_command.symoff, SEEK_SET);
    for (int i = 0; i < symtab_command.nsyms; i ++)
    {
        struct nlist_64 nlist64 = {0};
        fread(&nlist64, sizeof(struct nlist_64), 1, p_file);

        printf("n_strx: %d(%x) n_type: %d(%x) n_sect:  %d(%x) n_desc: %d(%x) n_value: %llu(%llx) \r\n",
               nlist64.n_un.n_strx, nlist64.n_un.n_strx,
               nlist64.n_type, nlist64.n_type,
               nlist64.n_sect, nlist64.n_sect,
               nlist64.n_desc, nlist64.n_desc,
               nlist64.n_value, nlist64.n_value);

        parse_lc_symtab_string(p_file, nlist64.n_un.n_strx, symtab_command.stroff);
    }
}

void parse_lc_dysymtab(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct dysymtab_command dysymtabCommand = {0};

    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&dysymtabCommand), sizeof(struct dysymtab_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);

    printf("ilocalsym: %d(%x) nlocalsym: %d(%x) "
           "iextdefsym: %d(%x) nextdefsym: %d(%x) "
           "iundefsym: %d(%x) nundefsym %d(%x) "
           "tocoff: %d(%x) ntoc: %d(%x)"
           "modtaboff: %d(%x) nmodtab: %d(%x)"
           "extrefsymoff: %d(%x) nextrefsyms: %d(%x)"
           "indirectsymoff: %d(%x) nindirectsyms: %d(%x)"
           "extreloff: %d(%x) nextrel: %d(%x)"
           "locreloff: %d(%x) nlocrel: %d(%x) \r\n",
           dysymtabCommand.ilocalsym, dysymtabCommand.ilocalsym,
           dysymtabCommand.nlocalsym, dysymtabCommand.nlocalsym,
           dysymtabCommand.iextdefsym, dysymtabCommand.iextdefsym,
           dysymtabCommand.nextdefsym, dysymtabCommand.nextdefsym,
           dysymtabCommand.iundefsym, dysymtabCommand.iundefsym,
           dysymtabCommand.nundefsym, dysymtabCommand.nundefsym,
           dysymtabCommand.tocoff, dysymtabCommand.tocoff,
           dysymtabCommand.ntoc, dysymtabCommand.ntoc,
           dysymtabCommand.modtaboff, dysymtabCommand.modtaboff,
           dysymtabCommand.nmodtab, dysymtabCommand.nmodtab,
           dysymtabCommand.extrefsymoff, dysymtabCommand.extrefsymoff,
           dysymtabCommand.nextrefsyms, dysymtabCommand.nextrefsyms,
           dysymtabCommand.indirectsymoff, dysymtabCommand.indirectsymoff,
           dysymtabCommand.nindirectsyms, dysymtabCommand.nindirectsyms,
           dysymtabCommand.extreloff, dysymtabCommand.extreloff,
           dysymtabCommand.nextrel, dysymtabCommand.nextrel,
           dysymtabCommand.locreloff, dysymtabCommand.locreloff,
           dysymtabCommand.nlocrel, dysymtabCommand.nlocrel);
}

void parse_lc_id_dylinker(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    char *p_mem = (char*)malloc(lc_info->st_load_command.cmdsize * sizeof(char));
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);

    if (p_mem == NULL)
    {
        return;
    }

    fread(p_mem, lc_info->st_load_command.cmdsize * sizeof(char), 1, p_file);
    printf("type: %s \r\n", st_lc_info.p_lc_name);
    printf("name: %s \r\n", p_mem + ((struct dylinker_command*)p_mem)->name.offset);

    free(p_mem);
    p_mem = NULL;
}

void parse_lc_uuid(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct uuid_command uuidCommand = {0};
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&uuidCommand), sizeof(struct uuid_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
    printf("uuid: ");
    for (int i = 0; i < 16; i ++)
    {
        printf("%02X ", uuidCommand.uuid[i]);
    }

    printf("\r\n");
}

void parse_lc_build_version(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct build_version_command buildVersionCommand = {0};
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&buildVersionCommand), sizeof(struct build_version_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_source_version(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct source_version_command sourceVersionCommand = {0};
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&sourceVersionCommand), sizeof(struct source_version_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
    printf("version: %llu.%llu.%llu.%llu.%llu(%llx) \r\n",
           sourceVersionCommand.version >> 48 & 0xfff,
           sourceVersionCommand.version >> 30 & 0x3ff,
           sourceVersionCommand.version >> 20 & 0x3ff,
           sourceVersionCommand.version >> 10 & 0x3ff,
           sourceVersionCommand.version & 0x3ff,
           sourceVersionCommand.version);
}

void parse_lc_main(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct entry_point_command entryPointCommand = {0};
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&entryPointCommand), sizeof(struct entry_point_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
    printf("entryoff: %llu(%llx), stacksize: %llu(%llx) \r\n",
           entryPointCommand.entryoff, entryPointCommand.entryoff,
           entryPointCommand.stacksize, entryPointCommand.stacksize);
}

void parse_lc_id_dylib(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);

    char *p_mem = (char*)malloc(sizeof(char) * lc_info->st_load_command.cmdsize);
    if (p_mem == NULL)
    {
        return;
    }
    fread(p_mem, sizeof(char) * lc_info->st_load_command.cmdsize, 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);

    printf("timestamp: %d(%x), current_version: %d(%x),"
           "compatibility_version: %d(%x) name: %s\r\n",
           ((struct dylib_command*)p_mem)->dylib.timestamp, ((struct dylib_command*)p_mem)->dylib.timestamp,
           ((struct dylib_command*)p_mem)->dylib.current_version, ((struct dylib_command*)p_mem)->dylib.current_version,
           ((struct dylib_command*)p_mem)->dylib.compatibility_version, ((struct dylib_command*)p_mem)->dylib.compatibility_version,
           p_mem + ((struct dylib_command*)p_mem)->dylib.name.offset);

    free(p_mem);
    p_mem = NULL;
}

void parse_lc_code_signature(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct linkedit_data_command linkeditDataCommand = {0};
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&linkeditDataCommand), sizeof(struct linkedit_data_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);

    printf("dataoff: %d(%x), datasize: %d(%x) \r\n",
           linkeditDataCommand.dataoff, linkeditDataCommand.dataoff,
           linkeditDataCommand.datasize, linkeditDataCommand.datasize);
}

void parse_lc_idfvmlib(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct fvmlib_command fvmlibCommand = {0};
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&fvmlibCommand), sizeof(struct fvmlib_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);

    printf("minor_version: %d(%x), header_addr: %d(%x) \r\n",
           fvmlibCommand.fvmlib.minor_version, fvmlibCommand.fvmlib.minor_version,
           fvmlibCommand.fvmlib.header_addr, fvmlibCommand.fvmlib.header_addr);
}

void parse_lc_dyld_info(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct dyld_info_command dyldInfoCommand = {0};
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&dyldInfoCommand), sizeof(struct dyld_info_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
    printf("rebase_off: %d(%x), rebase_size: %d(%x), "
           "bind_off: %d(%x), bind_size: %d(%x), "
           "lazy_bind_off: %d(%x), lazy_bind_size: %d(%x),"
           "export_off: %d(%x), export_size: %d(%x) \r\n",
           dyldInfoCommand.rebase_off, dyldInfoCommand.rebase_off,
           dyldInfoCommand.rebase_size, dyldInfoCommand.rebase_size,
           dyldInfoCommand.bind_off, dyldInfoCommand.bind_off,
           dyldInfoCommand.bind_size, dyldInfoCommand.bind_size,
           dyldInfoCommand.lazy_bind_off, dyldInfoCommand.lazy_bind_off,
           dyldInfoCommand.lazy_bind_size, dyldInfoCommand.lazy_bind_size,
           dyldInfoCommand.export_off, dyldInfoCommand.export_off,
           dyldInfoCommand.export_size, dyldInfoCommand.export_size);
}

void parse_lc_version_min_macosx(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct version_min_command versionMinCommand = {0};
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);
    fread((char *)(&versionMinCommand), sizeof(struct version_min_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);

    printf("version: %d.%d.%d(%x), sdk: %d.%d.%d(%x) \r\n",
           versionMinCommand.version >> 16 & 0xff,
           versionMinCommand.version >> 8 & 0xff,
           versionMinCommand.version & 0xff,
           versionMinCommand.version,
           versionMinCommand.sdk >> 16 & 0xff,
           versionMinCommand.sdk >> 8 & 0xff,
           versionMinCommand.sdk & 0xff,
           versionMinCommand.sdk);
}

void parse_lc_rpath(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    fseeko(p_file, (off_t)lc_info->offset, SEEK_SET);

    char *p_mem = (char*)malloc(sizeof(char) * lc_info->st_load_command.cmdsize);
    if (p_mem == NULL)
    {
        return;
    }
    fread(p_mem, sizeof(char) * lc_info->st_load_command.cmdsize, 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);

    printf("path: %s \r\n", p_mem + ((struct rpath_command*)p_mem)->path.offset);

    free(p_mem);
    p_mem = NULL;
}