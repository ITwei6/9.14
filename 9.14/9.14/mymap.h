#pragma once
#include "RBTree.h"

namespace tao
{

    //����ģ�������ʵ������ͬ�ĺ����
    template <class K,class V>
    class map
    {
      
    public:

        //����������ʵ����Ϊ�洢pair<K,V>���͵�
        
        struct map_keyoft
        {
            const K& operator()(const pair<K, V>& kv)
            {
                return kv.first;
            }
        };
    

        bool insert(const pair<K,V>& kv)//����������������ɺ����������������й�
            //ֱ�ӵ��ú�����Ľӿ�
        {
            return _rb.Insert(kv); //��Ϊmap�ײ�����������pair��������
        }
    private:
        RBTree<K, pair<K,V>, map_keyoft>  _rb;
    };//���ݴ���ģ�����T��ͬ�Ĳ������ú�������治ͬ������
}
