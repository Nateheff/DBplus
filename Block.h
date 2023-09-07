#pragma once

#include <stdint.h>
/*
 * Only the disk space manager(dsm) and buffer manager will ever need to deal directly with blocks
 * The dsm needs to know which pages are on which blocks and ccommunicate this with the buffer
 * manager
 * 
 */

const uint32_t MAX_BLOCK = 4294967294;

typedef struct Block_Id_Data{
    uint16_t bi_hi;
    uint16_t bi_low;
}Block_Id_Data;

typedef Block_Id_Data* Block_Id;

bool Is_Valid_Block(uint32_t block_num){
    return (block_num < MAX_BLOCK);
};

void Set_Block_Id(Block_Id_Data* block_id, uint32_t block_num){
    block_id->bi_hi = block_num >> 16; //Move bits of block num 16 bits right
    block_id->bi_low = block_num & 0xffff; //bitwise and sets equal to bits in which both block_num and 0xffff bits are 1
};

bool Equal_Block_Ids(const Block_Id_Data* block_id1,const Block_Id_Data* block_id2){
    return (block_id1->bi_low == block_id2->bi_low && block_id1->bi_hi == block_id2->bi_hi);
}

uint32_t Get_Block_Num(const Block_Id_Data* block_id){
    return((uint32_t)block_id->bi_hi << 16)| ((uint32_t)block_id->bi_low);
}