/**
 * This file is part of Sodium Language project
 *
 * Copyright © 2020 Murad Karakaþ <muradkarakas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v3.0
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 *	https://choosealicense.com/licenses/gpl-3.0/
 */

#pragma once

#include <iostream> 

#include "Node.h"

using namespace std;

namespace Sodium {

    const int MAX = 100;

    class SymbolTable {
        Node* head[MAX];

    public:
        SymbolTable();

        int hashf(string id); // hash function 
        bool insert(string id, string scope, string Type, int lineno);

        string find(string id);

        bool deleteRecord(string id);

        bool modify(string id, string scope, string Type, int lineno);
    };

}





