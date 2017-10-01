#include "stdafx.h"
#include "Controller.h"

Controller::Controller()
{
}

void Controller::equalize(kHashTable& k_1, kHashTable &k_2)
{
	k_1 = k_2;
}

void Controller::swap(kHashTable & k_1, kHashTable & k_2)
{
	Swap(k_1, k_2);
}

void Controller::read_str(LPARAM lParam, WPARAM wParam, string &key_1)
{
	switch (HIWORD(wParam))
	{
	case EN_KILLFOCUS:
	{

		key_1 = ReadText(lParam);
		break;
	}

	}
}

void Controller::emplace(kHashTable & Table_ONE, string & key_1, string & value_1)
{
	if (key_1.length() != 0 && value_1.length() != 0)
	{

		Table_ONE.Emplace(key_1, FromStrToInt(value_1));
	}
}

void Controller::delete_elem(kHashTable & Table_ONE, string & del_key_1)
{
	if (del_key_1.length() != 0)
	{
		Table_ONE.Delete(del_key_1);
	}
}

void Controller::clear(kHashTable & Table_ONE)
{
	Table_ONE.Clear();
}

string Controller::is_empty(kHashTable & Table_ONE)
{
	string buf;
	bool result = Table_ONE.IsEmpty();
	if (result == true)
	{
		buf = "true";
	}
	else buf = "false";
	return buf;
}

string Controller::is_full(kHashTable & Table_ONE)
{
	string buf;
	bool result = Table_ONE.IsFull();
	if (result == true)
	{
		buf = "true";
	}
	else buf = "false";
	return buf;
}

string Controller::size(kHashTable & Table_ONE)
{
	return to_string(Table_ONE.Size());
}




