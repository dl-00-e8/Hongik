#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <queue>

using namespace std;

template <class K, class E> class BST; //전방선언
template <class K, class E>

class TreeNode {
	friend class BST<K, E>;
	TreeNode(K ky, E el, TreeNode<K, E>* left = 0, TreeNode<K, E>* right = 0)
		: key(ky), element(el), leftChild(left), rightChild(right) { }
private:
	TreeNode<K, E>* leftChild;
	K key;
	E element;
	TreeNode<K, E>* rightChild;
};

template <class K, class E>
class BST {
public:
	BST() { root = 0; } // empty BST
	void Insert(K& newkey, E& el) { Insert(root, newkey, el); }
	void Preorder() { Preorder(root); }
	void Inorder() { Inorder(root); }
	void Postorder() { Postorder(root); }
	void Levelorder();
	bool Find(const K&, E&);
	void Delete(K& oldkey) { Delete(root, oldkey); }
private: // helper 함수들
	void Visit(TreeNode<K, E>*);
	void Insert(TreeNode<K, E>*&, K&, E&);
	void Preorder(TreeNode<K, E>*);
	void Inorder(TreeNode<K, E>*);
	void Postorder(TreeNode<K, E>*);
	void Delete(TreeNode<K, E>*&, K&);
	TreeNode<K, E>* root;
};

template <class K, class E>
void BST<K, E>::Visit(TreeNode<K, E>* ptr)
{
	cout << ptr->key << ":" << ptr->element << " ";
}

template <class K, class E>
void BST<K, E>::Insert(TreeNode<K, E>*& ptr, K& newkey, E& el) { //Insert의 helper함수
	if (ptr == 0) ptr = new TreeNode<K, E>(newkey, el);
	else if (newkey < ptr->key) Insert(ptr->leftChild, newkey, el);
	else if (newkey > ptr->key) Insert(ptr->rightChild, newkey, el);
	else ptr->element = el; // Update element
}

template <class K, class E>
void BST<K, E>::Preorder(TreeNode<K, E>* currentNode) { //Preorder의helper함수
	if (currentNode) {
		Visit(currentNode);
		Preorder(currentNode->leftChild);
		Preorder(currentNode->rightChild);
	}
}

template <class K, class E>
void BST<K, E>::Inorder(TreeNode<K, E>* currentNode) { //Inorder의helper함수
	if (currentNode) {
		Inorder(currentNode->leftChild);
		Visit(currentNode);
		Inorder(currentNode->rightChild);
	}
}

template <class K, class E>
void BST<K, E>::Postorder(TreeNode<K, E>* currentNode) { //Postorder의helper함수
	if (currentNode) {
		Postorder(currentNode->leftChild);
		Postorder(currentNode->rightChild);
		Visit(currentNode);

	}
}

template <class K, class E>
void BST<K, E>::Levelorder() { //Postorder의helper함수
	queue<TreeNode<K, E>*> q;
	TreeNode<K, E>* currentNode = root;

	while (currentNode) {
		Visit(currentNode);

		if (currentNode->leftChild) {
			q.push(currentNode->leftChild);
		}
		if (currentNode->rightChild) {
			q.push(currentNode->rightChild);
		}

		if (q.empty()) {
			return;
		}

		currentNode = q.front();
		q.pop();
	}
}

template <class K, class E>
bool BST<K, E>::Find(const K& k, E& e)
{
	TreeNode<K, E>* ptr = root;
	// root k key 부터 시작해서 반복해서 와 같은 를 갖고 있는 노드를 찾아 element e . 찾은 노드의 를 로 전달하여 반환한다
	// k e true, false . 를 갖고 있는 를 찾았으면 못 찾았으면 를 반환한다
	while (ptr) {
		if (k < ptr->key) {
			ptr = ptr->leftChild;
		}
		else if (k > ptr->key) {
			ptr = ptr->rightChild;
		}
		else {
			e = ptr->element;
			return true;
		}
	}

	return false;
}

template <class K, class E>
void BST<K, E>::Delete(TreeNode<K, E>*& ptr, K& oldkey)
{
	//ptr를 루트로 하는 트리에서 oldkey가 키인 노드를 찾아 삭제하기. 
	TreeNode<K, E>* tmpptr; TreeNode<K, E>* tmpparentptr;
	if (ptr == 0) return; // NULL , return
	if (oldkey < ptr->key) //left subtree에서 oldkey 찾아 삭제하기
		Delete(ptr->leftChild, oldkey);
	else if (oldkey > ptr->key) //right subtree에서 oldkey 찾아 삭제하기
		Delete(ptr->rightChild, oldkey);
	else //oldkey갖고 있는 삭제할 노드 ptr을 찾은 경우 : 
	// Children . 중 적당한 노드를 찾아 현재 노드를 대체한다
		if (!ptr->leftChild && !ptr->rightChild) // Children이 없다면
		{
			delete ptr; 
			ptr = 0; 
			
			return;
		}
		else if (ptr->leftChild && !ptr->rightChild) // 삭제할 노드가 왼쪽 만 갖고 있는 경우
			// child ptr ptr 왼쪽 로 을 대체하고 현재 이 가리키는 노드 삭제
		{
			tmpptr = ptr; 
			ptr = ptr->leftChild; 
			
			delete tmpptr; 
			
			return; }
		else if (!ptr->leftChild && ptr->rightChild) // 삭제할 노드가 오른쪽 만 있다면
		{ tmpptr = ptr; ptr = ptr->rightChild; delete tmpptr; return; }
		else { // child : 왼쪽 및 오른쪽 모두 있는 경우
		// rc ‘ ’ 루트가 인 우측 트리에서 제일 작은 노드 찾자
			TreeNode<K, E>* rc = ptr->rightChild; // rc가 루트인 subtree
			
			tmpparentptr = ptr;
			
			if (!rc->leftChild) // rc가 왼쪽 Child가 없으면 rc가 그 노드!
			// rc노드의 key/element/rightChild 정보를 ptr노드로 옮기고 rc노드 삭제(즉 delete rc)
			{
				ptr->key = rc->key;
				ptr->element = rc->element;
				ptr->rightChild = rc->rightChild;
				
				delete rc;
				
				return;
			}
			else 
			// 왼쪽 Child의 끝까지 내려가 가장 작은 키를 갖는 노드를 찾는다.
			// 그 노드의 key/element를 ptr노드로 옮기고, 그 노드의 rightChild를 그 노드의 parent의 leftChild로 저장한 다음에 그 노드를 삭제
			{
				while (rc->leftChild) {
					tmpparentptr = rc;
					rc = rc->leftChild;
				}
				
				ptr->key = rc->key;
				ptr->element = rc->element;
				tmpparentptr->leftChild = rc->rightChild;

				delete rc;

				return;
			}
		}
}

#endif