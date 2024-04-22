#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <algorithm>
#include<numeric>
#include <chrono>
using namespace std;

#define TABLE_SIZE 1000
#define MAX_KICKS 10

int hash1(int k) {
    return k /10;
}

int hash2(int k) {
    return k + 1;
}

class CuckooHashTable {
private:
    vector<int> table1;
    vector<int> table2;
public:
    CuckooHashTable() {//�ṩ��ʼ������
        table1.resize(TABLE_SIZE, -1);
        table2.resize(TABLE_SIZE, -1);
    }

    bool insert(int key) {
        return insertHelper(key, 0);
    }

    bool insertHelper(int key, int tableIdx, int cnt = 0) {//keyΪ��������ݣ�tableIdxΪ��ǰ�����hash��cntΪ��ǰ���˵ڼ���
        if (cnt > MAX_KICKS) return false;
        if (tableIdx == 0) {//��hash��1�����ж�
            size_t hashValue = hash1(key) % TABLE_SIZE;
            if (table1[hashValue] == -1) {//hash��1��δ������ͻ����������
                table1[hashValue] = key;
                return true;
            }
            else {//hash��1������ͻ����1�������߳�
                int displacedKey = table1[hashValue];
                table1[hashValue] = key;
                return insertHelper(displacedKey, 1, cnt + 1);
            }
        }
        else {
            size_t hashValue = hash2(key) % TABLE_SIZE;
            if (table2[hashValue] == -1) {
                table2[hashValue] = key;
                return true;
            }
            else {
                int displacedKey = table2[hashValue];
                table2[hashValue] = key;
            }
        }
    }

    bool search(int key) {
        size_t hashValue1 = hash1(key) % TABLE_SIZE;
        size_t hashValue2 = hash2(key) % TABLE_SIZE;
        if (table1[hashValue1] == key || table2[hashValue2] == key)//���hash��1��2���Ƿ�洢������
            return true;
        else
            return false;
    }
};

vector<int> random_creator() {
    random_device rd;
    mt19937 gen(rd());

    // ���ɴ�1��10000������
    vector<int> sequence(10000);
    vector<int> randoms(0);
    iota(sequence.begin(), sequence.end(), 1);
    // ��������
    shuffle(sequence.begin(), sequence.end(), gen);
    copy(sequence.begin(), sequence.begin() + 1000, back_inserter(randoms));
    return randoms;
}


int main() {
    
    
    double average_time = 0;//ƽ��ֵ
    double average_false = 0;//ƽ���������
    double totaltime = 0;
    double sum_false = 0;
    
    int j;
    for (j = 0; j < 10000; j++) {
        CuckooHashTable hashTable;
        //���������
        vector<int> randoms;
        randoms = random_creator();
        // ���������
        auto start = chrono::high_resolution_clock::now();
        for (int i : randoms) {
            hashTable.insert(i);
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        totaltime += duration.count();
        int false_cnt = 0;
        // ��ѯһЩԪ��,ͳ
        for (int i : randoms) {
            if (hashTable.search(i) == false) false_cnt++;
        }
        cout << false_cnt << endl;
        sum_false += false_cnt;
    }
    average_false = sum_false / 10000;
    average_time = totaltime / 10000;
    cout << "�������ʱ��Ϊ��" << average_time << " nanoseconds" << endl;
    cout << "ƽ���޷�������Ϊ��" << average_false;
    return 0;
}
