#include "stdafx.h"
#include "kHashTable.h"
int Hash(const string & key)
{
	int hash = 23;
	for (auto i = key.begin(); i != key.end(); i++)
	{
		hash = ((hash << 2) + hash) + (int)*i;
	}
	return hash;
}

ostream & operator<<(ostream & os, kHashTable & kHT)
{
	for (int i = 0; i < kHT.size; i++)
	{
		os << "[" << i << "]" << "  Key: " << kHT.arr[i].first << "  Value:" << kHT.arr[i].second << endl;
	}
	return os;
}

istream & operator >> (istream & is, kHashTable & kHT)
{
	string key;
	int value;
	for (int i = 0; i < kHT.size; i++)
	{
		cout << "[" << i << "]";
		cout << "  (Key and Value):";
		is >> key >> value;
		kHT.Insert(key, value);
	}
	return is;
}

kHashTable CreateHashTable(INIT & list)
{
	kHashTable buffer(list);
	return buffer;
}

void Swap(kHashTable & kHT_1, kHashTable & kHT_2)
{
	kHashTable temp;
	temp = kHT_1;
	kHT_1 = kHT_2;
	kHT_2 = temp;
}

kHashTable::kHashTable()
{
	added_elem = 0;
	size = MAX_SIZE;
	arr = new pair<string, int>[size];
	for (int i = 0; i < size; i++)
	{
		arr[i].first = EMPTYNESS_KEY;
		arr[i].second = EMPTYNESS_VAL;
	}
}

kHashTable::kHashTable(int s)
{
	added_elem = 0;
	size = s;
	arr = new pair<string, int>[size];
	for (int i = 0; i < size; i++)
	{
		arr[i].first = EMPTYNESS_KEY;
		arr[i].second = EMPTYNESS_VAL;
	}
}

kHashTable::kHashTable(const kHashTable & kHT)
{
	size = kHT.size;
	arr = new pair<string, int>[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = kHT.arr[i];
	}
	added_elem = kHT.added_elem;
}

kHashTable::kHashTable(kHashTable && kHT)
{
	size = kHT.size;
	arr = new pair<string, int>[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = kHT.arr[i];
	}
	added_elem = kHT.added_elem;

	kHT.added_elem = 0;
	kHT.arr = NULL;
	kHT.size = 0;
}

kHashTable::kHashTable(INIT& list)
{

	size = list.size();
	*this = kHashTable(size);
	for (INIT::iterator i = list.begin(); i != list.end(); i++)
	{
		Insert(*i);
		added_elem++;
	}



}

kHashTable::~kHashTable()
{
	delete[] arr;
}

kHashTable & kHashTable::operator=(const kHashTable & kHT)
{
	if (this != &kHT)
	{
		delete[] arr;
		size = kHT.size;
		arr = new pair<string, int>[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = kHT.arr[i];
		}
		added_elem = kHT.added_elem;
	}
	return *this;
}

kHashTable & kHashTable::operator=(kHashTable && kHT)
{
	size = kHT.size;
	arr = new pair<string, int>[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = kHT.arr[i];
	}
	added_elem = kHT.added_elem;
	kHT.added_elem = 0;
	kHT.arr = NULL;
	kHT.size = 0;
	return *this;
}

pair<string, int>& kHashTable::operator[](int index)
{
	return arr[index];
}

bool kHashTable::IsEmpty()
{
	if (added_elem == 0) return true;
	else return false;
}

bool kHashTable::IsFull()
{
	if (size == added_elem) return true;
	else return false;
}

int kHashTable::Size()
{
	return size;
}

pair<string, int>* kHashTable::Find(string & str)
{
	bool found = false;
	int index = Hash(str) % size;
	pair<string, int>*ptr = NULL;
	for (index; index < size && found == false; index++)
	{
		ptr = arr + index;
		if (arr[index].first == str)
		{
			found = true;
		}
	}
	if (found == true)
	{
		return ptr;
	}
	else
	{
		index = Hash(str) % size;
		for (index; index >= 0 && found == false; index--)
		{
			ptr = arr + index;
			if (arr[index].first == str)
			{
				found = true;
			}
		}
	}
	return ptr;
}

bool kHashTable::IsCellEmpty(int index)
{
	if (arr[index].first == EMPTYNESS_KEY && arr[index].second == EMPTYNESS_VAL)
	{
		return true;
	}
	else return false;
}

bool kHashTable::Insert(const string & key, const int value)
{
	int index = Hash(key) % size;

	while (index <(size - 1) && IsCellEmpty(index) == false)
	{
		index++;
	}
	if (IsCellEmpty(index) == true)
	{
		arr[index] = pair<string, int>(key, value);
		added_elem++;
		return true;
	}
	else
	{
		index = Hash(key) % size;
		while (index > 0 && IsCellEmpty(index) == false)
		{
			index--;
		}

		if (IsCellEmpty(index) == true)
		{
			arr[index] = pair<string, int>(key, value);
			added_elem++;
			return true;
		}
		else return false;

	}

}

bool kHashTable::Insert(const pair<string, int>& elem)
{
	bool result = Insert(elem.first, elem.second);
	return result;
}

bool kHashTable::Insert(const char * str, const int value)
{
	string convert(str);
	bool result = Insert(convert, value);
	return result;
}

bool kHashTable::Insert(INIT & args, ...)
{
	for (auto i = args.begin(); i != args.end() - 1; i++)
	{
		Insert(*i);
	}
	return Insert(*(args.end() - 1));
}

bool kHashTable::Append(INIT & list)
{
	for (auto i = list.begin(); i != list.end() - 1; i++)
	{
		Insert(*i);
	}
	bool result = Insert(*(list.end() - 1));
	return result;
}

void kHashTable::Clear()
{
	*this = kHashTable(size);
}

bool kHashTable::Delete(string & key)
{
	bool found = false;
	int index = Hash(key) % size;
	for (index; index < size; index++)
	{
		if (key == arr[index].first)
		{
			arr[index] = pair<string, int>(EMPTYNESS_KEY, EMPTYNESS_VAL);
			added_elem--;
			found = true;
		}
	}
	index = Hash(key) % size - 1;
	for (index; index >= 0; index--)
	{
		if (key == arr[index].first)
		{
			arr[index] = pair<string, int>(EMPTYNESS_KEY, EMPTYNESS_VAL);
			added_elem--;
			found = true;
		}
	}
	return found;
}

kHashTable::Iterator::Iterator()
{
	ptr = NULL;
}

kHashTable::Iterator::Iterator(pair<string, int>* p)
{
	ptr = p;
}

pair<string, int>& kHashTable::Iterator::operator*()
{
	return *ptr;
}

pair<string, int>* kHashTable::Iterator::operator=(const Iterator & second)
{
	ptr = second.ptr;
	return ptr;
}

pair<string, int>* kHashTable::Iterator::operator->()
{
	return ptr;
}

pair<string, int>* kHashTable::Iterator::operator++(int)
{
	return ptr++;
}

pair<string, int>* kHashTable::Iterator::operator--(int)
{
	return ptr++;
}

pair<string, int>* kHashTable::Iterator::operator++()
{
	return ++ptr;
}

pair<string, int>* kHashTable::Iterator::operator--()
{
	return --ptr;
}

bool kHashTable::Iterator::operator==(const Iterator & second)
{
	return ptr == second.ptr;
}

bool kHashTable::Iterator::operator!=(const Iterator & second)
{
	return ptr != second.ptr;
}
