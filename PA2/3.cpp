#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

struct node
{
    int val;
    struct node* left;
    struct node* right;
};
//function to insert new node
void insertbst(struct node* root,int x)
{
    struct node* root1=root;
    while(root1!=nullptr && root1->val!=x)
    {
        if(root1->val>x && root1->left!=nullptr) root1=root1->left;
        else if(root1->val>x && root1->left==nullptr) 
        {
                struct node* temp=new node;
                temp->val=x;
                temp->left=nullptr;
                temp->right=nullptr;
                root1->left=temp;
                return;
        }
        else if(root1->val<x && root1->right!=nullptr) root1=root1->right;
        else if(root1->val<x && root1->right==nullptr)
        {
                struct node* temp=new node;
                temp->val=x;
                temp->left=nullptr;
                temp->right=nullptr;
                root1->right=temp;
                return;
        }
    }
    //key of this value already exists.
    if(root1!=nullptr) return;
}
//function to find the smallest node greater than the current node
struct node* findinordersuccessor(struct node* root1)
{
    struct node* root2=root1->right;
    while(root2->left!=nullptr) root2=root2->left;

    return root2;

}
//function deletes a node from the bst
struct node* deletebst(struct node* root, int x)
{
    if(root==nullptr) return root;
    else
    {
        if(root->val>x)
        {
            root->left=deletebst(root->left,x);
            return root;
        }
        else if(root->val<x)
        {
            root->right=deletebst(root->right,x);
            return root;
        }
        else
        {
            //if node has no children, just set it to nullptr
            if(root->left==nullptr && root->right==nullptr) return nullptr;
            //if node has 2 children, replace the node with its child
            else if(root->left!=nullptr && root->right==nullptr)
            {
                return root->left;
            }
            else if(root->right!=nullptr && root->left==nullptr)
            {
                return root->right;
            }
            //difficult case, need to replace current node with its inorder successor
            else
            {
                struct node* root1=findinordersuccessor(root);
                root->val=root1->val;
                root->right=deletebst(root->right, root1->val);
                return root;
            }
        }
    }
}
//function looks for a node in the bst
void searchbst(struct node* root, int x)
{
    struct node* root1=root;
    while(root1!=nullptr && root1->val!=x)
    {
        if(root1->val>x) root1=root1->left;
        else if(root1->val<x) root1=root1->right;
    }
    if(root1==nullptr) cout<<"NO";
    else cout<<"YES";
    return;
}

int main() 
{
    int n;
    cin>>n;
    struct node* root=nullptr;
    for(int i=0;i<n;i++)
    {
        char c;
        cin>>c;
        switch(c)
        {
            case 'B':
            {
                int num;
                cin>>num;
                if(root==nullptr)
                {
                    root=new node;
                    root->val=num;
                    root->left=nullptr;
                    root->right=nullptr;
                }
                else insertbst(root,num);
                break;
            }
            case 'S':
            {
                int num;
                cin>>num;
                root=deletebst(root,num);
                break;
            }
            case 'R':
            {
                int num;
                cin>>num;
                searchbst(root,num);
                cout<<endl;
                break;
            }
        };
    }   
    return 0;
}