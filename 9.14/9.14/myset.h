#pragma once
#include "RBTree.h"
namespace tao
{

    //����ģ�������ʵ������ͬ�ĺ����
    template <class K>//���ݴ���ģ�����T��ͬ�Ĳ������ú�������治ͬ������
    class set
    {

    public:

        //����ĺ������ʵ�����ɴ洢K���͵�
        struct set_keyoft
        {
            const K& operator()(const K& kv)
            {
                return kv;
            }
        };
        bool insert(const K& kv)
        {
            return _rb.Insert(kv);//��Ϊset�ײ�����������K��������
        }
    private:
        RBTree<K, K, set_keyoft>  _rb;
    };
}