/* ===============================================================
 //
 //  Copyright by Ambi Studio 2018
 //  Licensed under the Apache License, Version 2.0 (the "License");
 //  (Please find "LICENSE" file attached for license details)
 //============================================================= */

#include "fsm_record.h"
#include "../config.h"
#include <iostream>

namespace vs {
  
    fsm_record::fsm_record(char* map_add, size_t begin_pos, int block_size, int record_size): 
        map(map_add), 
        beg(begin_pos),
        b_size(block_size),
        r_size(record_size)
    { };
    
    void fsm_record::c_str(char* buff) {

        // buffer with max size = block size (except meta) * number of blocks
        int num_of_blocks = map[beg + r_size] & 0xff;
        
        int r = 0, b = 0; // row & block iterator
        size_t buff_pos = 0;
        size_t beg_pos = beg;
        
        for (b = 0; b < num_of_blocks; b++) {
            
            r = 0;
            
            // This loop will exclude meta chars
            while (map[beg_pos + r] != '\0') {
                
                buff[buff_pos++] = map[beg_pos + r];
                r++;
            }
            beg_pos += b_size;
        }
        
        buff[buff_pos] = '\0';
    }
    
    fsm_record fsm_record::next() {
        
        size_t next_block_beg = beg +
        ((map[beg + r_size] & 0xff) * b_size) + 1;
        
        return fsm_record(map, next_block_beg, b_size, r_size);
    }
    
    fsm_record fsm_record::prev() {
        size_t last_block_beg = beg -
        (map[beg - 1] & 0xff * b_size);
        return fsm_record(map, last_block_beg, b_size, r_size);
    }
    
    const char* fsm_record::substr(int len) {
        return "";
    }
    
    const char* fsm_record::substr(int start, int len) {
        return "";
    }
}