//
// Created by apple on 2024/6/20.
//
#include <strings.h>
#include "macho.h"

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
    {LC_RPATH, "LC_RPATH", "runpath additions"},
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

    fseek(p_file, lc_info->offset, SEEK_SET);
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
    long offset = ftell(p_file);
    for (int i = 0; i < segment_command64.nsects; i ++)
    {
        printf("sectname name: %s segname: %s \r\n", p_section_64[i].sectname, p_section_64[i].segname);
        if (p_section_64[i].offset != 0 && p_section_64[i].flags & S_ATTR_SOME_INSTRUCTIONS && ((p_section_64[i].flags & 0xff & S_REGULAR) == 0))
        {
            uint8_t *code = (uint8_t*)malloc(sizeof(uint8_t) * p_section_64[i].size);
            uint64_t code_len = p_section_64[i].size;
            fseek(p_file, p_section_64[i].offset, SEEK_SET);

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

            fseek(p_file, p_section_64[i].offset, SEEK_SET);
            fread(code, sizeof(char*) * p_section_64[i].size, 1, p_file);

            uint64_t size = 0;
            while (size < p_section_64[i].size)
            {
                if (*(code + size) == NULL)
                {
                    size ++;
                    continue;
                }
                size_t len = strlen(code + size);
                printf("%s \r\n", code + size);
                size += (len + 1);
            }

            printf("\r\n");
        }
    }

    if (p_section_64)
    {
        free(p_section_64);
        p_section_64 = NULL;
    }
    fseek(p_file, offset, SEEK_SET);
}

void parse_lc_symtab(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct symtab_command symtab_command = {0};

    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&symtab_command), sizeof(struct symtab_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_dysymtab(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct dysymtab_command dysymtabCommand = {0};

    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&dysymtabCommand), sizeof(struct dysymtab_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_id_dylinker(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    char *p_load_command = (char*)malloc(lc_info->st_load_command.cmdsize * sizeof(char));
    fseek(p_file, lc_info->offset, SEEK_SET);
//    fseek(p_file, sizeof(struct load_command) * -1, SEEK_CUR);
    if (p_load_command == NULL)
    {
        fseek(p_file, lc_info->st_load_command.cmdsize, SEEK_CUR);
        return;
    }

    fread(p_load_command, lc_info->st_load_command.cmdsize * sizeof(char), 1, p_file);
    printf("type: %s \r\n", st_lc_info.p_lc_name);
    printf("name: %s \r\n", p_load_command + ((struct dylinker_command*)p_load_command)->name.offset);

    if (p_load_command != NULL)
    {
        free(p_load_command);
        p_load_command = NULL;
    }
}

void parse_lc_uuid(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct uuid_command uuidCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&uuidCommand), sizeof(struct uuid_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_build_version(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct build_version_command buildVersionCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&buildVersionCommand), sizeof(struct build_version_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_source_version(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct source_version_command sourceVersionCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&sourceVersionCommand), sizeof(struct source_version_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_main(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct entry_point_command entryPointCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&entryPointCommand), sizeof(struct entry_point_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
    printf("entryoff: %llx \r\n", entryPointCommand.entryoff);
}

void parse_lc_id_dylib(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct dylib_command dylibCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&dylibCommand), sizeof(struct dylib_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_code_signature(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct linkedit_data_command linkeditDataCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&linkeditDataCommand), sizeof(struct linkedit_data_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_idfvmlib(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct fvmlib_command fvmlibCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&fvmlibCommand), sizeof(struct fvmlib_command), 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_dyld_info(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct dyld_info_command dyldInfoCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&dyldInfoCommand) + sizeof(uint32_t) * 2, sizeof(struct dyld_info_command) - sizeof(uint32_t) * 2, 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}

void parse_lc_version_min_macosx(FILE *p_file, struct load_command_info *lc_info, struct lc_info st_lc_info)
{
    struct version_min_command versionMinCommand = {0};
    fseek(p_file, lc_info->offset, SEEK_SET);
    fread((char *)(&versionMinCommand) + sizeof(uint32_t) * 2, sizeof(struct version_min_command) - sizeof(uint32_t) * 2, 1, p_file);

    printf("type: %s \r\n", st_lc_info.p_lc_name);
}
