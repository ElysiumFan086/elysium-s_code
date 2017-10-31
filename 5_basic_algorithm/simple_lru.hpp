class LRUCache {
public:
    LRUCache(int capacity) : n_size(capacity) {
        
    }
    
    int get(int key) {
        auto itr = hash_cache.find(key);
        if(itr == hash_cache.end())  return -1;
        lst_cache.splice(lst_cache.begin(), lst_cache, itr->second);
        
        return itr->second->second;
    }
    
    void put(int key, int value) {
        auto itr = hash_cache.find(key);
        if(itr != hash_cache.end())  lst_cache.erase(itr->second);
        
        lst_cache.push_front(std::make_pair(key, value));
        hash_cache[key] = lst_cache.begin();
        if(hash_cache.size() > n_size){
            int n_key_rm = lst_cache.rbegin()->first;
            lst_cache.pop_back();
            hash_cache.erase(n_key_rm);
        }
    }
    
    int n_size;
    
    std::list<std::pair<int, int>> lst_cache;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> hash_cache;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
