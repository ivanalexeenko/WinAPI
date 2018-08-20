#pragma once
#include <windows.h>
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#define EMPTYNESS_KEY "THIS_CELL_IS_EMPTY"
#define EMPTYNESS_VAL 0
#define INIT initializer_list<pair<string, int>>
#define PAIR pair<string,int>
using namespace std;
int Hash(const string &key);
string ReadText(LPARAM lParam);
int FromStrToInt(string& value_1);

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
public:
	void AddObserver(Observer * observer);
	void NotifyUpdate();
private:
	vector<Observer*> observers;
};

class kHashTable : public Observable
{
private:
	pair<string, int> *arr;
	int size = 0;
	const int MAX_SIZE = 30;
	int added_elem = 0;
public:
	struct Iterator
	{
	private:
		pair<string, int> *ptr;
	public:
		Iterator();
		Iterator(pair<string, int> *p);
		pair<string, int> &operator*();
		pair<string, int> *operator=(const Iterator &second);
		pair<string, int> *operator->();
		pair<string, int> *operator++(int);//postfix
		pair<string, int> *operator--(int);//postfix

		pair<string, int> *operator++();//prefix
		pair<string, int> *operator--();//prefix

		bool operator==(const Iterator &second);
		bool operator!=(const Iterator &second);

	};
	Iterator Begin() { return Iterator(arr); }
	Iterator End() { return Iterator(arr + size); }
	kHashTable();
	kHashTable(int s);
	kHashTable(const kHashTable &kHT);
	kHashTable(kHashTable&&kHT);
	kHashTable(INIT &list);
	~kHashTable();
	kHashTable &operator = (const kHashTable &kHT);
	kHashTable &operator = (kHashTable &&kHT);

	pair<string, int>&operator[] (int index);
	friend ostream &operator << (ostream &os, kHashTable &kHT);
	friend istream &operator >> (istream &is, kHashTable &kHT);
	bool IsEmpty();
	bool IsFull();
	int Size();
	pair<string, int> *Find(string &str);
	bool IsCellEmpty(int index);
	bool Insert(const string &key, const int value);
	bool Insert(const pair<string, int>&elem);
	bool Insert(const char *str, const int value);
	bool Insert(INIT &args, ...);

	template <class ...Args>
	bool Emplace(const Args...args)
	{
		return Insert(PAIR(args...));
	}
	bool Append(INIT &list);
	void Clear();
	bool Delete(string &key);
};

class View : public Observer
{
private:
	kHashTable kHT_1;
	kHashTable kHT_2;
	HDC hdc;
	HWND hWnd;
	HFONT hFont;
	POINT Center;
public:
	View();
	View(kHashTable &k_1, kHashTable &k_2,HDC _hdc ,HWND _hWnd,HFONT _hFont,POINT _Center);
	View &operator = (View & v);
	virtual void update();
};



kHashTable CreateHashTable(INIT & list);
void Swap(kHashTable &kHT_1, kHashTable &kHT_2 );

