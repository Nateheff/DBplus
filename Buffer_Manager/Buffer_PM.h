#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

#include "Frame.h"
#include "../Nodes/Node.h"
#include "../Disk_Space/Disk_SM.h"
const int POOL_SIZE = 1024;
class Buffer_Pool
{
    std::vector<Frame>pool;
    Disk_SM* dsm;

    public:
    
    Buffer_Pool(Disk_SM* dsm_p):dsm(dsm_p){pool.reserve(POOL_SIZE);};
    Node* get_page(uint16_t page_num);
    bool release_page(uint16_t page_num);
};