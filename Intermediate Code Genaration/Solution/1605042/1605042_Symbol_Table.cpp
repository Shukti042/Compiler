#include<bits/stdc++.h>
using namespace std;
class ScopeID
{
    public:
    int sequence;
};
class SymbolInfo{
    string name="",type="";
public:
    SymbolInfo * next;
    int position;
    string data_type;
    string return_type;
    vector <string> parameter_list;
    vector <string> argumentList;
    vector <string> parameterNames;
    vector <string> argumentNames;
    vector <string> variableNames;
    int array_size;
    bool is_array=false;
    bool is_defined=false;
    bool is_function=false;
    string Symbol="";
    string code="";
    SymbolInfo()
    {
        name="";
        type="";
        next=0;
        position=0;
        array_size=0;
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
    void setID(int seq)
    {
      
            id=seq;
        
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
        //extern FILE* fp2;
    
        //fprintf(fp2,"Scope Table: %d\n",id);
        for(int i=0;i<len;i++)
        {
            SymbolInfo *temp=arr[i];
            if(temp==0)
            {
                continue;
            }
            //fprintf(fp2,"%d-->",i);
            while(temp!=0)
            {
               // fprintf(fp2," <%s , %s>",temp->getName().c_str(),temp->getType().c_str());
                temp=temp->next;
            }
            //fprintf(fp2,"\n");
        }
        //fprintf(fp2,"\n");
    }
    ~ScopeTable()
    {
        delete[] arr;
    }
};
class SymbolTable{
public:
    ScopeTable *currentScope;
    ScopeID scopeid;
    SymbolTable(int n)
    {
        scopeid.sequence=1;
        EnterScope(n);
    }
    void EnterScope(int n)
    {
        //extern FILE* fp2;
        if(currentScope==0)
        {
            currentScope=new ScopeTable(n);
            currentScope->setID(scopeid.sequence);
            scopeid.sequence++;
            return;
        }
        ScopeTable *temp=currentScope;
        currentScope=new ScopeTable(n);
        currentScope->parentScope=temp;
        currentScope->setID(scopeid.sequence);
        scopeid.sequence++;
        //fprintf(fp2,"Scope Table with id %d created\n\n",currentScope->id);

    }
    void ExitScope()
    {
        //extern FILE* fp2;
        if(currentScope!=0)
        {
            PrintAll();
            //fprintf(fp2,"Scope Table with id %d removed\n\n",currentScope->id);
            ScopeTable *temp=currentScope;
            currentScope=currentScope->parentScope;
            delete temp;
        }
    }
    bool Insert(string n,string t)
    {
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
        SymbolInfo *temp=0;
        while(t!=0)
        {
           temp=t->Lookup(n);
           if(temp!=0)
            return temp;
           t=t->parentScope;

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
