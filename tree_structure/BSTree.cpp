#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

/* 
BST树代码实现，与之相关的力扣算法题

BST树插入，删除，查询操作，递归和非递归实现
BST树前序，中序，后序，层序遍历的递归和非递归实现
BST求树的高度，节点元素个数
BST树区间元素查找
判断二叉树是否是一颗BST树
BST求子树问题
BST的LCA问题：求寻找最近公共祖先节点
BST树的镜像反转问题
BST树的镜像对称问题
已知BST树的前序遍历和中序遍历，重建BST树
判断一颗BST树是否是平衡树
求BST树中序遍历倒数第K个节点
*/

template<typename T,typename Comp=less<T>>
class BSTree
{
public:
    // 二叉树节点定义
    struct Node
    {
        Node(T data=T())
        :data_(data)
        ,left_(nullptr)
        ,right_(nullptr)
        {}

        T data_;
        Node* left_;
        Node* right_;
    };
    
    BSTree(Comp comp=Comp())
    :root_(nullptr)
    ,comp_(comp)
    {}

    // 层序遍历思想释放BST树所有节点资源
    ~BSTree()
    {
        if(root_!=nullptr)
        {
            queue<Node*> s;
            s.push(root_);
            while (!s.empty())
            {
                Node* front=s.front();
                s.pop();
                if(front->left_!=nullptr)
                {
                    s.push(front->left_);
                }
                if(front->right_!=nullptr)
                {
                    s.push(front->right_);
                }
                delete front;
            }
        }
    }

    // 非递归插入操作
    void n_insert(const T& val)
    {
        // 树为空，生成根节点
        if(root_==nullptr)
        {
            root_=new Node(val);
            return;
        }

        // 搜索合适的插入位置，记录父节点的位置
        Node* parent=nullptr;
        Node* cur=root_;
        while (cur!=nullptr)
        {
            if(cur->data_==val)
            {
                // 不插入元素相同的值
                return;
            }
            else if(comp_(val,cur->data_))
            {
                parent=cur;
                cur=cur->left_;
            }
            else
            {
                parent=cur;
                cur=cur->right_;
            }
        }

        // 把新节点插入到parent节点的孩子上
        if(comp_(val,parent->data_))
        {
            parent->left_=new Node(val);
        }
        else
        {
            parent->right_=new Node(val);
        }
    }

    // 非递归删除操作
    void n_remove(const T& val)
    {
        // 树空直接返回
        if(root_==nullptr)
        {
            return;
        }

        // 搜索待删除节点
        Node* parent = nullptr;
		Node* cur = root_;
        while (cur!=nullptr)
        {
            if(cur->data_==val)
            {
                break;
            }
            else if(comp_(val,cur->data_))
            {
                parent=cur;
                cur=cur->left_;
            }
            else
            {
                parent=cur;
                cur=cur->right_;
            }
        }

        // 没找到待删除节点
        if(cur==nullptr)
        {
            return;
        }
        /*
        1.删除节点没有子节点，直接删除
        2.删除节点有一个子节点，将子节点替换父节点
        3.删除节点有两个子节点
        将左子树最大节点/右子树最小节点覆盖节点的值，变成情况1,2
        */

       // 让cur指向前驱节点，转化成情况1，2
        if(cur->left_!=nullptr&&cur->right_!=nullptr)
        {
            parent = cur;
			Node* pre = cur->left_;
            while (pre->right_!=nullptr)
            {
                parent=pre;
                pre=pre->right_;
            }
            cur->data_=pre->data_;
            cur=pre;
        }

        // cur指向删除节点，parent指向其父节点，同一处理情况1或者2
        Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;//nullptr,情况2
		}

        if (parent == nullptr) // 特殊情况 表示删除的是根节点
		{
			root_ = child;
		}
        else
        {
            // 把待删除节点的孩子(nullptr或者不空)写入其父节点相应地址域中
            if(parent->left_==cur)
            {
                parent->left_=child;
            }
            else
            {
                parent->right_=child;
            }
        }
        delete cur;// 删除当前节点
    }

    // 非递归查询操作
    bool n_query(const T& val)
    {
        Node* cur = root_;
        while (cur!=nullptr)
        {
            if(cur->data_==val)
            {
                return true;
            }
            else if(comp_(cur->data_,val))
            {
                cur=cur->right_;
            }
            else
            {
                cur=cur->left_;
            }
        }
        return false;
    }

    // 递归插入操作
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}
    // 递归插入操作实现
	Node* insert(Node* node, const T& val)
    {
        if (node == nullptr)
		{
			// 递归结束，找到插入val的位置，生成新节点并返回其节点地址
			return new Node(val);
		}

        //先递归展开再回溯
        if(node->data_==val)
        {
            return node;
        }
        else if(comp_(node->data_,val))
        {
            node->right_=insert(node->right_,val);
        }
        else
        {
            node->left_=insert(node->left_,val);
        }
        return node;
    }

	// 递归删除操作
	void remove(const T& val)
	{
		root_ = remove(root_, val);
	}
    // 递归删除操作实现
	Node* remove(Node* node, const T& val)
    {
        if (node == nullptr)//找不到，结束递归
			return nullptr;

        if(node->data_==val)
        {
            // 情况3
            if(node->left_!=nullptr&&node->right_!=nullptr)
            {
                // 找前驱节点
                Node* pre = node->left_;
				while (pre->right_ != nullptr)
				{
					pre = pre->right_;
				}
                node->data_=pre->data_;
                // 通过递归直接删除前驱节点 
				node->left_ = remove(node->left_, pre->data_);
            }
            else//左右孩子一个为空或都为空
            {   
                if (node->left_ != nullptr)
				{
					// 删除节点以后，把非空的左孩子返回，回溯时更新其父节点地址域
					Node* left = node->left_;
					delete node;
					return left;
				}
                else if (node->right_ != nullptr)
				{
					// 删除节点以后，把非空的右孩子返回，回溯时更新其父节点地址域
					Node* right = node->right_;
					delete node;
					return right;
				}
                else
				{
					delete node;
					return nullptr; // 回溯时更新其父节点地址域为nullptr
				}
            }
        }
        else if(comp_(node->data_,val))
        {
            node->right_ = remove(node->right_, val);
        }
        else
        {
            node->left_ = remove(node->left_, val);
        }
        return node; // 把当前节点返回给父节点，更新父节点相应的地址域
    }

    // 递归查询操作
	bool query(const T& val)
	{
		return nullptr != query(root_, val);
	}
    // 递归查询操作实现
	Node* query(Node* node, const T& val)
    {
        if (node == nullptr)
			return nullptr;
        
        if (node->data_ == val)
		{
			return node;
		}
		else if (comp_(node->data_, val))
		{
			return query(node->right_, val);
		}
		else
		{
			return query(node->left_, val);
		}
    }

    // 非递归前序遍历操作
	void n_preOrder()
    {
        cout << "[非递归]前序遍历:";
		if (root_ == nullptr)
		{
			return;
		}

        stack<Node*> s;
        s.push(root_);
        while (!s.empty())
        {
            Node* top=s.top();
            s.pop();
            cout << top->data_ << " ";

            if(top->left_!=nullptr)
            {
                s.push(top->left_);
            }

            if(top->right_!=nullptr)
            {
                s.push(top->right_);
            }
        }
        cout<<endl;
    }

    // 非递归中序遍历操作
	void n_inOrder()
    {
        cout << "[非递归]中序遍历:";
		if (root_ == nullptr)
		{
			return;
		}

        stack<Node*> s;
        Node* cur = root_;

        while (!s.empty()||cur!=nullptr)
        {
            if(cur!=nullptr)
            {
                s.push(cur);
                cur=cur->left_;
            }
            else
            {
                Node* top = s.top();
				s.pop();
				cout << top->data_ << " ";
				cur = top->right_;
            }
        }
        cout<<endl;
    }

    // 非递归后序遍历操作
	void n_postOrder()
    {
        cout << "[非递归]后序遍历:";
		if (root_ == nullptr)
		{
			return;
		}
        stack<Node*> s1;
		stack<Node*> s2;
        s1.push(root_);
        while (!s1.empty())
        {
            Node* top = s1.top();
			s1.pop();

			s2.push(top); //放入根节点再放入右子树，最后放左子树
			if (top->left_ != nullptr)
			{
				s1.push(top->left_);
			}
			if (top->right_ != nullptr)
			{
				s1.push(top->right_);
			}
        }
        while (!s2.empty())
		{
			cout << s2.top()->data_ << " ";
			s2.pop();
		}
		cout << endl;
    }

    // 递归前序遍历操作
    void preOrder()
	{
		cout << "[递归]前序遍历:";
		preOrder(root_);
		cout << endl;
	}
    // 递归前序遍历的实现 VLR
	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " "; // 操作V
			preOrder(node->left_); // L
			preOrder(node->right_); // R
		}
	}

    // 递归中序遍历操作
	void inOrder()
	{
		cout << "[递归]中序遍历:";
		inOrder(root_);
		cout << endl;
	}
    // 递归中序遍历的实现
	void inOrder(Node* node)
	{
		if (node != nullptr)
		{
			inOrder(node->left_); // L
			cout << node->data_ << " "; // V
			inOrder(node->right_); // R
		}
	}

    // 递归后序遍历操作
	void postOrder()
	{
		cout << "[递归]后序遍历:";
		postOrder(root_);
		cout << endl;
	}
    // 递归后序遍历的实现 LRV
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_); // L
			postOrder(node->right_); // R
			cout << node->data_ << " "; // V
		}
	}

    // 非递归层序遍历操作
	void n_levelOrder()
	{
        cout << "[非递归]层序遍历:";
		if (root_ == nullptr)
		{
			return;
		}
        queue<Node*> que;
		que.push(root_);
		while (!que.empty())
		{
			Node* front = que.front();
			que.pop();

			cout << front->data_ << " ";
			if (front->left_ != nullptr)
			{
				que.push(front->left_);
			}
			if (front->right_ != nullptr)
			{
				que.push(front->right_);
			}
		}
		cout << endl;
    }
    // 递归层序遍历操作
	void levelOrder()
	{
		cout << "[递归]层序遍历:";
		int h = high(); // 树的层数
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i); // 递归调用树的层数次
		}
		cout << endl;
	}
    // 递归层序遍历的实现
	void levelOrder(Node* node, int i)
	{
        //节点随i大小移动
		if (node == nullptr)
			return;

		if (i == 0)
		{
			cout << node->data_ << " ";
			return;
		}
		levelOrder(node->left_, i - 1);
		levelOrder(node->right_, i - 1);
	}

    // 递归求二叉树层数
	int high()
	{
		return high(root_);
	}
    // 递归实现求二叉树层数 求以node为根节点的子树的高度并返回高度值
	int high(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = high(node->left_); // L
		int right = high(node->right_); // R
		return left > right ? left + 1 : right + 1; // V
	}

    // 递归求二叉树节点个数
	int number()
	{
		return number(root_);
	}
    // 递归求二叉树节点个数的实现 求以node为根节点的树的节点总数，并返回
	int number(Node* node)
	{
		if (node == nullptr)
			return 0;
		int left = number(node->left_);  // L
		int right = number(node->right_); // R
		return left + right + 1; // V
	}

    // 求满足区间的元素值[i, j]
	void findValues(vector<T>& vec, int i, int j)
	{
		findValues(root_, vec, i, j);
	}
    // 求满足区间的元素值[i, j]实现
	void findValues(Node* node, vector<T>& vec, int i, int j)
	{
        //中序遍历
        if(node!=nullptr)
        {
            //左子树的值都比data小，右子树的值都比data大，比较data与ij大小确定是否要访问子树
            if(node->data_>i)
            {
                findValues(node->left_, vec, i, j);
            }
            if (node->data_ >= i && node->data_ <= j)
			{
				vec.push_back(node->data_);
			}
            if (node->data_ < j)
			{
				findValues(node->right_, vec, i, j);
			}
        }

    }

    // 判断二叉树是否是BST树
	bool isBSTree()
	{
		return isBSTree(root_);
	}
    // 判断二叉树是否是BST树的实现
    bool isBSTree(Node* node)
    {
        if (node == nullptr)
		{
			return true;
		}
        if (node->left_ != nullptr && comp_(node->data_, node->left_->data_))
		{
            return false;
        }
        if (node->right_ != nullptr && comp_(node->right_->data_, node->data_))
		{
            return false;
        }

        if(!isBSTree(node->left_))// L 判断当前节点的左子树
        {
            return false;
        }
        if(!isBSTree(node->right_))// R 判断当前节点的右子树
        {
            return false;
        }
        return  true;
    }

    // 判断子树问题
    bool isChildTree(BSTree<T, Comp>& child)
	{
		if (child.root_ == nullptr)
		{
			return true;
		}

        // 在当前二叉树上找child的根节点
        Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == child.root_->data_)
			{
				break;
			}
			else if (comp_(cur->data_, child.root_->data_))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
        if (cur == nullptr)
		{
			return false;
		}
        return isChildTree(cur, child.root_);
    }
    // 判断子树问题实现
	bool isChildTree(Node* father, Node* child)
    {
        //递归结束条件
        if (father == nullptr && child == nullptr)
		{
			return true;
		}

        if (father == nullptr) //子树不能多
		{
			return false;
		}

		if (child == nullptr)//子树可以少
		{
			return true;
		}

        if (father->data_ != child->data_)
		{
			return false;
		}
        //一起移动
        return isChildTree(father->left_, child->left_)
			&& isChildTree(father->right_, child->right_);
    }

    // 最近公共祖先节点
	int getLCA(int val1, int val2)
	{
		Node* node = getLCA(root_, val1, val2);
		if (node == nullptr)
		{
			throw "no LCA!";
		}
		else
		{
			return node->data_;
		}
	}
    // 最近公共祖先节点实现
	Node* getLCA(Node* node, int val1, int val2)
	{
        if (node == nullptr)
		{
			return nullptr;
		}
        //val都大于node->data,最近公共祖先节点在右子树
        if (comp_(node->data_, val1) && comp_(node->data_, val2))
		{
			return getLCA(node->right_, val1, val2);
		}
		else if (comp_(val1, node->data_) && comp_(val2, node->data_))
		{
			return getLCA(node->left_, val1, val2);
		}
		else//一小一大，node就是最近公共祖先节点
		{
			return node;
		}

    }

    // 镜像翻转
	void mirror01()
	{
		mirror01(root_);
	}
    // 镜像翻转
	void mirror01(Node* node)
	{
        if (node == nullptr)
			return;
        
        Node* tmp = node->left_;
		node->left_ = node->right_;
		node->right_ = tmp;

        mirror01(node->left_);
		mirror01(node->right_);
    }

    // 镜像对称
	bool mirror02()
	{
		if (root_ == nullptr)
			return true;
		return mirror02(root_->left_, root_->right_);
	}
    // 镜像对称
	bool mirror02(Node* node1, Node* node2)
	{
        if (node1 == nullptr && node2 == nullptr)
		{
			return true;
		}
        //少节点/节点不对称
        if (node1 == nullptr || node2 == nullptr)
		{
			return false;
		}
        if (node1->data_ != node2->data_)
		{
			return false;
		}

        return mirror02(node1->left_, node2->right_)
			&& mirror02(node1->right_, node2->left_);
    }

    // 重建二叉树
	void rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		root_ = _rebuild(pre, i, j, in, m, n);
	}
    // 重建二叉树递归实现
	Node* _rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
        //前序遍历的数组pre的第一个节点是根节点，在中序遍历的数组in能计算子树的节点大小
        //从而在前序遍历VLR的数组左子树根节点和右子树根节点都能找到

        if (i > j || m > n)
		{
			return nullptr;
		}

        Node* node = new Node(pre[i]);//根节点
        for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k]) // 在中序遍历中找子树根节点的下标k,k-m为子树大小
			{
                /*
                在pre(VLR)i+1左子树的根，左子树的边界[i+1,i+(k-m)]，在in(LVR)，[m，k-1]左子树
                在in(LVR)同理
                划分后再找出它们的左右子树的根
                */
				node->left_ = _rebuild(pre, i + 1, i + (k - m), in, m, k - 1); // L
				node->right_ = _rebuild(pre, i + (k - m) + 1, j, in, k + 1, n); // R
				return node;
			}
		}
        return node;
    }

     // 判断平衡树 效率比较低
	bool isBalance(Node* node)
	{
        if (node == nullptr)
			return true;
        
		if (!isBalance(node->left_))  // L
			return false;
		if (!isBalance(node->right_))  // R
			return false;
        //high在递归回溯过程中只记录高度，node在递归过程中用high比较高度，效率比较低
        int left = high(node->left_);
		int right = high(node->right_);
		return abs(left - right) <= 1;
    }

    // 判断平衡树
	bool isBalance()
	{
		int l = 0;//节点的高度
		bool flag = true;//是否为平衡树
		isBalance02(root_, l, flag);
		return flag;
	}
    // 判断平衡树 效率高 
	int isBalance02(Node* node, int l, bool& flag)
	{
        //在递归过程中l记录了节点的高度值，在回溯过程用l判断平衡
        if (node == nullptr)
		{
			return l;
		}

        int left = isBalance02(node->left_, l + 1, flag); // L
		if (!flag)
			return left;
		int right = isBalance02(node->right_, l + 1, flag); // R
		if (!flag)
			return right;

        if (abs(left - right) > 1) // 节点失衡了
		{
			flag = false;
		}
		return max(left, right);
    }

    // 求中序倒数第K个节点
	int getVal(int k)
	{
		Node* node = getVal(root_, k);
		if (node == nullptr)
		{
			string err = "no No.";
			err += k;
			throw err;
		}
		else
		{
			return node->data_;
		}
	}
    // 求中序倒数第K个节点
    int i = 1;
	Node* getVal(Node* node, int k)
	{
        //先在右子树找，再在左子树找
		if (node == nullptr)
			return nullptr;

		Node* right = getVal(node->right_, k); // R
		if (right != nullptr)
			return right;
		// V
		if (i++ == k) // 在RVL的顺序下，找到正数第k个元素
		{
			return node;
		}
		return getVal(node->left_, k); // L
	}
private:
    Node* root_;
    Comp comp_;
};
