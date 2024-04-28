#include <vector>
#include <array>
#include <bitset>
#include <functional>
#include <iostream>


class BloomFilter {
private:
    std::bitset<1024> bits; // ѡ���ʵ���С�� bitset
    std::hash<std::string> hash_fn1;
    std::hash<std::string> hash_fn2;

public:
    void add(const std::string& item) {
        auto hash1 = hash_fn1(item) % bits.size();
        auto hash2 = hash_fn2(item) % bits.size();
        bits.set(hash1);
        bits.set(hash2);
    }

    bool possiblyContains(const std::string& item) const {
        auto hash1 = hash_fn1(item) % bits.size();
        auto hash2 = hash_fn2(item) % bits.size();
        return bits.test(hash1) && bits.test(hash2);
    }
};


class UnionMultiDimensionalBloomFilter {
private:
    std::array<BloomFilter, 3> filters; // ������3��ά��
    BloomFilter unionFilter; // ������������

public:
    void add(const std::array<std::string, 3>& items) {
        std::string combined;
        for (size_t i = 0; i < items.size(); ++i) {
            filters[i].add(items[i]);
            combined += items[i]; // ���������ַ���
        }
        unionFilter.add(combined); // ��������ַ��������� Bloom Filter
    }

    bool possiblyContains(const std::array<std::string, 3>& items) {
        std::string combined;
        for (size_t i = 0; i < items.size(); ++i) {
            if (!filters[i].possiblyContains(items[i])) {
                return false;
            }
            combined += items[i];
        }
        return unionFilter.possiblyContains(combined); // ������� Bloom Filter
    }
};


int main() {
    UnionMultiDimensionalBloomFilter umdbf;

    // ���һЩ����
    umdbf.add({ "apple", "banana", "cherry" });
    umdbf.add({ "dog", "elephant", "frog" });

    // ���Բ�ѯ
    std::cout << "Testing 'apple', 'banana', 'cherry': "
        << (umdbf.possiblyContains({ "apple", "banana", "cherry" }) ? "Found" : "Not Found") << std::endl;
    std::cout << "Testing 'apple', 'banana', 'grape': "
        << (umdbf.possiblyContains({ "apple", "banana", "grape" }) ? "Found" : "Not Found") << std::endl;
    std::cout << "Testing 'apple', 'elephant', 'cherry': "
        << (umdbf.possiblyContains({ "apple", "elephant", "cherry" }) ? "Found" : "Not Found") << std::endl;
    return 0;
}

