#pragma once
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

#include "run.h"
#include "Nodes/Node.h"
#include "Catalog/Syst_Root.h"

void search(uint16_t key,uint16_t num_rows,uint16_t row_size, char ind_type, Run* obj);
void insert(uint16_t key, uint16_t num_rows,uint16_t row_size, Run* obj, Curr_Node leaf);