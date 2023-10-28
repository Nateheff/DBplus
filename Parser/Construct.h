#pragma once

#include <iostream>
#include <stdint.h>
#include <map>
#include <vector>

#include "../Commands/Commands.h"

bool receiver_main(std::vector<uint16_t> full_tok,std::vector<std::string> identifiers,Keyword_List*list);