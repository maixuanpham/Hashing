//
//  LinearHashing.h
//  Project 1
//
//  Created by Mai Pham on 3/20/18.
//  Copyright © 2018 Mai Pham. All rights reserved.
//

#ifndef LinearHashing_h
#define LinearHashing_h

#include <iostream>
#include "Entry.h"
#include <list>
#include <vector>
using namespace std;

template <typename K, typename V>
class LHashMap {
public:
    typedef Entry<const K,V> Entry;                         // a (key,value) pair
    class Iterator;                                         // a iterator/position
public:
    LHashMap(int capacity);                                  // constructor
    int size() const;                                       // number of entries
    bool empty() const;                                     // is the map empty?
    Iterator find(const K& k);                              // find entry with key k
    Iterator put(const K& k, const V& v);                   // insert/replace (k,v)
    void erase(const K& k);                                 // remove entry with key k
    void erase(const Iterator& p);                          // erase entry at p
    Iterator begin();                                       // iterator to first entry
    Iterator end();                                         // iterator to end entry
    void cluster();
    void printData();
protected:
    typedef std::list<Entry> Bucket;                        // a bucket of entries
    typedef std::vector<Bucket> BktArray;                   // a bucket array
    // ...insert HashMap utilities here
    Iterator finder(const K& k);                            // find utility
    Iterator inserter(const Iterator& p, const Entry& e);   // insert utility
    void eraser(const Iterator& p);                         // remove utility
    typedef typename BktArray::iterator BItor;              // bucket iterator
    typedef typename Bucket::iterator EItor;                // entry iterator
    static void nextEntry(Iterator& p)                      // bucket's next entry
    { ++p.ent; }
    static bool endOfBkt(const Iterator& p)                 // end of bucket?
    { return p.ent == p.bkt->end(); }
private:
    int n;                                                  // number of entries
    //H hash;                                               // the hash comparator
    BktArray B;                                             // bucket array
    int totalProbes = 0;
    int maxProbes = 0;
    int numCluster = 0;
    int maxCluster = 0;
    int totalCluster = 0;
public:
    // ...insert Iterator class declaration here
    class Iterator {                                        // an iterator (& position)
    private:
        EItor ent;                                          // which entry
        BItor bkt;                                          // which bucket
        const BktArray* ba;                                 // which bucket array
    public:
        Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
        : ent(q), bkt(b), ba(&a) { }
        Entry& operator*() const;                           // get entry
        bool operator==(const Iterator& p) const;           // are iterators equal?
        Iterator& operator++();                             // advance to next entry
        friend class LHashMap;                              // give HashMap access
    };
};

template <typename K, typename V>        // constructor
LHashMap<K,V>::LHashMap(int capacity) : n(0), B(capacity) { }

template <typename K, typename V>        // number of entries
int LHashMap<K,V>::size() const { return n; }

template <typename K, typename V>        // is the map empty?
bool LHashMap<K,V>::empty() const { return size() == 0; }

template <typename K, typename V>                           // iterator to end
typename LHashMap<K,V>::Iterator LHashMap<K,V>::end()
{ return Iterator(B, B.end()); }

template <typename K, typename V>                           // iterator to front
typename LHashMap<K,V>::Iterator LHashMap<K,V>::begin() {
    if (empty()) return end();                              // emtpty - return end
    BItor bkt = B.begin();                                  // else search for an entry
    while (bkt->empty()) ++bkt;                             // find nonempty bucket
    return Iterator(B, bkt, bkt->begin());                  // return first of bucket
}

template <typename K, typename V>                           // remove utility
void LHashMap<K,V>::eraser(const Iterator& p) {
    p.bkt->erase(p.ent);                                    // remove entry from bucket
    n--;                                                    // one fewer entry
}

template <typename K, typename V>                           // remove entry at p
void LHashMap<K,V>::erase(const Iterator& p)
{ eraser(p); }

template <typename K, typename V>                           // remove entry with key k
void LHashMap<K,V>::erase(const K& k) {
    Iterator p = finder(k);                                 // find k
    if (endOfBkt(p))                                        // not found?
    {    //throw NonexistentElement("Erase of nonexistent");   // ...error
        cout << "Erase of nonexistent" << endl;
        return;
    }
    eraser(p);                                              // remove it
}

template <typename K, typename V>                           // find utility
typename LHashMap<K,V>::Iterator LHashMap<K,V>::finder(const K& k) {
    int probes = 0;
    int i = k % B.size();                                   // get hash index i
    BItor bkt = B.begin() + i;                              // the ith bucket
    Iterator p(B, bkt, bkt->begin());                       // start of ith bucket
    probes++;
    while (!endOfBkt(p) && (*p).key() != k)                 // search for k
    //while (!bkt->empty())
    {
        bkt++;
        if (bkt == B.end())
            bkt = B.begin();
        //else
        //    bkt++;
        //nextEntry(p);
        p = Iterator (B, bkt, bkt->begin());
        probes++;
    }
    totalProbes += probes;
    if (probes > maxProbes)
        maxProbes = probes;
    return p;                                               // return final position
}

template <typename K, typename V>
void LHashMap<K,V>::cluster()    {
    int cluster = 0, cluster2 = 0;
    /*for (BItor bkt = B.begin(); bkt != B.end(); ++bkt) {
        if (!(bkt->empty()))
            cluster++;
        else    {
            if (cluster > 1)    {
                numCluster++;
                totalCluster += cluster;
                if (cluster > maxCluster)
                    maxCluster = cluster;
            }
            cluster = 0;
        }
        if (bkt == B.end()) {
            cout << "Inside << ";
            BItor bkt1 = B.begin();
            while (!(bkt1->empty()))
            {
                cluster2++;
                bkt1++;
                cout << "in";
            }
            totalCluster -= cluster2;
            cluster += cluster2;
            if (cluster > maxCluster)
                maxCluster = cluster;
            //numCluster--;
        }
    }*/
    BItor bkt = B.begin();
    while (bkt != B.end()) {
        if (!(bkt->empty()))
            cluster++;
        else    {
            if (cluster > 1)    {
                numCluster++;
                totalCluster += cluster;
                if (cluster > maxCluster)
                    maxCluster = cluster;
            }
            cluster = 0;
        }
        bkt++;
    }
    if (bkt == B.end() && !(bkt->empty())) {
        if (cluster > 1)    {
            numCluster++;
            totalCluster += cluster;
            if (cluster > maxCluster)
                maxCluster = cluster;
        }
        BItor bkt1 = B.begin();
        if (!(bkt1->empty()))   {
            while (!(bkt1->empty()))    {
                cluster2++;
                bkt1++;
            }
            cluster += cluster2;
            if (cluster > maxCluster)
                maxCluster = cluster;
            numCluster--;
        }
    }
}

template <typename K, typename V>
void LHashMap<K,V>::printData()    {
    cluster();
    cout << "Table size: " << B.size() << endl;
    cout << "Total Probes: " << totalProbes << endl;
    cout << "Average number of probes: " << (double)(totalProbes) / n << endl;
    cout << "Maximum number of probes for worst case: " << maxProbes << endl;
    cout << "Number of clusters: " << numCluster << endl;
    //cout << "Total clusters: " << totalCluster << endl;
    if (numCluster == 0)
        cout << "Average clusters size: " << numCluster << endl;
    else
        cout << "Average clusters size: " << (double)(totalCluster)/numCluster << endl;
    cout << "Largest cluster size: " << maxCluster << endl << endl;
}

template <typename K, typename V>                           // find key
typename LHashMap<K,V>::Iterator LHashMap<K,V>::find(const K& k) {
    Iterator p = finder(k);                                 // look for k
    if (endOfBkt(p))                                        // didn't find it?
        return end();                                       // return end iterator
    else
        return p;                                           // return its position
}

template <typename K, typename V>                           // insert utility
typename LHashMap<K,V>::Iterator LHashMap<K,V>::inserter(const Iterator& p, const Entry& e) {
    EItor ins = p.bkt->insert(p.ent, e);                    // insert before p
    n++;                                                    // one more entry
    return Iterator(B, p.bkt, ins);                         // return this position
}

template <typename K, typename V>                           // insert/replace (v,k)
typename LHashMap<K,V>::Iterator LHashMap<K,V>::put(const K& k, const V& v) {
    Iterator p = finder(k);                                 // search for k
    if (endOfBkt(p)) {                                      // k not found?
        return inserter(p, Entry(k, v));                    // insert at end of bucket
    }
    else {                                                  // found it?
        p.ent->setValue(v);                                 // replace value with v
        return p;                                           // return this position
    }
}

template <typename K, typename V>                           // are iterators equal?
bool LHashMap<K,V>::Iterator::operator==(const Iterator& p) const {
    if (ba != p.ba || bkt != p.bkt) return false;           // ba or bkt differ?
    else if (bkt == ba->end()) return true;                 // both at the end?
    else return (ent == p.ent);                             // else use entry to decide
}

template <typename K, typename V>                           // advance to next entry
typename LHashMap<K,V>::Iterator& LHashMap<K,V>::Iterator::operator++() {
    ++ent;                                                  // next entry in bucket
    if (endOfBkt(*this)) {                                  // at end of bucket?
        ++bkt;                                              // go to next bucket
        while (bkt != ba->end() && bkt->empty())            // find nonempty bucket
            ++bkt;
        if (bkt == ba->end()) return *this;                 // end of bucket array?
        ent = bkt->begin();                                 // first nonempty entry
    }
    return *this;                                           // return self
}

template <typename K, typename V>                           // get entry
typename LHashMap<K,V>::Entry& LHashMap<K,V>::Iterator::operator*() const
{ return *ent; }

#endif /* LinearHashing_h */

