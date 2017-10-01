#pragma once
#include"kHashTable.h"
class Controller
{
public:
	Controller();
	void equalize(kHashTable &k_1, kHashTable &k_2);
	void swap(kHashTable &k_1, kHashTable &k_2);
	void read_str(LPARAM lParam, WPARAM wParam, string &key_1);
	void emplace(kHashTable &Table_ONE, string & key_1, string &value_1);
	void delete_elem(kHashTable &Table_ONE, string &del_key_1);
	void clear(kHashTable &Table_ONE);
	string is_empty(kHashTable&Table_ONE);
	string is_full(kHashTable&Table_ONE);
	string size(kHashTable&Table_ONE);
};