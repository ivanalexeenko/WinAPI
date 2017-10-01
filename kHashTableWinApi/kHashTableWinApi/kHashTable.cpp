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

string ReadText(LPARAM lParam)
{
	int length = SendMessage((HWND)lParam, WM_GETTEXTLENGTH, 0, 0);
	char *buffer = new char[length];
	SendMessage((HWND)lParam, WM_GETTEXT, (WPARAM)(length + 1), (LPARAM)buffer);
	string temp_num_str(buffer);
	return temp_num_str;
}

int FromStrToInt(string & value_1)
{
	int val_1 = 0;
	int deg = value_1.length() - 1;
	for (auto i : value_1)
	{
		val_1 += ((i - '0') * pow(10, deg));
		deg--;
	}
	return val_1;
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
	NotifyUpdate();
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
	NotifyUpdate();
	return *this;
}

pair<string, int>& kHashTable::operator[](int index)
{
	return arr[index];
}

bool kHashTable::IsEmpty()
{
	NotifyUpdate();
	if (added_elem == 0) return true;
	else return false;
}

bool kHashTable::IsFull()
{
	NotifyUpdate();
	if (size == added_elem) return true;
	else return false;
}

int kHashTable::Size()
{
	NotifyUpdate();
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
		NotifyUpdate();
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
			NotifyUpdate();
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
	NotifyUpdate();
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
			NotifyUpdate();
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
			NotifyUpdate();
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

View::View()
{
	kHT_1 = kHashTable();
	kHT_2 = kHashTable();
	hdc = NULL;
	hWnd = NULL;
	hFont = NULL;
	Center.x = 0;
	Center.y = 0;
}

View::View(kHashTable & k_1, kHashTable & k_2, HDC _hdc, HWND _hWnd, HFONT _hFont, POINT _Center)
{
	kHT_1 = k_1;
	kHT_2 = k_2;
	hdc = _hdc;
	hWnd = _hWnd;
	hFont = _hFont;
	Center = _Center;

}

View & View::operator=(View & v)
{
	kHT_1 = v.kHT_1;
	kHT_2 = v.kHT_2;
	hdc = v.hdc;
	hWnd = v.hWnd;
	hFont = v.hFont;
	Center = v.Center;
	return *this;
}

void View::update()
{
	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);
	SetBkMode(hdc, TRANSPARENT);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, Center.x / 3, 0, (LPCSTR)"kHashTable_1", strlen("kHashTable_1"));
	TextOut(hdc, Center.x / 0.7, 0, (LPCSTR)"kHashTable_2", strlen("kHashTable_2"));
	int format = Center.y / 10;
	int index = 0;
	for (kHashTable::Iterator i = kHT_1.Begin(); i != kHT_1.End(); i++)
	{
		string str = "[" + to_string(index++) + "]" + "  Key : " + (i->first) + "  Value : " + to_string(i->second);
		TextOut(hdc, Center.x / 6, format += 20, str.c_str(), strlen(str.c_str()));
	}
	index = 0;
	format = Center.y / 10;
	for (kHashTable::Iterator i = kHT_2.Begin(); i != kHT_2.End(); i++)
	{
		string str = "[" + to_string(index++) + "]" + "  Key : " + (i->first) + "  Value : " + to_string(i->second);
		TextOut(hdc, Center.x / 0.8, format += 20, str.c_str(), strlen(str.c_str()));
	}

	EndPaint(hWnd, &ps);
}


void Observable::AddObserver(Observer * observer)
{
	observers.push_back(observer);
}

void Observable::NotifyUpdate()
{
	for (auto i : observers)
	{
		i->update();
	}
}

