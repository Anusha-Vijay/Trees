#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;



class Node{
public:
    int value;
    Node* left;
    Node* right;
public: Node(int val): value(val),left(nullptr),right(nullptr){}
};

class Tree{
    Node* root;

    void printInOrderRecurrsive(Node* root){
        if(root == nullptr)
            return;
        printInOrderRecurrsive(root->left);
        cout<<"\t"<<root->value;
        printInOrderRecurrsive(root->right);
    }

    void printPostOrderRecurrsive(Node* root){
        if(root == nullptr)
            return;
        printInOrderRecurrsive(root->left);
        printInOrderRecurrsive(root->right);
        cout<<"\t"<<root->value;
    }
    void printPreOrderRecurrsive(Node* root){
        if(root == nullptr)
            return;
        cout<<"\t"<<root->value;
        printInOrderRecurrsive(root->left);
        printInOrderRecurrsive(root->right);
    }
    Node* insertRecurssive(Node* root,int val){
        if(root == nullptr) {
            root = new Node(val);
            return root;
        }
        else{
            if(val>root->value)
                root->right=insertRecurssive(root->right,val);
            else
                root->left=insertRecurssive(root->left,val);
        }
        return root;
    }

    bool isBST(Node* root){
        if(root== nullptr)
            return true;
        if(root->left!= nullptr){
            if(root->value>root->left->value)
                isBST(root->left);
            else
                return false;
        }
        if(root->right!= nullptr){
            if(root->value<root->right->value)
                isBST(root->right);
            else
                return false;
        }
        return true;
    }

    bool hasPath(Node* root, int path,vector<int> pathvec){
        if(path==0){
            for(int i=0;i<pathvec.size();i++)
                cout<<"-->"<<pathvec[i];
            cout<<"\n";
            return true;
        }
        if(root!= nullptr)
        {
            pathvec.push_back(root->value);
            int sum=path-root->value;
            return ((hasPath(root->left,sum,pathvec))|| hasPath(root->right,sum,pathvec));
        }

    }

    int maxDepth(Node* root){
        if(root == nullptr)
            return 0;
        else
        return (max(maxDepth(root->left),maxDepth(root->right))+1);
    }

    vector<int> hasCommonAncestor(int node,vector<int> ancestor,Node* root){
        if(node == root->value){
            cout<<"\n"<<"Printing!!\n";
            ancestor.push_back(root->value);
            for(int i=0;i<ancestor.size();i++){
                cout<<ancestor[i]<<" , ";
            }
            return ancestor;
        }

        if(node>root->value && root->right!= nullptr){
            ancestor.push_back(root->value);
            hasCommonAncestor(node,ancestor,root->right);
        }

        if(node<root->value && root->left!= nullptr){
            ancestor.push_back(root->value);
            hasCommonAncestor(node,ancestor,root->left);
        }

        return ancestor;
    }

    int lca(int nodeA,int nodeB,Node* root){

        while (root!= nullptr){
            if(root->value>nodeA && root->value>nodeB && root->left!= nullptr)
                root=root->left;
            else if(root->value<nodeA && root->value<nodeB && root->right!= nullptr)
                root=root->right;
            else
                return root->value;
        }
    }

    bool equalNode(Node*t, Node* s){
        if(t== nullptr && s== nullptr)
            return true;
        if(t== nullptr || s== nullptr)
            return false;

        return(t->value==s->value && equalNode(t->left,s->left) && equalNode(t->right,s->right));

    }

    bool subTree(Node* t, Node* s){
        return  s!= nullptr && ( equalNode(t,s) || subTree(t->left,s) || subTree(t->right,s));
    }

    void mirror(Node* root){
        if(root== nullptr)
            return;
        Node* temp=root->right;
        root->right=root->left;
        root->left=temp;
    }

    void printInOrderIterative(Node* root){
        Node* ptr=root;
        stack<Node*> stack;
        bool flag= false;
        while (!flag){
            if(ptr!= nullptr){
                stack.push(ptr);
                ptr=ptr->left;
            }
            else {
                if (!stack.empty()) {
                    cout << stack.top()->value<<" ";
                    ptr = stack.top()->right;
                    stack.pop();
                } else
                flag= true;
            }
        }
    }

public:
    Tree():root(nullptr){};

    Node *getRoot() const;

    void insertIterative(int value);   //1.done
    int minValue(); //2.done
    int maxDepth(); //3.done
    void printLevelOrder(); //4.done
    void printPostOrderRecurrsive(); //5.done
    void printPreOrderRecurrsive(); //6.done
    void printInOrderRecurrsive(); //7.done
    void printPath(int); //8.done
    bool isBST(); //9.done
    bool lowestCommonAncestor(int nodeA, int nodeB); //10. Done
    void printTree(); //11.done
    void insertRecurssive(int val); //12.done
    bool hasPath(int path);//13. done
    bool subTree(Node* ); //14. Done
    void mirror(); //15. Done


    void printInOrderIterative(); //16.
    void reverseLevelOrderTraversal(); //17.
};

// [15/17]

void Tree::mirror() {
    mirror(root);
    printTree();
}


bool Tree::subTree(Node *sroot) {
    return subTree(this->root,sroot);

}

bool Tree::lowestCommonAncestor(int nodeA, int nodeB) {
    vector<int> ancestorA,ancestorB;
    ancestorA=hasCommonAncestor(nodeA,ancestorA,root);
    ancestorB=hasCommonAncestor(nodeB,ancestorB,root);
    cout<<"\nLowest Common Ancestor:\n"<<lca(nodeA,nodeB,root);
}

int Tree::minValue() {
    Node* ptr=root;
    while(ptr->left!= nullptr){
        ptr=ptr->left;
    }
    return ptr->value;
}
bool Tree::isBST() {
    cout << isBST(root);
}

bool Tree::hasPath(int path){
    vector<int> vect;
    hasPath(root,path,vect);
}

void Tree::insertRecurssive(int val){
    root=insertRecurssive(root,val);
}

void Tree::insertIterative(int value){
    if(root == nullptr){
        root=new Node(value);
        return;
    }
    Node* ptr=root;
    while(ptr!= nullptr) {
        if (value > ptr->value) {
            if(ptr->right== nullptr) {
                ptr->right = new Node(value);
                return;
            }
            ptr=ptr->right;
        }
        else{
            if(ptr->left== nullptr){
                ptr->left=new Node(value);
                return;
            }
            ptr=ptr->left;
        }
        }
}

void Tree::printInOrderRecurrsive(){
    printInOrderRecurrsive(root);
}

void Tree::printPostOrderRecurrsive() {
    printPostOrderRecurrsive(root);
}

void Tree::printPreOrderRecurrsive() {
    printPreOrderRecurrsive(root);
}

void Tree::printLevelOrder(){
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        cout<<q.front()->value<<"\t";
        if(q.front()->left!= nullptr)
            q.push(q.front()->left);
        if(q.front()->right!= nullptr)
            q.push(q.front()->right);
        q.pop();
    }
}

int Tree::maxDepth() {
    return maxDepth(root);
}

void Tree::printInOrderIterative() {
    printInOrderIterative(root);
}

void Tree::printTree() {
    queue<Node*> q1;
    queue<Node*>q2;
    q1.push(root);

    while(!q1.empty() || !q2.empty()){
        while (!q1.empty()) {
            if(q1.front()->left!= nullptr){
                q2.push(q1.front()->left);
            }

            if(q1.front()->right!= nullptr){
                q2.push(q1.front()->right);
            }
            cout<<" "<<q1.front()->value;
            q1.pop();

        }
        cout<<"\n";
        while (!q2.empty()){
            if(q2.front()->left!= nullptr){
                q1.push(q2.front()->left);
            }

            if(q2.front()->right!= nullptr){
                q1.push(q2.front()->right);
            }

            cout<<" "<<q2.front()->value;
            q2.pop();
        }
        cout<<"\n";
    }
}

Node *Tree::getRoot() const {
    return root;
}

int main() {
    Tree t;
    t.insertIterative(5);
    t.insertIterative(6);
    t.insertIterative(2);
    t.insertIterative(10);
    t.insertIterative(3);
    t.insertIterative(1);

    Tree s;
    s.insertRecurssive(2);
    s.insertRecurssive(1);
    s.insertRecurssive(3);

    cout<<"\nPrinting Tree!\n";
    t.printTree();
    cout<<"\nPrinting Tree!\n";
    s.printTree();
    cout<<"\nIs s a subtree?\n"<<t.subTree(s.getRoot());
    t.printInOrderRecurrsive();
    cout<<"\n Pre Order:\n";
    t.printPreOrderRecurrsive();
    cout<<"\n Post Order \n";
    t.printPostOrderRecurrsive();
    cout<<"\n Level Order\n";
    t.printLevelOrder();
    cout<<"\nPrinting Tree!\n";
    t.printTree();
    cout<<"\nIs Binary Tree?:";
    t.isBST();
    cout<<"\nHas Path:";
    cout<<t.hasPath(28);
    cout<<"\n Minimum value of the tree is:"<<t.minValue();
    cout<<"\n Max Depth of the Tree is:"<<t.maxDepth();
    cout<<"\nHas common path!";
    t.lowestCommonAncestor(10,7);
    cout<<"\nBefore Mirror";
    t.printTree();
    cout<<"\n";
    cout<<"\nAfter Mirror\n";
    t.mirror();
    t.mirror();
    cout<<"\n Iterative Solution!:";
    t.printInOrderIterative();
    return 0;
}
