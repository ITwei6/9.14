#pragma once
#include "RBTree.h"

namespace tao
{

    //根据模板参数来实例化不同的红黑树
    template <class K,class V>
    class map
    {
      
    public:

        //这里红黑树被实例化为存储pair<K,V>类型的
        
        struct map_keyoft
        {
            const K& operator()(const pair<K, V>& kv)
            {
                return kv.first;
            }
        };
    

        bool insert(const pair<K,V>& kv)//插入的数据类型是由红黑树存的数据类型有关
            //直接调用红黑树的接口
        {
            return _rb.Insert(kv); //因为map底层红黑树里存的是pair类型数据
        }
    private:
        RBTree<K, pair<K,V>, map_keyoft>  _rb;
    };//根据传给模板参数T不同的参数，让红黑树来存不同的数据
}
