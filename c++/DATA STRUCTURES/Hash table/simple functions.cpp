#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
#define ll long long
const ll HashTableSize = 10007;

struct node {
    string key;
    string phonenumber;
    node* next;
};

node* HashTable[HashTableSize] = {nullptr};

ll HashFunction(string key) { // hashing
    ll power = 1, index = 0;
    for (char c : key) {
        c = tolower(c);
        index = (index + 1LL * (c - '0' + 1) * power) % HashTableSize;
        power = (power * 31) % HashTableSize;
    }
    return index;
}

void InsertElement(string key, string value) {
    ll index = HashFunction(key);


    node* temp = HashTable[index];
    while (temp != nullptr) { // check if key existed
        if (temp->key == key) {
            temp->phonenumber = value;
            return;
        }
        temp = temp->next;
    }

    temp = new node{key, value, HashTable[index]}; // initializer list
    HashTable[index] = temp;
}

void SearchElement(string key) {
    ll index = HashFunction(key);
    node* temp = HashTable[index];

    while (temp != nullptr) {
        if (temp->key == key) {
            cout << temp->phonenumber << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "NOT FOUND" << endl;
}

void DeleteElement(string key) {
    ll index = HashFunction(key);
    node* temp = HashTable[index], *prev = nullptr;

    while (temp != nullptr) {
        if (temp->key == key) {
            if (prev == nullptr)
                HashTable[index] = temp->next;
            else
                prev->next = temp->next; // link node prev to temp->next, skip node temp

            delete temp;
            cout << "Deleted " << key << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "NOT FOUND" << endl;
}

void ClearTable() {
    for (int i = 0; i < HashTableSize; i++) {
        node* temp = HashTable[i];
        while (temp != nullptr) {
            node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        HashTable[i] = nullptr; // hashtable khong cap phat tren heap, node moi cap phat tren heap
    }
}

int main() {
    InsertElement("sytoan", "0762583261");
    InsertElement("minhthu", "0935111037");

    SearchElement("sytoan");
    SearchElement("toansamba");

    DeleteElement("sytoan");
    SearchElement("sytoan");

    ClearTable();
}
