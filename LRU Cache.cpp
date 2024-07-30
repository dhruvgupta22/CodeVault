#include <bits/stdc++.h>
using namespace std;

struct CacheBlock
{
    int data;
    CacheBlock *prev, *next;
    CacheBlock(int x): data(x), prev(NULL), next(NULL) {};
};

class Cache
{
  protected:
    map<int,CacheBlock*> mp;
    int max_capacity;
    CacheBlock *tail, *head;

  public:
    virtual void set(int key, int value) = 0;
    virtual int get(int key) = 0;
};
class LRUCache : public Cache
{
  protected:
    int curr_time;
    map<int,int> time;
    int curr_size;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    void updateAccessTime(int key)
    {
        time[key] = curr_time++;
        pq.push({time[key],key});
    }
    
    void removeFromList(CacheBlock* &p)
    {
        CacheBlock* prev = p->prev;
        CacheBlock* next = p->next;
        if(prev) prev->next = next;
        if(next) next->prev = prev;
        delete p;
    }
    
    void removeLRUblock()
    {
        while(!pq.empty() && curr_size == max_capacity)
        {
            auto [key,timeStamp] = pq.top();
            pq.pop();
            
            if(time.find(key) != time.end() && timeStamp >= time[key])
            {
                time.erase(key);
                CacheBlock* p = mp[key];
                mp.erase(key);
                removeFromList(p);
                curr_size--;   
            }
        }
    }
  public:
    LRUCache(int cap)
    {
        curr_time = 0;
        curr_size = 0;
        max_capacity = cap;
    }
    
    void set(int key, int value)
    {
        if(mp.find(key) != mp.end())
            mp[key]->data = value;
        
        else
        {
            if(curr_size == max_capacity)
                removeLRUblock();
            
            CacheBlock* new_block = new CacheBlock(value);
            mp[key] = new_block;
            tail->next = new_block;
            new_block->prev = tail;
            curr_size++;
        }
        
        updateAccessTime(key);
    }
    
    int get(int key)
    {
        if(mp.find(key) != mp.end())
        {
            updateAccessTime(key);
            return mp[key]->data;
        }
        else return -1;
    }
};

int main()
{
    int N, M;
    cin >> N >> M;
     
    LRUCache cache(M);
    
    string op;
    int key, value;
    
    while(N--){
        cin >> op;
        if(op == "set")
        {
            cin >> key >> value;
            cache.set(key,value);
        }
        else if(op == "get")
        {
            cin >> key;
            cout << cache.get(key) << endl;
        }
    }
    return 0;
}
