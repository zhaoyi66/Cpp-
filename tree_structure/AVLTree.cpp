#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

// AVL树   二叉平衡搜索树的实现
template<typename T>
class AVLTree
{
public:
    // AVL的初始化
	AVLTree() :root_(nullptr) {}
    // AVL树的插入操作接口
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}
	// 删除操作接口
	void remove(const T& val)
	{
		root_ = remove(root_, val);
	}

private:
    // 定义AVL树节点类型
    struct Node
	{
		Node(T data = T())
			:data_(data)
			, left_(nullptr)
			, right_(nullptr)
			, height_(1)
		{}
		T data_;
		Node* left_;
		Node* right_;
		int height_; // 记录节点的高度值
	};

    // 返回节点的高度值
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}

    // 左孩子node的左子树太高 右旋转操作 以参数node为轴做右旋转操作，并把新的根节点返回
	Node* rightRotate(Node* node)
	{
        //节点旋转
        Node* child=node->left_;
        node->left_=child->right_;
        child->right_=node;
        // 高度更新
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
        //返回旋转后的子树新的根节点
        return child;
    }

    // 右孩子node的右子树太高 左旋转操作 以参数node为轴做左旋转操作，并把新的根节点返回
	Node* leftRotate(Node* node)
	{
		// 节点旋转
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		// 高度更新
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		// 返回旋转后的子树新的根节点
		return child;
	}

    // 左孩子child的右子树太高 左平衡操作 以参数node为轴做左-右旋转操作，并把新的根节点返回
	Node* leftBalance(Node* node)
	{
		node->left_ = leftRotate(node->left_);
		return rightRotate(node);
	}
    // 右孩子child的左子树太高 右平衡操作 以参数node为轴做右-左旋转操作，并把新的根节点返回
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->right_);
		return leftRotate(node);
	}

    // 插入操作实现
	Node* insert(Node* node, const T& val)
	{
        //BST的递归插入，但是要在回溯时判断节点平衡并且更新各个节点高度

        if (node == nullptr) // 递归结束，找到插入的位置了
		{
			return new Node(val);
		}

        if (node->data_ > val)
		{
			node->left_ = insert(node->left_, val);
			// 在回溯时判断节点是否失衡  node的左子树太高 node失衡了
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					// 节点失衡，由于左孩子的左子树太高
					node = rightRotate(node);
				}
				else
				{
					// 节点失衡，由于左孩子的右子树太高
					node = leftBalance(node);
				}
            }
		}
        else if (node->data_ < val)
		{
			node->right_ = insert(node->right_, val);
			// 在回溯时判断节点是否失衡  node的右子树太高 node失衡了
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					// 节点失衡，由于右孩子的右子树太高
					node = leftRotate(node);
				}
				else
				{
					// 节点失衡，由于右孩子的左子树太高
					node = rightBalance(node);
				}
			}
		}
		else
		{
			; // 找到相同节点了，不用再往下递归了，直接向上回溯
		}
	    
        //回溯更新节点高度
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node;
    }

    // 删除操作实现
	Node* remove(Node* node, const T& val)
	{
        //BST的递归删除，注意要删除节点的三种情况。多了回溯过程判断平衡和更新高度

        if (node == nullptr)//没找到
		{
			return nullptr;
		}
        if(node->data_>val)
        {
            node->left_ = remove(node->left_, val);
            // 左子树删除节点，可能造成右子树太高
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					// 右孩子的右子树太高
					node = leftRotate(node);
				}
				else
				{
					// 右孩子的左子树太高
					node = rightBalance(node);
				}
			}
        }
        else if(node->data_<val)
        {
            node->right_ = remove(node->right_, val);
			// 右子树删除节点，可能导致左子树太高
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					// 左孩子的左子树太高
					node = rightRotate(node);
				}
				else
				{
					// 左孩子的右子树太高
					node = leftBalance(node);
				}
			}
        }
        else
        {
            // 找到了 先处理有两个孩子的节点删除情况
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				// 为了避免删除前驱或者后继节点造成节点失衡，谁高删除谁
				if (height(node->left_) >= height(node->right_))
				{
					// 删前驱
					Node* pre = node->left_;
					while (pre->right_ != nullptr)
						pre = pre->right_;
					node->data_ = pre->data_;
					node->left_ = remove(node->left_, pre->data_); // 删前驱节点
				}
				else
				{
					// 删后继
					Node* post = node->right_;
					while (post->left_ != nullptr)
						post = post->left_;
					node->data_ = post->data_;
					node->right_ = remove(node->right_, post->data_); // 删除后继节点
				}
			}
            else // 删除节点，最多有一个孩子(1/0)
			{
				if (node->left_ != nullptr)
				{
					Node* left = node->left_;
					delete node;
					return left;
				}
				else if (node->right_ != nullptr)
				{
					Node* right = node->right_;
					delete node;
					return right;
				}
				else
				{
					return nullptr;
				}
			}
        }

        // 更新节点高度
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node; // 回溯过程中，把当前节点给父节点返回
    }
    // 指向根节点
	Node* root_;
};
int main()
{
	AVLTree<int> avl;
	for (int i = 1; i <= 10; i++)
	{
		avl.insert(i);
	}

	avl.remove(9);
	avl.remove(10);
	avl.remove(6);
	avl.remove(1);
	avl.remove(2);
	avl.remove(3);

	return 0;
}
