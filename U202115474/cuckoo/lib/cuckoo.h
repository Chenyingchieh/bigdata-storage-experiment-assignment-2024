//#pragma once
#include "hash.h"
#include <bits/stdc++.h>

//用于扩容的size备选值，数值来源于STL
static const int size_num = 28;
static const unsigned long sizes[size_num] = {
    53,        97,          193,          389,         769,       1543,
    3079,      6151,        12289,        24593,       49157,     98317,
    196613,    393241,      786433,       1572869,     3145739,   6291469,
    12582917,  25165843,    50331653,     100663319,   201326611, 402653189,
    805306457, 16106122741, 3221225473ul, 4294967291ul};

// T是key的类型，P是value的类型
template <class T, class P>
class CuckooMap {
    //当前大小在sizes里的对应下标
    int size_pos;
    //当前大小
    int _size;
    //当前元素数量
    int num;
    //拥挤阈值
    double num_limits;
    //每个链表元素上限
    int num_per_bucket;
    // a和b两个链表数组
    std::vector<std::list<std::pair<T, P>>> a, b;
    //两个哈希函数
    std::function<int(T)> hasha, hashb;

public:
    //迭代器
    class iterator {
    public:
        typedef typename std::list<std::pair<T, P>>::iterator Iter;
        //链表指针
        Iter ptr;
        //父实例
        CuckooMap<T, P> &outer;
        //当前在哪个数组
        int vec_num;
        //在当前数组的第几个链表
        int pos;

    public:
        // 迭代器构造函数
        iterator(CuckooMap<T, P> &_outer, Iter p, int _vec_num, int _pos) :
            outer(_outer), ptr(p), vec_num(_vec_num), pos(_pos) {
        }
        // 指针解引用操作符重载
        std::pair<T, P> &operator*() {
            return *ptr;
        }
        //成员访问重载
        Iter operator->() {
            return ptr;
        }
        // 前缀自增操作符重载
        iterator &operator++() {
            ptr++;
            if (vec_num == 0) { //当前在a数组
                auto &vec = outer.a;
                if (ptr != vec[pos].end()) return *this;
                pos++;
                while (pos < vec.size()) {
                    if (!vec[pos].empty()) break;
                    pos++;
                }
                if (pos == vec.size()) {
                    vec_num = 1;
                    auto &Vec = outer.b;
                    pos = 0;
                    while (pos < Vec.size()) {
                        if (!Vec[pos].empty()) break;
                        pos++;
                    }
                    // b数组走到了最后，返回end
                    if (pos == Vec.size()) {
                        ptr = Vec.back().end();
                        return *this;
                    }
                    //在b数组中找到了
                    ptr = Vec[pos].begin();
                    return *this;
                }
                //在a数组找到了
                ptr = vec[pos].begin();
                return *this;
            } else { //当前在b数组
                auto &vec = outer.b;
                if (ptr != vec[pos].end()) return *this;
                pos++;
                while (pos < vec.size()) {
                    if (!vec[pos].empty()) break;
                    pos++;
                }
                // b数组走到了最后，返回end
                if (pos == vec.size()) {
                    ptr = vec.back().end();
                    return *this;
                }
                //在b数组中找到了
                ptr = vec[pos].begin();
                return *this;
            }
            //理论上不会走到这
            return *this;
        }

        // 后缀自增操作符重载
        iterator operator++(int) {
            // todo
            iterator temp = *this;
            ++*this;
            return temp;
        }
        // 比较操作符重载
        bool operator!=(const iterator &other) const {
            return ptr != other.ptr;
        };
    };
    //默认构造
    CuckooMap<T, P>() :
        size_pos(0), _size(sizes[0]), num(0), num_limits(0.75),
        num_per_bucket(5) {
        Hash_Generator<T> *hash_generator = new Hash_Generator<T>();
        hasha = hash_generator->alloc();
        hashb = hash_generator->alloc();
        a.resize(_size);
        b.resize(_size);
        delete hash_generator;
    }
    //指定哈希函数进行构造
    CuckooMap<T, P>(std::function<int(T)> hasha, std::function<int(T)> hashb) :
        size_pos(0), _size(sizes[0]), hasha(hasha), hashb(hashb), num(0),
        num_limits(0.75), num_per_bucket(5) {
        a.resize(_size);
        b.resize(_size);
    }
    //析构函数
    ~CuckooMap<T, P>(){};
    //清空
    void clear() {
        a.clear();
        b.clear();
        num = 0;
    }
    //判断是否需要扩容
    bool need_enlarge() {
        return 1.0 * num / _size > num_limits;
    }

    //扩容
    void enlarge() {
        // printf("enlage trigeered\n");
        size_pos++;
        _size = sizes[size_pos];
        std::vector<std::list<std::pair<T, P>>> temp;
        for (auto &v : a) temp.push_back(std::move(v));
        for (auto &v : b) temp.push_back(std::move(v));
        clear();
        a.resize(_size);
        b.resize(_size);
        for (auto list : temp)
            for (auto v : list) insert(v.first, v.second);
    }
    //修改阈值
    void change_limits(double _limits) {
        num_limits = _limits;
    }

    //修改每个链表的元素上限
    void change_num_limits(int _nums) {
        num_limits = _nums;
    }
    //插入键值对
    void insert(T key, P value) {
        iterator it = find(key);
        if (it != end()) { //原本就在
            it->second = value;
            return;
        }
        //新增键值对
        if (need_enlarge()) enlarge();
        num++;
        int posa = hasha(key) % _size;
        int posb = hashb(key) % _size;
        //没满就加到较小的桶里
        if (a[posa].size() > b[posb].size())
            b[posb].emplace_back(key, value);
        else if (a[posa].size() < num_per_bucket)
            a[posa].emplace_back(key, value);
        else {
            //虽然弹出的元素如果也全满，直接调用插入有二分之一的概率选到同一个桶，但由于添加元素是从桶位加，
            //弹出元素是从桶头弹，因此选中的不是同一个元素，与另选一个桶没有区别。
            if (time(0) % 2) {
                auto temp = a[posa].front();
                a[posa].pop_front();
                a[posa].emplace_back(key, value);
                insert(temp.first, temp.second);
            } else {
                auto temp = a[posb].front();
                a[posa].pop_front();
                a[posa].emplace_back(key, value);
                insert(temp.first, temp.second);
            }
        }
    }

    //删除键值对,返回下一个元素的迭代器
    iterator erase(iterator it) {
        iterator nxt = it;
        nxt++;
        if (it.vec_num == 0) {
            it.outer.a[it.pos].erase(it.ptr);
        } else {
            it.outer.b[it.pos].erase(it.ptr);
        }
        num--;
        return nxt;
    }
    //删除键值对,返回下一个元素的迭代器
    iterator erase(T key) {
        iterator it = find(key);
        return erase(it);
    }
    //查找键值对
    iterator find(T key) {
        int posa = hasha(key) % _size;
        int posb = hashb(key) % _size;
        for (auto it = a[posa].begin(); it != a[posa].end(); it++)
            if (it->first == key) return iterator(*this, it, 0, posa);
        for (auto it = b[posb].begin(); it != b[posb].end(); it++)
            if (it->first == key) return iterator(*this, it, 1, posa);
        return end();
    }
    //键值对计数(其实只有0或1)
    int count(T key) {
        return find(key) != end();
    }
    //首
    iterator begin() {
        for (int i = 0; i < a.size(); i++)
            if (!a[i].empty()) return iterator(*this, a[i].begin(), 0, i);
        for (int i = 0; i < b.size(); i++)
            if (!b[i].empty()) return iterator(*this, b[i].begin(), 0, i);
        return end();
    }

    //尾
    iterator end() {
        return iterator(*this, b.back().end(), 1, b.size() - 1);
    }

    int size() {
        return num;
    }
};