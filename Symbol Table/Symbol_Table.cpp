#include<bits/stdc++.h>
using namespace std;
ifstream in;
ofstream out;
int scopeid,hashid;
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
        out<<"Scope Table: "<<id<<endl;
        for(int i=0;i<len;i++)
        {
            out<<i<<"-->";
            SymbolInfo *temp=arr[i];
            while(temp!=0)
            {
                out<<" <"<<temp->getName()<<" , "<<temp->getType()<<"> ";
                temp=temp->next;
            }
            out<<endl;
        }
        out<<endl;
    }
    ~ScopeTable()
    {
        delete[] arr;
    }
};
class SymbolTable{
public:
    ScopeTable *currentScope;
    SymbolTable()
    {
        currentScope=0;
    }
    void EnterScope(int n)
    {
        if(currentScope==0)
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
        if(currentScope!=0)
        {
            return currentScope->Insert(n,t);
        }
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
main()
{
    /*SymbolInfo *s=new SymbolInfo("Hello","World");
    SymbolInfo *t=new SymbolInfo("Hellot","World");
    s->next=t;
    cout<<s->next->getName();*/
    /*ScopeTable *s=new ScopeTable(7);
    cout<<s->Insert("hello","oo")<<endl;
    cout<<s->Insert("Hello","oop")<<endl;
    s->Print();
    SymbolInfo *s2 = s->Lookup("Hello");
    cout<<s2->getType()<<endl;
    cout<<s->Delete("hello")<<endl;
    cout<<s->Insert("hello","oop")<<endl;
    SymbolInfo *s1 = s->Lookup("hello");
    cout<<s1->getType()<<endl;
    s->Print();
    delete s;*/

     /*SymbolTable *st=new SymbolTable();
    st->EnterScope(7);
    st->Insert("hello","oo");
    st->Insert("world","oop");
    st->EnterScope(7);
    st->Insert("hello","oop");
    cout<<st->Lookup("hello")->getType()<<endl;
    st->PrintAll();*/
    SymbolTable *st=new SymbolTable();
    SymbolInfo *si;
    bool flag;
    in.open ("input.txt");
    out.open ("output.txt");
    int sz;
    in>>sz;
    st->EnterScope(sz);
    string command,name,type,printtype;
    in>>command;
    while(in)
    {
        if(st->currentScope==0&&command!="S")
        {
            out<<"Enter a Scope First"<<endl<<endl;
            continue;
        }
        if(command=="I")
        {
            if(st->currentScope==0)
            {
                out<<"Enter a scope first"<<endl<<endl;
            }
            in>>name>>type;
            flag=st->Insert(name,type);
            out<<"I "<<name<<" "<<type<<endl<<endl;
            if(flag)
            {
                out<<"Inserted in ScopeTable# "<<st->currentScope->id <<" at position "<<st->currentScope->Hash(name)<<" "<<st->Lookup(name)->position<<endl<<endl;
            }
            else
            {
                 out<<"Already exist in ScopeTable# "<<st->currentScope->id <<" at position "<<st->currentScope->Hash(name)<<" "<<st->Lookup(name)->position<<endl<<endl;
            }


        }
        if(command=="L")
        {
            in>>name;
            out<<"L "<<name<<endl<<endl;
            si=st->Lookup(name);
            if(si!=0)
            {
                out<<"Found in ScopeTable# "<<scopeid <<" at position "<<hashid<<" "<<si->position<<endl<<endl;

            }
            else
            {
                out<<"Not Found"<<endl<<endl;
            }


        }
        if(command=="D")
        {
            in>>name;
            out<<"D "<<name<<endl<<endl;
            si=st->currentScope->Lookup(name);
            if(si!=0)
            {
                out<<"Found in ScopeTable# "<<st->currentScope->id <<" at position "<<st->currentScope->Hash(name)<<" "<<si->position<<endl<<endl;
                out<<"Deleted entry at "<<st->currentScope->Hash(name)<<" "<<si->position<<endl<<endl;
                st->Remove(name);

            }
            else
            {
                out<<"Not Found"<<endl<<endl;
            }
        }
        if(command=="P")
        {
            in>>printtype;
            if(printtype=="A")
            {
                out<<"P A"<<endl<<endl;
                st->PrintAll();
            }
            else if(printtype=="C")
            {
                out<<"P C"<<endl<<endl;
                st->PrintCurrent();
            }
        }
        if(command=="S")
        {
            out<<"S"<<endl<<endl;
            st->EnterScope(sz);
            out<<"New ScopeTable with id "<<st->currentScope->id<<" is created"<<endl<<endl;
        }
        if(command=="E")
        {
            out<<"E"<<endl<<endl;
            out<<"ScopeTable with id "<<st->currentScope->id<<" removed"<<endl<<endl;
            st->ExitScope();
        }
        in>>command;

    }
    in.close();
    out.close();


}
