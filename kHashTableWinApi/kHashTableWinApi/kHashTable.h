#pragma once
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <string>
#include <algorithm>
#define _CRT_SECURE_NO_WARNINGS
#define EMPTYNESS_KEY "THIS_CELL_IS_EMPTY"
#define EMPTYNESS_VAL 0
#define INIT initializer_list<pair<string, int>>
#define PAIR pair<string,int>
using namespace std;
int Hash(const string &key);
class kHashTable
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
kHashTable CreateHashTable(INIT & list);
void Swap(kHashTable &kHT_1, kHashTable &kHT_2 );
