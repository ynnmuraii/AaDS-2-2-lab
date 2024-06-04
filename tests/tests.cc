#include <gtest/gtest.h>
#include <hash_table/hash_table.h>
#include <iostream>

using namespace hash_table;
using namespace std;

TEST(HashTableTest, InsertString) {
	HashTable<int, string> a(10);
	a.insert(5, "cat");
	a.insert(13, "dog");
	a.insert(9, "pig");
	HashTable<int, string> b(a);
	a.print();
	b.print();
	cout << a.count(6) << endl;
}

TEST(HashTableTest, InsertInt) {
	HashTable <int, int> a(10);
	a.insert(1, 15);
	a.insert(1, 9);
	a.insert(3, 26);
	a.insert(56, 7);
	a.print();
	HashTable<int, int> b(a);
	b.print();
	cout << a.count(1) << endl;
}

TEST(HashTableTest, HashTableRand) {
	HashTable<int, string> c(10, 5);
	c.print();
}

TEST(HashTableTest, Insert_or_AssignString) {
	HashTable<int, string> a(10);
	a.insert(5, "cat");
	a.insert(13, "dog");
	a.insert(9, "pig");
	a.insert(1, "mice");
	a.print();
	a.insert_or_assign(2, "parrot");
	a.print();
}

TEST(HashTableTest, EraseString) {
	HashTable<int, string> a(10);
	a.insert(5, "cat");
	a.insert(13, "dog");
	a.insert(4, "pig");
	a.insert(1, "mice");
	a.print();
	a.erase(4);
	a.print();

}
TEST(HashTableTest, SearchT) {
	HashTable<int, string> a(10);
	a.insert(5, "cat");
	a.insert(13, "dog");
	a.insert(4, "pig");
	a.insert(1, "mice");
	cout << *a.search(4) << endl;
}

TEST(HashTableTest, Ñomparison) {
	string s1 = "it always seems impossible until its done";
	string s2 = "it always seems impossible";
	cout << "Result: " << hash_comparison<>(s1, s2) << endl;
	string s3 = "it always seems impossible until its done";
	string s4 = "it always seems impossible until its done";
	cout << "Result: " << hash_comparison<>(s3, s4) << endl;
}