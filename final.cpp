#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
// tree node
struct tnode
{
    int data;
    struct tnode *left;
    struct tnode *right;
    struct tnode *prev;
    tnode()
    {
        data = 0;
        left = right = prev = NULL;
    }
    tnode(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
        prev = NULL;
    }
};
// tree
class tree
{
public:
    tnode *root;
    tnode *cur;
    tree()
    {
        root = NULL;
    }
    void make(vector<int> course, vector<int> pre) //
    {
        tnode *pnn;
        for (int i = 0, find = 0; i < course.size(); i++, find = 0)
        {
            if (root == NULL)
            {
                root = new tnode(course[i]);
            }
            else
            {
                pnn = new tnode(course[i]);

                check(root, pre[i], find, pnn);
            }
        }
    }
    /*
    check()
    When a course node has two children
    you will always assume that the child entered
    is the left child and the child entered second is the right child
    */
    void check(tnode *t, int v, int &f, tnode *pnn)
    {
        if (t == NULL || t->data == v)
        {

            if (t != NULL)
            {
                if (t->left == NULL)
                {
                    pnn->prev = t;
                    t->left = pnn;
                }
                else if (t->right == NULL)
                {
                    pnn->prev = t;
                    t->right = pnn;
                }
                f = 1;
            }
            return;
        }
        if (!f)
        {
            check(t->left, v, f, pnn);
            check(t->right, v, f, pnn);
        }
    }
    // ~tree(){
    //     ay7aga(root);
    // }
    // void ay7aga(tnode *t){
    //     if(t == NULL)
    //         return;
    //     ay7aga(t->left);
    //     ay7aga(t->right);
    //     delete t;
    // }
    void preOrder(tnode *p) // display the tree in pre order
    {
        if (p != NULL)
        {

            if (p->prev == NULL)
            {
                cout << p->data << "(0) ,";
            }
            else
            {
                cout << p->data << "(" << p->prev->data << ") ,";
            }

            preOrder(p->left);
            preOrder(p->right);
        }
    }
    tnode *search(tnode *r, int val) // search about code and return its node
    {
        if (r != NULL)
        {
            if (r->data == val)
            {
                cur = r;
                return cur;
            }
            else
            {
                search(r->left, val);
                search(r->right, val);
                return NULL;
            }
        }
        return cur;
    }

    void Processing(tnode *t, vector<int> l1, vector<int> l2, vector<string> ok, vector<string> no, vector<string> a, vector<string> w) // check if student can take the courses or not
    {
        for (int i = 0; i < l2.size(); i++)
        {
            search(root, l2[i]);

            for (int j = 0; j < l1.size(); j++)
            {
                if (cur->prev->data == l1[j])
                {
                    ok.push_back(w[i]);
                }
            }
        }
        for (int i = 0, f = 0; i < l2.size(); i++, f = 0)
        {
            for (int j = 0; j < ok.size(); j++)
            {
                if (w[i] == ok[j])
                {
                    f = 1;
                }
            }
            if (!f)
            {
                no.push_back(w[i]);
            }
        }
        if (ok.size() > 0)
        {
            cout << "the follwing courses are ok to to take :\n";
            for (int i = 0; i < ok.size(); i++)
            {
                cout << ok[i] << "\n";
            }
        }
        else if (ok.size() == 0)
            cout << "you can not enroll any course\n";

        if (no.size() > 0)
        {
            cout << "the follwing courses are not ok to to take :\n";
            for (int i = 0; i < no.size(); i++)
            {
                cout << no[i] << "\n";
            }
        }
        else if (no.size() == 0)
            cout << " you can enroll all courses\n";
    }
};

int main()
{

    vector<char> v;
    vector<int> v2;
    vector<int> courses;
    vector<int> prerequisites;
    vector<pair<int, int>> subjects;
    vector<string> alreadyStudied;
    vector<string> wantToStudy;
    vector<char> code1;
    vector<char> code2;
    vector<int> list1;
    vector<int> list2;
    vector<string> OkToTake;
    vector<string> CannotBeTaken;

    string myText, tmp;
    ifstream MyReadFile("final_project.txt");
    while (getline(MyReadFile, myText))
    {
        v.push_back(myText[0]);
        v.push_back(myText[1]);
        v.push_back(myText[2]);
        for (int i = 0; i < myText.size(); i++)
        {
            if (myText[i] == ',')
            {
                v.push_back(myText[i + 1]);
                v.push_back(myText[i + 2]);
                v.push_back(myText[i + 3]);
            }
        }
    }
    tmp = "";

    for (int i = 0; i < v.size() + 1; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            if (tmp.compare("Non") == 0)
            {
                v2.push_back(0);
            }
            else
            {
                v2.push_back(stoi(tmp));
            }
            tmp = "";
        }
        tmp += (char)v[i];
    }
    cout << "\n";
    for (int i = 0; i < v2.size(); i++)
    {
        if (i % 2 == 0)
        {
            courses.push_back(v2[i]);
        }
        else
        {
            prerequisites.push_back(v2[i]);
        }
    }
    v.clear();
    v2.clear();
    tree t;
    t.make(courses, prerequisites);
    t.preOrder(t.root);
    cout << endl;

    MyReadFile.close();
    int N;
    string st1, st2;
    cout << "Enter No. of courses that you already studied:" << endl;
    cin >> N;
    cout << "Enter the courses that you already studied:" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "Enter course " << i + 1 << " :";
        cin >> st1;
        alreadyStudied.push_back(st1);
        for (int j = 0; j < 3; j++)
        {
            code1.push_back(st1[j]);
        }
        st1 = "";
    }
    cout << "\n"
         << "*********************\n";
    cout << "Enter No. of courses that you want to study:" << endl;
    int N2;
    cin >> N2;
    cout << "Enter the courses that you want to study:" << endl;
    for (int i = 0; i < N2; i++)
    {
        cout << "Enter course " << i + 1 << " :";
        cin >> st2;
        wantToStudy.push_back(st2);
        for (int j = 0; j < 3; j++)
        {
            code2.push_back(st2[j]);
        }
        st2 = "";
    }
    string tmp2 = "";
    for (int j = 0; j <= code1.size(); j++)
    {
        if (!(j % 3) && j)
        {
            list1.push_back(stoi(tmp2));
            tmp2 = "";
        }
        tmp2 += (char)code1[j];
    }
    string tmp3 = "";
    for (int j = 0; j <= code2.size(); j++)
    {
        if (j % 3 == 0 && j != 0)
        {
            list2.push_back(stoi(tmp3));
            tmp3 = "";
        }
        tmp3 += (char)code2[j];
    }

    t.Processing(t.root, list1, list2, OkToTake, CannotBeTaken, alreadyStudied, wantToStudy);
    return 0;
}
