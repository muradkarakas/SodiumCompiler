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

#include "pch.h"

#include <iostream> 
#include "Node.h"

using namespace std;

Node::Node()
{
    next = NULL;
}

Node::Node(string key, string value, string type, int lineNo)
{
    this->identifier = key;
    this->scope = value;
    this->type = type;
    this->lineNo = lineNo;
    next = NULL;
}

void Node::print()
{
    cout << "Identifier's Name:" << identifier
        << "\nType:" << type
        << "\nScope: " << scope
        << "\nLine Number: " << lineNo << endl;
}
