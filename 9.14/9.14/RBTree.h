#pragma once
#pragma once
#include <iostream>
using namespace std;

//����������Ǻ�ɫ���Ǻ�ɫ
enum Color
{
	RED,
	BLACK
};
template <class T>
//�ȶ�����
struct RBtreeNode
{
	//����Ҳ��֪��������ʲô�� ��T����
	RBtreeNode<T>* _left;
	RBtreeNode<T>* _right;
	RBtreeNode<T>* _parent;
	Color _col;
	T _data;
		
	RBtreeNode(const T& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)//������Ǻ�ɫ,�������Ԫ���Ǻ�ɫ��
		, _data(data)
	{}

};


template <class T>
struct _Iterator
{
	typedef _Iterator<T> Self;
	typedef RBtreeNode<T> Node;


	_Iterator(Node * node)
		:_node(node)
	{}

	T& operator*()
	{
		return _node->_data;
	}
	T* operator->()
	{
		return &_node->_data;
	}
	Self& operator++()
	{
		//����ұߴ��ڣ���ô������С���
		if (_node->_right)
		{
			Node* curright = _node->_right;
			while (curright->_left)
			{
				curright = curright->_left;
			}
			_node = curright;
		}
		else//�ұ߲����ڣ����Һ����Ǹ�����ߵ��Ǹ�����
		{
			Node* cur = _node;

			Node* parent = cur->_parent;

			while (parent)
			{
				if (cur == parent->_left)
					break;
				else
				{
					cur = parent;
					parent = cur->_parent;
				}
			}
			_node = parent;
		}
		return *this;
	}
	bool operator!=(const Node* n)
	{
		return _node != n;
	}
	//�������ײ��װ�Ž��ָ��
	Node* _node;
};

template <class K, class T,class keyofT>
//�����K��find���� keyֵ
class RBTree
{
	typedef RBtreeNode<T> Node;
	typedef _Iterator<T> iterator;
public:
	//������ĵ�����������ĵ����������ƶ����Զ������ͣ������װ��ָ�룬��Ϊԭ��ָ�벻����Ҫ��
	iterator begin()//����ߵĽ��
	{
		Node* curleft = _root;
		while (curleft && curleft->_left)//��Ҫ�ж�һ��curleft�Ƿ�Ϊ�գ���Ϊrootͷ����Ϊ��
		{
			curleft = curleft->_left;
		}

		return iterator(curleft);
	}
	iterator end()
	{
		return iterator(nullptr);//�ÿձ�ʾend();
	}
	keyofT kof;
	//�������������е�key
	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (kof(cur->_data) < key)
			{
				cur = cur->_right;
			}
			else if (kof(cur->_data) > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;

	}
	//��������������һ�µ�
	bool Insert(const T& data)//���ں���������������ǲ�ȷ������ֻ��T����
	{
		//������Ĳ�������������Ĳ���
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return true;
		}

		//˵���ö��������ǿ�������ô�ͽ��бȽ��ҵ�λ��
		Node* cur = _root;
		Node* parent = nullptr;
		keyofT kof;
		while (cur)
		{
			//������Ϊ���������ݵ�����ʲô���͵ģ������޷������Ƚ�
			//������Ҫ����Kֵ�����бȽϣ������յ����ݿ�����pair���͵�
			//����������Ҫһ���º���keyofT����ȡK���ͺ�pair���͵����Kֵ

			
			if (kof(cur->_data) < kof(data))
			{
				parent = cur;
				//��¼����λ��
				cur = cur->_right;
			}
			else if (kof(cur->_data) > kof(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		//�ߵ��������curΪ���ˣ�����λ���Ѿ��ҵ���
		cur = new Node(data);
		cur->_col = RED;
		//�������Ǻ�ɫ��
		if (kof(data) > kof(parent->_data))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		//ע�����������������Ҫע�⸸ָ��
		cur->_parent = parent;


		//�������Ǻ�ɫ�ģ�Ȼ��������ڵ��Ǻ�ɫ����ô��û���£���������ڵ��Ǻ�ɫ��ô����Ҫ���ۣ�
		//����parent������
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//�ȼ�¼���游λ��

			if (parent == grandfather->_left)
			{
				//˵���������ұ�
				Node* uncle = grandfather->_right;
				//uncle������Ϊ��ɫ
				if (uncle && uncle->_col == RED)
				{
					//�����������ɫ+���ϵ���
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;


				}
				else//uncle�����ڻ���uncle����Ϊ��ɫ   �����������ת+��ɫ   ��ת�����Ϊ��������Ҫ���ɫ
				{
					if (cur == parent->_left)
					{
						//����
						RotateR(grandfather);
						//��ɫ
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//˫��
						//������
						RotateL(parent);
						RotateR(grandfather);

						//��ɫ
						cur->_col = BLACK;
						grandfather->_col = RED;

					}
					break;
				}
			}
			else//parent==grandfather->_right
			{
				Node* uncle = grandfather->_left;

				//uncle������Ϊ��ɫ
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle�����ڻ��ߴ�����Ϊ��ɫ
				{
					if (cur == parent->_right)
					{
						//����
						RotateL(grandfather);
						//��ɫ
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//������������
						RotateR(parent);
						RotateL(grandfather);
						//��ɫ
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;

				}
			}

		}
		
		//�������������ڵ�ʱ�����ڵ㲻���ڣ������ʱ�����Ҫ�Ǻ�ɫ����ô����Ҫ��ɫ��ɫ
		_root->_col = BLACK;
		return true;
	}
	bool CheckColour(Node* root, int blacknum, int benchmark)
	{
		if (root == nullptr)
		{
			if (blacknum != benchmark)
				return false;

			return true;
		}

		if (root->_col == BLACK)
		{
			++blacknum;
		}

		if (root->_col == RED && root->_parent && root->_parent->_col == RED)
		{
			cout << root->_kv.first << "����������ɫ�ڵ�" << endl;
			return false;
		}

		return CheckColour(root->_left, blacknum, benchmark)
			&& CheckColour(root->_right, blacknum, benchmark);
	}

	bool IsBalance()
	{
		return IsBalance(_root);
	}

	bool IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		if (root->_col != BLACK)
		{
			return false;
		}

		// ��׼ֵ
		int benchmark = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				++benchmark;

			cur = cur->_left;
		}

		return CheckColour(root, 0, benchmark);
	}

	void RotateL(Node* parent)//����
	{

		Node* cur = parent->_right;

		Node* curleft = cur->_left;
		parent->_right = curleft;
		if (curleft)
		{
			curleft->_parent = parent;
		}
		cur->_left = parent;
		Node* pp = parent->_parent;
		parent->_parent = cur;



		if (parent == _root)
		{
			//��ô����cur���Ǹ������
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (pp->_left == parent)
			{
				pp->_left = cur;
			}
			else
			{
				pp->_right = cur;
			}

			cur->_parent = pp;
			//��ת��cur��parent bf��Ϊ0?
		}

	}
	void RotateR(Node* parent)//�ҵ���
	{
		Node* cur = parent->_left;

		Node* curright = cur->_right;

		parent->_left = curright;
		if (curright)
		{
			curright->_parent = parent;
		}
		Node* ppnode = parent->_parent;
		cur->_right = parent;
		parent->_parent = cur;

		if (ppnode == nullptr)
		{
			//˵��cur�ͱ�ɸ��ڵ���
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = cur;
			}
			else
			{
				ppnode->_right = cur;
			}
			cur->_parent = ppnode;
		}

	}
private:
	Node* _root = nullptr;

};