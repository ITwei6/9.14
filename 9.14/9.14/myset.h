#pragma once
#include "RBTree.h"
namespace tao
{

    //根据模板参数来实例化不同的红黑树
    template <class K>//根据传给模板参数T不同的参数，让红黑树来存不同的数据
    class set
    {

    public:

        //这里的红黑树被实例化成存储K类型的
        struct set_keyoft
        {
            const K& operator()(const K& kv)
            {
                return kv;
            }
        };
        bool insert(const K& kv)
        {
            return _rb.Insert(kv);//因为set底层红黑树里存的是K类型数据
        }
    private:
        RBTree<K, K, set_keyoft>  _rb;
    };
}