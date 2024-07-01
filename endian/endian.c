//
// Created by Netor0x86 on 2024/6/28.
//
#include "endian.h"

/**
 * 返回16位小尾数据
 *
 * @param value 待处理的数值
 * @param endian 字节序
 * @return 如果是小尾，则返回小尾数据，否则返回小尾数据
 */
uint16_t big_endian_to_little_endian_uint16(uint16_t value, uint32_t endian)
{
    if (endian == DEF_LITTLE_ENDIAN)
    {
        return value;
    }

    return (value << 8) | (value >> 8);
}

/**
 * 返回32位小尾数据
 *
 * @param value 待处理的数值
 * @param endian 字节序
 * @return 如果是小尾，则返回小尾数据，否则返回小尾数据
 */
uint32_t big_endian_to_little_endian_uint32(uint32_t value, uint32_t endian)
{
    if (endian == DEF_LITTLE_ENDIAN)
    {
        return value;
    }

    return ((value << 24) & 0xFF000000) |
           ((value << 8)  & 0x00FF0000) |
           ((value >> 8)  & 0x0000FF00) |
           ((value >> 24) & 0x000000FF);
}

/**
 * 返回64位小尾数据
 *
 * @param value 待处理的数值
 * @param endian 字节序
 * @return 如果是小尾，则返回小尾数据，否则返回小尾数据
 */
uint64_t big_endian_to_little_endian_uint64(uint64_t value, uint32_t endian)
{
    if (endian == DEF_LITTLE_ENDIAN)
    {
        return value;
    }

    uint64_t result = 0;
    uint8_t *pValue = (uint8_t *)&value;
    uint8_t *pResult = (uint8_t *)&result;

    for (size_t i = 0; i < sizeof(value); ++i) {
        pResult[i] = pValue[sizeof(value) - 1 - i];
    }

    return result;
}
