#pragma once

static uint16_t Swap16(uint16_t value) {
    return  (value >> 8) | 
            (value << 8);
}

static uint32_t Swap32(uint32_t value) {
    return  ((value >> 24) & 0x000000FF) | 
            ((value >> 8)  & 0x0000FF00) | 
            ((value << 8)  & 0x00FF0000) | 
            ((value << 24) & 0xFF000000);
}

static uint64_t Swap64(uint64_t value) {
    return  ((value >> 56) & 0x00000000000000FF) |
            ((value >> 40) & 0x000000000000FF00) |
            ((value >> 24) & 0x0000000000FF0000) |
            ((value >>  8) & 0x00000000FF000000) |
            ((value <<  8) & 0x000000FF00000000) |
            ((value << 24) & 0x0000FF0000000000) |
            ((value << 40) & 0x00FF000000000000) |
            ((value << 56) & 0xFF00000000000000);
}