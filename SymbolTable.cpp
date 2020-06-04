/**
 * This file is part of Sodium Language project
 *
 * Copyright � 2020 Murad Karaka� <muradkarakas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v3.0
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 *	https://choosealicense.com/licenses/gpl-3.0/
 */

#include <iostream>

#include "SymbolTable.h"
#include "Node.h"

using namespace std;

SymbolTable::SymbolTable()
{
    for (int i = 0; i < MAX; i++)
        head[i] = NULL;
}

// Function to modify an identifier 
bool 
    SymbolTable::modify(
        string id, 
        string s, 
        string t,
        int l
    )
{
    int index = hashf(id);
    Node* start = head[index];

    if (start == NULL)
        return "-1";

    while (start != NULL) {
        if (start->identifier == id) {
            start->scope = s;
            start->type = t;
            start->lineNo = l;
            return true;
        }
        start = start->next;
    }

    return false; // id not found 
}

// Function to delete an identifier 
bool 
    SymbolTable::deleteRecord(
        string id
    )
{
    int index = hashf(id);
    Node* tmp = head[index];
    Node* par = head[index];

    // no identifier is present at that index 
    if (tmp == NULL) {
        return false;
    }
    // only one identifier is present 
    if (tmp->identifier == id && tmp->next == NULL) {
        tmp->next = NULL;
        delete tmp;
        return true;
    }

    while (tmp->identifier != id && tmp->next != NULL) {
        par = tmp;
        tmp = tmp->next;
    }
    if (tmp->identifier == id && tmp->next != NULL) {
        par->next = tmp->next;
        tmp->next = NULL;
        delete tmp;
        return true;
    }

    // delete at the end 
    else {
        par->next = NULL;
        tmp->next = NULL;
        delete tmp;
        return true;
    }
    return false;
}

// Function to find an identifier 
string 
    SymbolTable::find(
        string id
    )
{
    int index = hashf(id);
    Node* start = head[index];

    if (start == NULL)
        return "-1";

    while (start != NULL) {

        if (start->identifier == id) {
            start->print();
            return start->scope;
        }

        start = start->next;
    }

    return "-1"; // not found 
}

// Function to insert an identifier 
bool 
    SymbolTable::insert(
        string id, 
        string scope,
        string Type, 
        int lineno
    )
{
    int index = hashf(id);
    Node* p = new Node(id, scope, Type, lineno);

    if (head[index] == NULL) {
        head[index] = p;
        cout << "\n"
            << id << " inserted";

        return true;
    }

    else {
        Node* start = head[index];
        while (start->next != NULL)
            start = start->next;

        start->next = p;
        cout << "\n"
            << id << " inserted";

        return true;
    }

    return false;
}

int 
SymbolTable::hashf(
    string id
)
{
    int asciiSum = 0;

    for (int i = 0; i < id.length(); i++) {
        asciiSum = asciiSum + id[i];
    }

    return (asciiSum % 100);
}

