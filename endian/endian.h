//
// Created by Netor0x86 on 2024/6/28.
//

#ifndef CSTUDY_ENDIAN_H
#define CSTUDY_ENDIAN_H

#include "../macho/macho64.h"

#define _LITTLE_ENDIAN 0x01
#define _BIG_ENDIAN    0x02

/**
 * 返回16位小尾数据
 *
 * @param value 待处理的数值
 * @param endian 字节序
 * @return 如果是小尾，则返回小尾数据，否则返回小尾数据
 */
uint16_t big_endian_to_little_endian_uint16(uint16_t value, uint32_t endian);

/**
 * 返回32位小尾数据
 *
 * @param value 待处理的数值
 * @param endian 字节序
 * @return 如果是小尾，则返回小尾数据，否则返回小尾数据
 */
uint32_t big_endian_to_little_endian_uint32(uint32_t value, uint32_t endian);

/**
 * 返回64位小尾数据
 *
 * @param value 待处理的数值
 * @param endian 字节序
 * @return 如果是小尾，则返回小尾数据，否则返回小尾数据
 */
uint64_t big_endian_to_little_endian_uint64(uint64_t value, uint32_t endian);

#endif //CSTUDY_ENDIAN_H
