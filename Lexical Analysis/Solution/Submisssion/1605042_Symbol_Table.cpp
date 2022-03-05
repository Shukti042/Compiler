#include<bits/stdc++.h>
using namespace std;
int scopeid,hashid;
ofstream out;
class SymbolInfo{
    string name,type;
public:
    SymbolInfo * next;
    int position;
    SymbolInfo()
    {
        name="";
        type="";
        next=0;
        position=0;
    }
    SymbolInfo(string n,string t)
    {
        name=n;
        type=t;
        next=0;
        position=0;
    }
    string getName()
    {
        return name;
    }
    string getType()
    {
        return type;
    }
    void setName(string n)
    {
        name=n;
    }
    void setType(string t)
    {
        type=t;
    }
};
class ScopeTable{
public:
    int len,id;
    ScopeTable *parentScope;
    SymbolInfo **arr;
    ScopeTable(int sz)
    {
        len=sz;
        arr=new SymbolInfo*[sz];
        for(int i=0;i<sz;i++)
        {
            arr[i]=0;
        }
        parentScope=0;
        id=1;
    }
    void setID()
    {
        if(parentScope==0)
        {
            id=1;
        }
        else
        {
            id=parentScope->id+1;
        }
    }
    int Hash(string s)
    {
        long h = 37;
        for(int i=0;i<s.length();i++)
        {
            h = (h * 54059) ^ (s[0] * 76963);
        }
        return abs(h%len);
    }
    bool Insert(string n,string t)
    {
        int h=Hash(n);
        SymbolInfo *temp=arr[h];
        if(temp==0)
        {
            arr[h]=new SymbolInfo(n,t);
            Print();
            return true;
        }
        while(temp!=0)
        {
            if(temp->getName()==n)
                return false;
            temp=temp->next;
        }
        temp=arr[h];
        if(temp!=0)
        {
            while(temp->next!=0)
            {
                temp=temp->next;
            }
        }

        SymbolInfo *newSymbol=new SymbolInfo(n,t);
        newSymbol->position=temp->position+1;
        temp->next=newSymbol;
        Print();
        return true;
    }
    SymbolInfo* Lookup(string n)
    {
        int h=Hash(n);
        SymbolInfo *temp=arr[h];
        if(temp==0)
            return 0;
        while(temp!=0)
        {
            if(temp->getName()==n)
                return temp;
            temp=temp->next;
        }
        return 0;

    }
    bool Delete(string n)
    {
        int h=Hash(n);
        SymbolInfo *temp=arr[h];
        SymbolInfo *temp2=0,*temp3;
        if(temp==0)
        {
            return false;
        }
        while(temp!=0)
        {
            if(temp->getName()==n)
            {
                if(temp2==0)
                {
                    arr[h]=temp->next;
                    delete temp;
                    temp3=arr[h];
                    while(temp3!=0)
                    {
                        temp3->position--;
                    }
                    return true;
                }
                else
                {
                    temp2->next=temp->next;
                    delete temp;
                    temp3= temp2->next;
                    while(temp3!=0)
                    {
                        temp3->position--;
                    }
                    return true;
                }
            }
            temp2=temp;
            temp=temp->next;
        }
        return false;
    }
    void Print()
    {
        out.open("1605042_log.txt",ofstream::app);
        out<<"Scope Table: "<<id<<endl;
        for(int i=0;i<len;i++)
        {
            SymbolInfo *temp=arr[i];
            if(temp==0)
            {
                continue;
            }
            out<<i<<"-->";
            while(temp!=0)
            {
                out<<" <"<<temp->getName()<<" , "<<temp->getType()<<"> ";
                temp=temp->next;
            }
            out<<endl;
        }
        out<<endl;
        out.close();
    }
    ~ScopeTable()
    {
        delete[] arr;
    }
};
class SymbolTable{
public:
    ScopeTable *currentScope;
    SymbolTable(int n)
    {
        EnterScope(n);
    }
    void EnterScope(int n)
    {
        if(currentScope==0||true)
        {
            currentScope=new ScopeTable(n);
            return;
        }
        ScopeTable *temp=currentScope;
        currentScope=new ScopeTable(n);
        currentScope->parentScope=temp;
        currentScope->setID();

    }
    void ExitScope()
    {
        if(currentScope!=0)
        {
            ScopeTable *temp=currentScope;
            currentScope=currentScope->parentScope;
            delete temp;
        }
    }
    bool Insert(string n,string t)
    {
        //cout<<"I was called";
         return currentScope->Insert(n,t);
    }
    bool Remove(string n)
    {
        if(currentScope!=0)
        {
            return currentScope->Delete(n);
        }
    }
    SymbolInfo* Lookup(string n)
    {
        ScopeTable *t=currentScope;
        if(t!=0)
        {
            scopeid=t->id;
            hashid=t->Hash(n);
        }
        SymbolInfo *temp=0;
        while(t!=0)
        {
           temp=t->Lookup(n);
           if(temp!=0)
            return temp;
           t=t->parentScope;
           if(t!=0)
           {
                scopeid=t->id;
                hashid=t->Hash(n);
           }

        }
        return 0;
    }
    void PrintCurrent()
    {
        if(currentScope!=0)
        {
            currentScope->Print();
        }
    }
    void PrintAll()
    {
        ScopeTable *t=currentScope;
        while(t!=0)
        {
            t->Print();
            t=t->parentScope;
        }
    }
};
/*main()
{
    SymbolTable st(11);
    st.Insert("Hello","World");
    st.Insert("i","know");
}*/
