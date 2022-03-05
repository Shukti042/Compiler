%{
#include "1605042_Symbol_Table.cpp"
#define YYSTYPE SymbolInfo*
int line_count=1;
int yyparse(void);
int yylex(void);
extern FILE *yyin;
string argument;
int error_count=0;
SymbolTable *table;
vector<string> declarationList;
vector<string> parameterList;
vector<string> returnList;
vector<string> variable_for_asm;
vector<pair<string,string> > parameterNames;
vector<pair<string,string> > array_for_asm;
FILE *fp,*fp3;
int i=0;
string current_function="";

int labelCount=0;
int tempCount=0;

void yyerror(const char* st)
{
	error_count++;
	fprintf(fp3,"Error at Line No %d :%s\n\n",line_count,st);
}

char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

string Symbolmaker(string s,int num)
{
	char a[1];
    a[0]='0'+num;
	s=s+a;
	return s;
}

void optimize()
{
    ofstream ofs("Code.asm",ofstream::out);
    ifstream code("code.asm");
    string line,saveline;
    getline(code, line);
    saveline=line;
    string op1,a1,b1,op2,a2,b2,temp;
    stringstream check(line);
    getline(check,op1,' ');
    if(op1.compare("\tMOV")==0)
    {
        getline(check,temp,' ');
        stringstream check(temp);
        getline(check,a1,',');
        getline(check,b1,',');
    }
    ofs<<saveline<<endl;
    while(getline(code, line))
    {
        saveline=line;
        stringstream check(line);
        getline(check,op2,' ');
        if(op2.compare("\tMOV")==0)
        {
            getline(check,temp,' ');
            stringstream check(temp);
            getline(check,a2,',');
            getline(check,b2,',');
            if(op1.compare("\tMOV")==0)
            {
                if((a1.compare(a2)==0&&b1.compare(b2)==0)||((a1.compare(b2)==0&&b1.compare(a2)==0)))
                {

                }
                else
                {
                    ofs<<saveline<<endl;
                    op1=op2;
                    a1=a2;
                    b1=b2;
                }

            }
            else
            {
                ofs<<saveline<<endl;
                op1=op2;
                a1=a2;
                b1=b2;
            }
        }
        else
        {
            ofs<<saveline<<endl;
            op1=op2;
        }

    }
	ofs.close();
}


%}
%error-verbose
%token IF ELSE FOR WHILE ID LPAREN RPAREN SEMICOLON COMMA
%token LCURL RCURL INT FLOAT VOID CONST_INT LTHIRD RTHIRD PRINTLN RETURN
%token NOT CONST_FLOAT INCOP DECOP
%left ADDOP
%left MULOP
%right ASSIGNOP
%nonassoc LOGICOP
%nonassoc RELOP
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

start : program
	{

		if(error_count==0)
		{
			string temp=$1->code;
			$$->code=".MODEL SMALL\n\.STACK 100H\n\.DATA \n";
			$$->code+="RESULT DB ?,?,?,?,?,?,?,?,?\nFINAL DB ?,?,?,?,?,?,?,?,?\n";
			for(i=0;i<variable_for_asm.size();i++)
			{
				$$->code+=variable_for_asm[i]+" DW ?\n";
			}
			for(i=0;i<array_for_asm.size();i++)
			{
				$$->code+=array_for_asm[i].first+" DW "+array_for_asm[i].second+" DUP(?)\n";
			}
			$$->code+="DISPLAY PROC\n\tPUSH AX\n\tPUSH BX\n\tPUSH CX\n\tPUSH DX\n\tMOV BX,AX\n\tCMP AX,0\n\tJGE POS\n\tMOV AH,2\n\tMOV DL,45\n\tINT 21H\n\tMOV AX,BX \n\tNEG AX\n\tPOS\:\n\tMOV SI,0\n\tWHILE_LOOP\:\n\tMOV DX,0\n\tMOV BX,10\n\tDIV BX\n\tADD DX,'0'\n\tMOV RESULT+SI,DL\n \tADD SI,1\n \tCMP AX,0\n\tJNZ WHILE_LOOP\n\tEND_LOOP\:\n\tMOV RESULT+SI,'$'\n\tMOV FINAL+SI,'$'\n\tMOV CX,SI\n\tMOV DI,SI\n\tSUB DI,1\n\tMOV SI,0\n\tREVERSE\:\n\tMOV BL,RESULT+DI\n\tMOV FINAL+SI,BL\n\tSUB DI,1\n\tADD SI,1\n\tLOOP REVERSE\n\tMOV AH,9\n\tLEA DX,FINAL\n\tINT 21H\n\tMOV AH,2\n\tMOV DL,0DH\n\tINT 21H\n\tMOV DL,0AH\n\tINT 21H\n\tPOP DX\n\tPOP CX\n\tPOP BX\n\tPOP AX\n\tret\nDISPLAY ENDP\n";
			$$->code+=temp;
			ofstream fout;
			fout.open("code.asm");
			fout << $$->code;
			fout.close();
			optimize();
		}

		//fprintf(fp2,"At line No %d start : program\n",line_count);
		$$->setName($1->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

	}
	;

program : program unit 
	{
		//fprintf(fp2,"At line No %d program : program unit\n",line_count);
		$$->setName($1->getName()+$2->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$1->code+$2->code;
		}
	}
	| unit	
	{
		//fprintf(fp2,"At line No %d program : unit\n",line_count);
		$$->setName($1->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		
		if(error_count==0)
		{
			$$->code=$1->code;
		}
	}
	;
	
unit : var_declaration
	{
		//fprintf(fp2,"At line No %d unit : var_declaration\n",line_count);
		$$->setName($1->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$1->code;
		}
	}
     | func_declaration
	{
		//fprintf(fp2,"At line No %d unit : func_declaration\n",line_count);
		$$->setName($1->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$1->code;
		}
	}
     | func_definition
	{
		//fprintf(fp2,"At line No %d unit : func_definition\n",line_count);
		$$->setName($1->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$1->code;
		}
	}
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON	
	{
		if(table->currentScope->id!=1)
		{
			fprintf(fp3,"Error at Line No %d : Function should be declared in global scope \n\n",line_count);
			error_count++;
		}
		else if(table->Lookup($2->getName())==0)
		{
			table->Insert($2->getName(),$2->getType());
			table->Lookup($2->getName())->is_function=true;
			table->Lookup($2->getName())->return_type=$1->getType();
			for(i=0;i<parameterList.size();i++)
				{
					table->Lookup($2->getName())->parameter_list.push_back(parameterList[i]);
				} 
			parameterList.clear();
		}
		else
		{
			fprintf(fp3,"Error at Line No %d : Redeclaration of function %s \n\n",line_count,$2->getName().c_str());
			error_count++;
			parameterList.clear();
		}
		//fprintf(fp2,"At line No %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		parameterNames.clear();
	
	}
		| type_specifier ID LPAREN RPAREN SEMICOLON
			{
				if(table->currentScope->id!=1)
				{
					fprintf(fp3,"Error at Line No %d : Function should be declared in global scope \n\n",line_count);
					error_count++;
				}
				else if(table->Lookup($2->getName())==0)
				{
					table->Insert($2->getName(),$2->getType());
					table->Lookup($2->getName())->is_function=true;
					table->Lookup($2->getName())->return_type=$1->getType();
				}
				else
				{
					fprintf(fp3,"Error at Line No %d : Redeclaration of function %s \n\n",line_count,$2->getName().c_str());
					error_count++;
				}
				//fprintf(fp2,"At line No %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n",line_count);
				$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
			}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN
	{
		if(table->currentScope->id!=1)
		{
			fprintf(fp3,"Error at Line No %d : Function should be declared in global scope \n\n",line_count);
			error_count++;
			parameterList.clear(); 
		}
		else if(table->Lookup($2->getName())==0)
		{
			table->Insert($2->getName(),$2->getType());
			table->Lookup($2->getName())->return_type=$1->getType();
				for(i=0;i<parameterList.size();i++)
				{
						table->Lookup($2->getName())->parameter_list.push_back(parameterList[i]);
				} 
				parameterList.clear();
			table->Lookup($2->getName())->is_function=true;
			table->Lookup($2->getName())->is_defined=true;
			returnList.push_back($1->getType());
		}
		else
		{
			if(table->Lookup($2->getName())->is_defined)
			{
				fprintf(fp3,"Error at Line No %d : Function is already defined\n\n",line_count);
				error_count++;
				parameterList.clear(); 
			}
			else
			{
					bool t=false;
					if(table->Lookup($2->getName())->return_type!=$1->getType())
					{
						fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
						error_count++;
						t=true;
					}
					else
					{
						if(parameterList.size()!=table->Lookup($2->getName())->parameter_list.size())
						{
							fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
							error_count++;
							t=true;
						}
						else{
								for(i=0;i<parameterList.size();i++)
								{
										if(table->Lookup($2->getName())->parameter_list[i]!=parameterList[i])
										{
											fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
											error_count++;
											t=true;
											break;
										}
								}
							}

					}
					if(!t)
					{
						table->Lookup($2->getName())->is_defined=true;

					}
					parameterList.clear(); 
			}
			returnList.push_back($1->getType());

			
		}
		if(error_count==0)
			{
				current_function=$2->getName();
				variable_for_asm.push_back(current_function+"_return");
				for(i=0;i<parameterNames.size();i++)
				{
					table->Lookup($2->getName())->parameterNames.push_back(Symbolmaker(parameterNames[i].second,table->scopeid.sequence));
					variable_for_asm.push_back(Symbolmaker(parameterNames[i].second,table->scopeid.sequence));
				}
			}
	} compound_statement
	{
		//fprintf(fp2,"At line No %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$7->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$2->getName()+" PROC\n";
			if($2->getName()=="main")
			{
				$$->code+="\tMOV AX,@DATA\n\tMOV DS,AX \n"+$7->code+"Return_"+current_function+":\n\tMOV AH,4CH\n\tINT 21H\nEND MAIN\n";
			}
			else
			{
				/*for(i=0;i<table->Lookup($2->getName())->parameterNames.size();i++)
				{
					$$->code+="\tPUSH "+table->Lookup($2->getName())->parameterNames[i]+"\n";
				}
				for(i=0;i<table->Lookup(current_function)->variableNames.size();i++)
				{
					$$->code+="\tPUSH "+table->Lookup(current_function)->variableNames[i]+"\n";
				}*/
				$$->code+="\tPUSH AX\n\tPUSH BX \n\tPUSH CX \n\tPUSH DX\n";
				$$->code+=$7->code;
				$$->code+="Return_"+current_function+":\n";
				$$->code+="\tPOP DX\n\tPOP CX\n\tPOP BX\n\tPOP AX\n";
				/*for(i=table->Lookup(current_function)->variableNames.size()-1;i>=0;i--)
				{
					$$->code+="\tPOP "+table->Lookup(current_function)->variableNames[i]+"\n";
				}
				for(i=table->Lookup($2->getName())->parameterNames.size()-1;i>=0;i--)
				{
					$$->code+="\tPOP "+table->Lookup($2->getName())->parameterNames[i]+"\n";
				}*/
				$$->code+="\tret\n";
				$$->code+=$2->getName()+" ENDP\n";
			}
			parameterNames.clear();
		}
		else
		{
			parameterNames.clear();
		}
		current_function="";
	}
		| type_specifier ID LPAREN RPAREN 
			{
				if(table->currentScope->id!=1)
				{
					fprintf(fp3,"Error at Line No %d : Function should be declared in global scope \n\n",line_count);
					error_count++;
					parameterList.clear(); 
				}
				else if(table->Lookup($2->getName())==0)
				{
					table->Insert($2->getName(),$2->getType());
					table->Lookup($2->getName())->return_type=$1->getType();
					table->Lookup($2->getName())->is_function=true;
					table->Lookup($2->getName())->is_defined=true;
					returnList.push_back($1->getType());
					parameterList.clear();
				}
				else
				{
					bool t=false;
						if(table->Lookup($2->getName())->is_defined)
						{
							fprintf(fp3,"Error at Line No %d : Function is already defined\n\n",line_count);
							t=true;
							error_count++;
						}
						else if(parameterList.size()!=table->Lookup($2->getName())->parameter_list.size())
						{
							fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
							t=true;
							error_count++;
						}
						else if(table->Lookup($2->getName())->return_type!=$1->getType())
						{
							fprintf(fp3,"Error at Line No %d : Function defination doesn't match with declaration\n\n",line_count);
							t=true;
							error_count++;
						}
						if(!t)
						{
							table->Lookup($2->getName())->is_defined=true;

						}
						parameterList.clear();
				}
				returnList.push_back($1->getType());

				if(error_count==0)
				{
					current_function=$2->getName();
					variable_for_asm.push_back(current_function+"_return");
				}
			} compound_statement	
		{
			//fprintf(fp2,"At line No %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n",line_count);
			$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$6->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code=$2->getName()+" PROC\n";
				if($2->getName()=="main")
				{
					$$->code+="\tMOV AX,@DATA\n\tMOV DS,AX \n"+$6->code+"Return_"+current_function+":\n\tMOV AH,4CH\n\tINT 21H\nEND MAIN\n";
				}
				else
				{
					/*for(i=0;i<table->Lookup(current_function)->variableNames.size();i++)
					{
						$$->code+="\tPUSH "+table->Lookup(current_function)->variableNames[i]+"\n";
					}*/
					$$->code+="\tPUSH AX\n\tPUSH BX \n\tPUSH CX \n\tPUSH DX\n";
					$$->code+=$6->code;
					$$->code+="Return_"+current_function+":\n";
					$$->code+="\tPOP DX\n\tPOP CX\n\tPOP BX\n\tPOP AX\n";
					/*for(i=table->Lookup(current_function)->variableNames.size()-1;i>=0;i--)
					{
						$$->code+="\tPOP "+table->Lookup(current_function)->variableNames[i]+"\n";
					}*/
					$$->code+="\tret\n";
					$$->code+=$2->getName()+" ENDP\n";
				}
				parameterNames.clear();
			}
			else
			{
				parameterNames.clear();
			}
			current_function="";
			
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID	
	{
		//fprintf(fp2,"At line No %d parameter_list  : parameter_list COMMA type_specifier ID\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		parameterList.push_back($3->getType());
		parameterNames.push_back(make_pair($3->getType(),$4->getName()));
	}
		| parameter_list COMMA type_specifier	
		{
			//fprintf(fp2,"At line No %d parameter_list  : parameter_list COMMA type_specifier\n",line_count);
			$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());
			parameterList.push_back($3->getType());
		}
 		| type_specifier ID	
		 {
			// fprintf(fp2,"At line No %d parameter_list  : type_specifier ID\n",line_count);
			 $$->setName($1->getName()+" "+$2->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());
			parameterList.push_back($1->getType());
			parameterNames.push_back(make_pair($1->getType(),$2->getName()));
			}
		| type_specifier
			{
				//fprintf(fp2,"At line No %d parameter_list  : type_specifier\n",line_count);
				$$->setName($1->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				parameterList.push_back($1->getType());
			}
 		;

 		
compound_statement : LCURL {table->EnterScope(11);
for(i=0;i<parameterNames.size();i++)
{
	table->Insert(parameterNames[i].second,"ID");
	table->Lookup(parameterNames[i].second)->data_type=parameterNames[i].first;
	table->Lookup(parameterNames[i].second)->Symbol=Symbolmaker(parameterNames[i].second,table->currentScope->id);
	parameterNames[i].second=Symbolmaker(parameterNames[i].second,table->currentScope->id);
}
} statements RCURL	
	{
		//fprintf(fp2,"At line No %d compound_statement : LCURL statements RCURL\n",line_count);
		$$->setName($1->getName()+" "+$3->getName()+" "+$4->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		$$->code=$3->code;
		table->ExitScope();
	}
 		    | LCURL {table->EnterScope(11);
			 for(i=0;i<parameterNames.size();i++)
				{
					table->Insert(parameterNames[i].second,"ID");
					table->Lookup(parameterNames[i].second)->data_type=parameterNames[i].first;
					table->Lookup(parameterNames[i].second)->Symbol=Symbolmaker(parameterNames[i].second,table->currentScope->id);
					parameterNames[i].second=Symbolmaker(parameterNames[i].second,table->currentScope->id);
				}
			} RCURL	
			 {
				 //fprintf(fp2,"At line No %d compound_statement : LCURL RCURL	compound_statement\n",line_count);
				 $$->setName($1->getName()+" "+$3->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				table->ExitScope();
			 }
			 | error RCURL {yyerrok;}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON	
	{
		while(!declarationList.empty())
		{
			table->Lookup(declarationList.back())->data_type=$1->getType();
			declarationList.pop_back();
		}
		//fprintf(fp2,"At line No %d var_declaration : type_specifier declaration_list SEMICOLON\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
 		 ;
 		 
type_specifier	: INT	
	{
		//fprintf(fp2,"At line No %d type_specifier	: INT\n",line_count);
		$$->setName($1->getName());
		$$->setType("INT");
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
 		| FLOAT
		 	{
				// fprintf(fp2,"At line No %d type_specifier	:  FLOAT\n",line_count);
				 $$->setName($1->getName());
				 $$->setType("FLOAT");
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
			}
 		| VOID	
		 {
			// fprintf(fp2,"At line No %d type_specifier	: VOID\n",line_count);
			 $$->setName($1->getName());
			 $$->setType("VOID");
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
 		;
 		
declaration_list : declaration_list COMMA ID	
	{
		if(!table->Insert($3->getName(),$3->getType()))
		{
			fprintf(fp3,"Error at Line No %d : Multiple declaration of %s \n\n",line_count,$3->getName().c_str());
			error_count++;
		}
		else
		{
			
			declarationList.push_back($3->getName());
		}

		if(error_count==0)
		{
			variable_for_asm.push_back(Symbolmaker($3->getName(),table->currentScope->id));
			if(current_function.compare("main")!=0 && current_function.compare("")!=0)
			{
				table->Lookup(current_function)->variableNames.push_back(Symbolmaker($3->getName(),table->currentScope->id));
			}
			table->Lookup($3->getName())->Symbol=Symbolmaker($3->getName(),table->currentScope->id);
		}
		
		//fprintf(fp2,"At line No %d declaration_list : declaration_list COMMA ID\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		
	}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	
		   {
			    if(!table->Insert($3->getName(),$3->getType()))
				{
					fprintf(fp3,"Error at Line No %d : Multiple declaration of %s \n\n",line_count,$3->getName().c_str());
					error_count++;
				}
				else
				{
					table->Lookup($3->getName())->is_array=true;
					table->Lookup($3->getName())->array_size=atoi($5->getName().c_str());
					declarationList.push_back($3->getName());
					array_for_asm.push_back(make_pair(Symbolmaker($3->getName(),table->currentScope->id),$5->getName()));
					if(current_function.compare("main")!=0 && current_function.compare("")!=0)
					{
						table->Lookup(current_function)->variableNames.push_back(Symbolmaker($3->getName(),table->currentScope->id));
					}
					table->Lookup($3->getName())->Symbol=Symbolmaker($3->getName(),table->currentScope->id);
				}
			  // fprintf(fp2,"At line No %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n",line_count);
			   $$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				

		   }
 		  | ID	
		   {
			   if(!table->Insert($1->getName(),$1->getType()))
			   {
				   fprintf(fp3,"Error at Line No %d : Multiple declaration of %s \n\n",line_count,$1->getName().c_str());
					error_count++;
			   }
			   else
			   {
				   declarationList.push_back($1->getName());
			   }

			   if(error_count==0)
				{
					variable_for_asm.push_back(Symbolmaker($1->getName(),table->currentScope->id));
					if(current_function.compare("main")!=0 && current_function.compare("")!=0)
					{
						table->Lookup(current_function)->variableNames.push_back(Symbolmaker($1->getName(),table->currentScope->id));
					}
					table->Lookup($1->getName())->Symbol=Symbolmaker($1->getName(),table->currentScope->id);
				}
				
			  // fprintf(fp2,"At line No %d declaration_list : ID\n",line_count);
			   $$->setName($1->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
		   }
 		  | ID LTHIRD CONST_INT RTHIRD	
		   {
			   if(!table->Insert($1->getName(),$1->getType()))
			   {
				   fprintf(fp3,"Error at Line No %d : Multiple declaration of %s \n\n",line_count,$1->getName().c_str());
					error_count++;
			   }
			   else
			   {
				    table->Lookup($1->getName())->is_array=true;
					table->Lookup($1->getName())->array_size=atoi($3->getName().c_str());
					declarationList.push_back($1->getName());
					array_for_asm.push_back(make_pair(Symbolmaker($1->getName(),table->currentScope->id),$3->getName()));
					if(current_function.compare("main")!=0 && current_function.compare("")!=0)
					{
						table->Lookup(current_function)->variableNames.push_back(Symbolmaker($1->getName(),table->currentScope->id));
					}
					table->Lookup($1->getName())->Symbol=Symbolmaker($1->getName(),table->currentScope->id);
			   }
				
			  // fprintf(fp2,"At line No %d declaration_list :ID LTHIRD CONST_INT RTHIRD\n",line_count);
			   $$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				
				
		   }
 		  ;
 		  
statements : statement	
	{
	//fprintf(fp2,"At line No %d statements : statement\n",line_count);
	$$->setName($1->getName());
	//fprintf(fp2,"%s\n\n",$$->getName().c_str());

	if(error_count==0)
	{
		$$->code=$1->code;
	}
	}
	   | statements statement
	   {
		   //fprintf(fp2,"At line No %d statements : statements statement\n",line_count);
	   		$$->setName($1->getName()+" "+$2->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
		{
			$$->code=$1->code+$2->code;
		}
			}
	   ;
	   
statement : var_declaration	{
							//fprintf(fp2,"At line No %d statement : var_declaration\n",line_count);
							$$->setName($1->getName());
							//fprintf(fp2,"%s\n\n",$$->getName().c_str());
							}
	  | expression_statement	{
		  						//fprintf(fp2,"At line No %d statement : expression_statement\n",line_count);
	  							$$->setName($1->getName());
								//fprintf(fp2,"%s\n\n",$$->getName().c_str());
								
								if(error_count==0)
								{
									$$->code=$1->code;
									$$->Symbol=$1->Symbol;
									$$->setType($1->getType());
								}
							}
	  | compound_statement	{
		  					//fprintf(fp2,"At line No %d statement : compound_statement\n",line_count);
	  						$$->setName($1->getName());
							//fprintf(fp2,"%s\n\n",$$->getName().c_str());
							
							if(error_count==0)
								{
									$$->code=$1->code;
									$$->Symbol=$1->Symbol;
									$$->setType($1->getType());
								}
							}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement	
	  {
		 // fprintf(fp2,"At line No %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n",line_count);
	  	$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName()+" "+$7->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$3->code;
			char *label1=newLabel();
			char *label2=newLabel();
			$$->code+=string(label1)+":\n";
			$$->code+=$4->code;
			$$->code+="\tMOV AX,"+$4->Symbol+"\n";
			$$->code+="\tCMP AX,0\n";
			$$->code+="\tJE "+string(label2)+"\n";
			$$->code+=$7->code;
			$$->code+=$5->code;
			$$->code+="\tJMP "+string(label1)+"\n";
			$$->code+=string(label2)+":\n";
		}
	}
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE	
	  {
		 // fprintf(fp2,"At line No %d statement : IF LPAREN expression RPAREN statement\n",line_count);
	  		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code=$3->code;
				char *label=newLabel();
				$$->code+="\tMOV AX,"+$3->Symbol+"\n";
				$$->code+="\tCMP AX,0\n";
				$$->code+="\tJE "+string(label)+"\n";
				$$->code+=$5->code;
				$$->code+=string(label)+":\n";
			}
		}
	  | IF LPAREN expression RPAREN statement ELSE statement	
	 														 {
		  														//fprintf(fp2,"At line No %d statement : IF LPAREN expression RPAREN statement ELSE statement\n",line_count);
	  															$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName()+" "+$7->getName());
																//fprintf(fp2,"%s\n\n",$$->getName().c_str());

																if(error_count==0)
																{
																	$$->code=$3->code;
																	char *label1=newLabel();
																	char *label2=newLabel();
																	$$->code+="\tMOV AX,"+$3->Symbol+"\n";
																	$$->code+="\tCMP AX, 0\n";
																	$$->code+="\tJE "+string(label1)+"\n";
																	$$->code+=$5->code;
																	$$->code+="\tJMP "+string(label2)+"\n";
																	$$->code+=string(label1)+":\n";
																	$$->code+=$7->code;
																	$$->code+=string(label2)+":\n";
																}
															}
	  | WHILE LPAREN expression RPAREN statement	
	  											{
													// fprintf(fp2,"At line No %d statement : WHILE LPAREN expression RPAREN statement\n",line_count);
	  												$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName());
													//fprintf(fp2,"%s\n\n",$$->getName().c_str());
													
													if(error_count==0)
													{
														char *label1=newLabel();
														char *label2=newLabel();
														$$->code+=string(label1)+":\n";
														$$->code+=$3->code;
														$$->code+="\tMOV AX,"+$3->Symbol+"\n";
														$$->code+="\tCMP AX,0\n";
														$$->code+="\tJE "+string(label2)+"\n";
														$$->code+=$5->code;
														$$->code+="\tJMP "+string(label1)+"\n";
														$$->code+=string(label2)+":\n";
													}
												}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	   {
		  	 if(table->Lookup($3->getName())==0)
			   {
				   fprintf(fp3,"Error at Line No %d : Undeclared Variable : %s \n\n",line_count,$3->getName().c_str());
				   error_count++;
			   }
		    //fprintf(fp2,"At line No %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n",line_count);
	  		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code+="\tMOV AX,"+table->Lookup($3->getName())->Symbol+"\n";
				$$->code+="\tCALL DISPLAY\n";
			}
		}
	  | RETURN expression SEMICOLON	
	  {
		  if(!returnList.empty())
		  {
			  if($2->data_type!=returnList.back())
			  {
				  if(!(($2->data_type=="INT")&&(returnList.back()=="FLOAT")))
				  {
					  fprintf(fp3,"Error at Line No %d : Return type doesn't match with declaration \n\n",line_count);
						error_count++;
						returnList.pop_back();

				  }
			  }
			  else
			  {
				  returnList.pop_back();
			  }
		  }
		 // fprintf(fp2,"At line No %d statement : RETURN expression SEMICOLON\n",line_count);
	  		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code=$2->code;
				$$->code+="\tMOV AX,"+$2->Symbol+"\n";
				$$->code+="\tMOV "+current_function+"_return"+",AX\n";
				$$->code+="\tJMP Return_"+current_function+"\n";
			}
		}
		| error SEMICOLON {yyerrok;}
	  ;
	  
expression_statement 	: SEMICOLON		{
										//fprintf(fp2,"At line No %d expression_statement 	: SEMICOLON\n",line_count);
										$$->setName($1->getName());
										//fprintf(fp2,"%s\n\n",$$->getName().c_str());
										if(error_count==0)
										{
											$$->code="";
										}
										}		
			| expression SEMICOLON 	
			{
				$$->data_type=$1->data_type;
				//fprintf(fp2,"At line No %d expression_statement 	: expression SEMICOLON\n",line_count);
				$$->setName($1->getName()+" "+$2->getName());
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());

				if(error_count==0)
				{
					$$->code=$1->code;
					$$->Symbol=$1->Symbol;
					$$->setType($1->getType());
				}
				
			}
			;
	  
variable : ID 		{
					string tt=$1->getName();
					if(table->Lookup($1->getName())==0)
					{
						fprintf(fp3,"Error at Line No %d : Undeclared variable :  %s \n\n",line_count,$1->getName().c_str());
						error_count++;
					}
					else
					{
						$$->data_type=table->Lookup($1->getName())->data_type;
						if(table->Lookup($1->getName())->is_array)
						{
							fprintf(fp3,"Error at Line No %d : Type mismatch\n\n",line_count);
							error_count++;
						}

						else if(error_count==0)
						{
							$$->Symbol=table->Lookup(tt)->Symbol;
						}
					}
					//fprintf(fp2,"At line No %d variable : ID \n",line_count);
					$$->setName($1->getName());
					//fprintf(fp2,"%s\n\n",$$->getName().c_str());

					if(error_count==0)
					{
						$$->setType("notarray");
						$$->code="";
						
					}
					
				}
	 | ID LTHIRD expression RTHIRD 	{
		 							string tt=$1->getName();
		 							if(table->Lookup($1->getName())==0)
									{
										fprintf(fp3,"Error at Line No %d : Variable %s is  not declared in this scope\n\n",line_count,$1->getName().c_str());
										error_count++;
									}
									else if(!(table->Lookup($1->getName())->is_array))
									 {
										 fprintf(fp3,"Error at Line No %d : Variable %s is not an array\n\n",line_count,$1->getName().c_str());
										 error_count++;
									 }
		 							else if($3->data_type!="INT")
									 {
										fprintf(fp3,"Error at Line No %d : Non-integer Array Index \n\n",line_count);	
										error_count++; 
									 }
									 if(table->Lookup($1->getName())!=0)
									 {
										$$->data_type=table->Lookup($1->getName())->data_type;
										$$->is_array=true;
									 }
									if(error_count==0)
									{
										$$->setType("array");
										$$->Symbol=table->Lookup(tt)->Symbol;
										$$->code=$3->code+"MOV BX," +$3->Symbol +"\nADD BX, BX\n";
									}
									//fprintf(fp2,"At line No %d variable : ID LTHIRD expression RTHIRD\n",line_count);
	 								$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName());
									//fprintf(fp2,"%s\n\n",$$->getName().c_str());
										
								}
								;
	 
 expression : logic_expression	{
	 							$$->data_type=$1->data_type;
	 							//fprintf(fp2,"At line No %d expression : logic_expression\n",line_count);
 								$$->setName($1->getName());
								//fprintf(fp2,"%s\n\n",$$->getName().c_str());
								if(error_count==0)
								{
									$$->code=$1->code;
									$$->Symbol=$1->Symbol;
									$$->setType($1->getType());
								}
							}
	   | variable ASSIGNOP logic_expression 	
	   {
		   if($1->data_type!=$3->data_type)
		   {
			   if($1->data_type=="FLOAT"&&$3->data_type=="INT")
				{
					$$->data_type="FLOAT";
				}
				else if($1->data_type=="INT"&&$3->data_type=="FLOAT")
				{
					fprintf(fp3,"Error at Line No %d : Type Mismatch\n\n",line_count);
					   error_count++;
				}
				else if($1->data_type==""||$3->data_type=="")
				{

				}
				else
				{
			   		fprintf(fp3,"Error at Line No %d : Two operands of assign operator doesn't match\n\n",line_count);
					   error_count++;
				}
		   }
		   else
		   {
			   $$->data_type=$1->data_type;
		   }
		  // fprintf(fp2,"At line No %d expression : variable ASSIGNOP logic_expression\n",line_count);
	   		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code=$3->code+$1->code;
				$$->Symbol=$1->Symbol;
				$$->setType($1->getType());
				$$->code+="\tMOV AX,"+$3->Symbol+"\n";
				if($$->getType()=="array")
				{
					$$->code+= "\tMOV  "+$1->Symbol+"[BX],AX\n";
				}
				else
				{
					$$->code+= "\tMOV "+$1->Symbol+",AX\n";
				}
				
			}
		}	
	   ;
			
logic_expression : rel_expression 	
	{
		$$->is_array=$1->is_array;
		$$->data_type=$1->data_type;
		//fprintf(fp2,"At line No %d logic_expression : rel_expression\n",line_count);
		$$->setName($1->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$1->code;
			$$->Symbol=$1->Symbol;
			$$->setType($1->getType());
		}
	}	
		 | rel_expression LOGICOP rel_expression 	
		{
			$$->data_type="INT";
			//fprintf(fp2,"At line No %d logic_expression : rel_expression LOGICOP rel_expression\n",line_count);
		 	$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code=$1->code;
				$$->code+=$3->code;
				char *temp=newTemp();
				
				$$->Symbol=string(temp);
				variable_for_asm.push_back($$->Symbol);
				if(current_function.compare("main")!=0 && current_function.compare("")!=0)
				{
					table->Lookup(current_function)->variableNames.push_back($$->Symbol);
				}
				char *label1=newLabel();
				char *label2=newLabel();
				if($2->getName()=="&&"){
					$$->code+="\tMOV AX,"+$1->Symbol+"\n";
					$$->code+="\tCMP AX,0\n";
					$$->code+="\tJE "+string(label1)+"\n";
					$$->code+="\tMOV AX,"+$3->Symbol+"\n";
					$$->code+="\tCMP AX,0\n";
					$$->code+="\tJE "+string(label1)+"\n";
					$$->code+="\tMOV "+$$->Symbol+",1\n";
					$$->code+="\tJMP "+string(label2)+"\n";
					$$->code+=string(label1)+":\n";
					$$->code+="\tMOV "+$$->Symbol+",0\n";		
					$$->code+=string(label2)+":\n";

				}
				else if($2->getName()=="||"){
					$$->code+="\tMOV AX,"+$1->Symbol+"\n";
					$$->code+="\tCMP AX,1\n";
					$$->code+="\tJE "+string(label1)+"\n";
					$$->code+="\tMOV AX,"+$3->Symbol+"\n";
					$$->code+="\tCMP AX,1\n";
					$$->code+="\tJE "+string(label1)+"\n";
					$$->code+="\tMOV "+$$->Symbol+",0\n";
					$$->code+="\tJMP "+string(label2)+"\n";
					$$->code+=string(label1)+":\n";
					$$->code+="\tMOV "+$$->Symbol+",1\n";		
					$$->code+=string(label2)+":\n";

				}
			}
		}
		 ;
			
rel_expression	: simple_expression 			
	{
		$$->is_array=$1->is_array;
		$$->data_type=$1->data_type;
		//fprintf(fp2,"At line No %d rel_expression	: simple_expression\n",line_count);
		$$->setName($1->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$1->code;
			$$->Symbol=$1->Symbol;
			$$->setType($1->getType());
		}
		}
		| simple_expression RELOP simple_expression		
		{
			$$->data_type="INT";
			//fprintf(fp2,"At line No %d rel_expression	: simple_expression RELOP simple_expression\n",line_count);
			$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code=$1->code;
				$$->code+=$3->code;
				$$->code+="\tMOV AX," + $1->Symbol+"\n";
				$$->code+="\tCMP AX," + $3->Symbol+"\n";
				char *temp=newTemp();
				char *label1=newLabel();
				char *label2=newLabel();
				if($2->getName()=="<")
				{
					$$->code+="\tJL " + string(label1)+"\n";
				}
				else if($2->getName()=="<=")
				{
					$$->code+="\tJLE " + string(label1)+"\n";
				}
				else if($2->getName()==">")
				{
					$$->code+="\tJG " + string(label1)+"\n";
				}
				else if($2->getName()==">=")
				{
					$$->code+="\tJGE " + string(label1)+"\n";
				}
				else if($2->getName()=="==")
				{
					$$->code+="\tJE " + string(label1)+"\n";
				}
				else if($2->getName()=="!=")
				{
					$$->code+="\tJNE " + string(label1)+"\n";
				}
				$$->code+="\tMOV "+string(temp) +",0\n";
				$$->code+="\tJMP "+string(label2) +"\n";
				$$->code+=string(label1)+":\n\tMOV "+string(temp)+",1\n";
				$$->code+=string(label2)+":\n";
				$$->Symbol=string(temp);
				variable_for_asm.push_back($$->Symbol);
				if(current_function.compare("main")!=0 && current_function.compare("")!=0)
				{
					table->Lookup(current_function)->variableNames.push_back($$->Symbol);
				}
			}
		}
		;
				
simple_expression : term 	{
								$$->is_array=$1->is_array;
								$$->data_type=$1->data_type;
								//fprintf(fp2,"At line No %d simple_expression : term \n",line_count);
								$$->setName($1->getName());
								//fprintf(fp2,"%s\n\n",$$->getName().c_str());

								if(error_count==0)
								{
									$$->code=$1->code;
									$$->Symbol=$1->Symbol;
									$$->setType($1->getType());
								}							
							}
		  | simple_expression ADDOP term 	{
			if($1->data_type!=$3->data_type)
			{
				if(($1->data_type=="INT"&&$3->data_type=="FLOAT")||($1->data_type=="FLOAT"&&$3->data_type=="INT"))
				{
					$$->data_type="FLOAT";
				}
			}
			else{$$->data_type=$1->data_type;}
			//fprintf(fp2,"At line No %d simple_expression : simple_expression ADDOP term \n",line_count);
		  	$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code=$1->code;
				$$->code+=$3->code;
				char *temp=newTemp();
				$$->code+="\tMOV AX,"+$1->Symbol+"\n";
				if($2->getName()=="+")
				{
					$$->code+="\tADD AX,"+$3->Symbol+"\n";
				}
				else
				{
					$$->code+="\tSUB AX,"+$3->Symbol+"\n";
				}
				$$->code+="\tMOV "+string(temp)+",AX\n";
				$$->Symbol=string(temp);
				variable_for_asm.push_back($$->Symbol);
				if(current_function.compare("main")!=0 && current_function.compare("")!=0)
				{
					table->Lookup(current_function)->variableNames.push_back($$->Symbol);
				}
			}
		}
		  ;
			 		
term :	unary_expression	{
							$$->data_type=$1->data_type;
							//fprintf(fp2,"At line No %d term :	unary_expression\n",line_count);
							$$->setName($1->getName());
							//fprintf(fp2,"%s\n\n",$$->getName().c_str());

							if(error_count==0)
								{
									$$->code=$1->code;
									$$->Symbol=$1->Symbol;
									$$->setType($1->getType());
								}	
							}
     |  term MULOP unary_expression	
	 	{
			if($2->getName()=="%")
			 {
				 if($1->data_type!="INT"||$3->data_type!="INT")
				 {
					 fprintf(fp3,"Error at Line No %d : Non-integer operand on modulus operator\n\n",line_count);
					 error_count++;
				 }
			 }
			 else if($1->data_type!=$3->data_type)
			 {
				 if(($1->data_type=="INT"&&$3->data_type=="FLOAT")||($1->data_type=="FLOAT"&&$3->data_type=="INT"))
				 {
					 $$->data_type="FLOAT";
				 }
			 }
			 else{$$->data_type=$1->data_type;}
		 	//fprintf(fp2,"At line No %d term :	term MULOP unary_expression\n",line_count);
	 		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());

			if(error_count==0)
			{
				$$->code=$1->code;
				$$->code += $3->code;
				$$->code += "\tMOV AX,"+ $1->Symbol+"\n";
				$$->code += "\tMOV BX,"+ $3->Symbol+"\n";
				char *temp=newTemp();
				if($2->getName()=="*")
				{
					$$->code += "\tMUL BX\n";
					$$->code += "\tMOV "+ string(temp) + ",AX\n";
				}
				else if($2->getName()=="/")
				{
					$$->code += "\tMOV DX,0\n";
					$$->code += "\tDIV BX\n";
					$$->code += "\tMOV "+ string(temp) + ",AX\n";
				}
				else
				{
					$$->code += "\tMOV DX,0\n";
					$$->code += "\tDIV BX\n";
					$$->code += "\tMOV "+ string(temp) + ",DX\n";
				}
				$$->Symbol=string(temp);
				variable_for_asm.push_back($$->Symbol);
				if(current_function.compare("main")!=0 && current_function.compare("")!=0)
				{
					table->Lookup(current_function)->variableNames.push_back($$->Symbol);
				}
			}
			
		}
     ;

unary_expression : ADDOP unary_expression 	{
												string tt=$1->getName();
												$$->data_type=$2->data_type;
												//fprintf(fp2,"At line No %d unary_expression : ADDOP unary_expression\n",line_count);
												$$->setName($1->getName()+" "+$2->getName());
												//fprintf(fp2,"%s\n\n",$$->getName().c_str());

												if(error_count==0)
												{
													$$->code=$2->code;
													$$->Symbol=$2->Symbol;
													if(tt=="-")
													{
														$$->Symbol="-"+$$->Symbol;
													}
												}
											} 
		 | NOT unary_expression 	{
			 						$$->data_type=$2->data_type;
			 						//fprintf(fp2,"At line No %d unary_expression : NOT unary_expression\n",line_count);
		 							$$->setName($1->getName()+" "+$2->getName());
									//fprintf(fp2,"%s\n\n",$$->getName().c_str());

									if(error_count==0)
									{
										$$->code=$2->code;
										$$->Symbol=$2->Symbol;
										$$->code+="\tMOV AX,"+$$->Symbol+"\n";
										$$->code+="\tNOT AX\n";
										$$->code+="\tMOV "+$$->Symbol+",AX\n";
									}
									
								} 
		 | factor 	{
			 		$$->is_array=$1->is_array;
			 		$$->data_type=$1->data_type;
			 		//fprintf(fp2,"At line No %d unary_expression :factor\n",line_count);
		 			$$->setName($1->getName());
					//fprintf(fp2,"%s\n\n",$$->getName().c_str());
					
					if(error_count==0)
					{
						$$->code=$1->code;
						$$->Symbol=$1->Symbol;
						$$->setType($1->getType());
					}
				} 
		 ;
	
factor	: variable 	{
						$$->is_array=$1->is_array;
						$$->data_type=$1->data_type;
						//fprintf(fp2,"At line No %d factor	: variable\n",line_count);
						$$->setName($1->getName()); 
						//fprintf(fp2,"%s\n\n",$$->getName().c_str());

						if(error_count==0)
						{
							$$->setType($1->getType());
							$$->code=$1->code;
							if($$->getType()=="notarray")
							{
								$$->Symbol=$1->Symbol;
							}
							else
							{
								char *temp= newTemp();
								$$->code+="\tMOV AX," + $1->Symbol + "[BX]\n";
								$$->code+= "\tMOV " + string(temp) + ",AX\n";
								$$->Symbol=string(temp);
								variable_for_asm.push_back($$->Symbol);
								if(current_function.compare("main")!=0 && current_function.compare("")!=0)
								{
									table->Lookup(current_function)->variableNames.push_back($$->Symbol);
								}
							}
						}
						

					}
	| ID LPAREN argument_list RPAREN	
	{
		bool allIsWell=true;
		SymbolInfo *temp=table->Lookup($1->getName());
		if(temp==0)	
		{
			fprintf(fp3,"Error at Line No %d : Function is not defined\n\n",line_count);
			error_count++;
			allIsWell=false;
		}
		else if(!(temp->is_defined))
		{
			fprintf(fp3,"Error at Line No %d : Function is not defined\n\n",line_count);
			error_count++;
			allIsWell=false;
		}
		else if(!temp->is_function)
		{
			fprintf(fp3,"Error at Line No %d : %s is not a Function \n\n",line_count,$1->getName().c_str());
			error_count++;
			allIsWell=false;
		}
		else if(temp->parameter_list.size()!=$3->argumentList.size())
		{
			fprintf(fp3,"Error at Line No %d : Number of arguments doesn't match with defination\n\n",line_count);
			error_count++;
			allIsWell=false;
		}
		else if(temp->parameter_list.size()!=0)
		{
			for(i=0;i<temp->parameter_list.size();i++)
			{
				if(temp->parameter_list[i]!=$3->argumentList[i])
				{
					if(!(temp->parameter_list[i]=="FLOAT"&&$3->argumentList[i]=="INT"))
					{
						fprintf(fp3,"Error at Line No %d : Argument doesn't match with defination \n\n",line_count,temp->parameter_list[i].c_str());
						allIsWell=false;
						error_count++;
						break;
					}
				}
			}
		}
		if(allIsWell)
		{
			$$->data_type=table->Lookup($1->getName())->return_type;

		}
		

		if(error_count==0)
		{
			$$->code=$3->code;
			if(current_function.compare("main")!=0)
			{
				for(i=0;i<table->Lookup($1->getName())->parameterNames.size();i++)
				{
					$$->code+="\tPUSH "+table->Lookup($1->getName())->parameterNames[i]+"\n";
				}
				for(i=0;i<table->Lookup($1->getName())->variableNames.size();i++)
				{
					$$->code+="\tPUSH "+table->Lookup($1->getName())->variableNames[i]+"\n";
				}
			}
			for(i=0;i<$3->argumentNames.size();i++)
			{
				$$->code+="\tMOV AX,"+$3->argumentNames[i]+"\n";
				$$->code+="\tMOV "+table->Lookup($1->getName())->parameterNames[i]+",AX\n";

			}
			$$->code+="\tCALL "+$1->getName()+"\n";
			$$->code+="\tMOV AX,"+$1->getName()+"_return\n";
			char *temp=newTemp();
			$$->code+="\tMOV "+string(temp)+",AX\n";
			if(current_function.compare("main")!=0)
			{
				for(i=table->Lookup($1->getName())->variableNames.size()-1;i>=0;i--)
					{
						$$->code+="\tPOP "+table->Lookup($1->getName())->variableNames[i]+"\n";
					}
					for(i=table->Lookup($1->getName())->parameterNames.size()-1;i>=0;i--)
					{
						$$->code+="\tPOP "+table->Lookup($1->getName())->parameterNames[i]+"\n";
					}
			}
			$$->Symbol=string(temp);
			variable_for_asm.push_back($$->Symbol);
			if(current_function.compare("main")!=0 && current_function.compare("")!=0)
			{
				table->Lookup(current_function)->variableNames.push_back($$->Symbol);
			}
		}

		//fprintf(fp2,"At line No %d factor	: ID LPAREN argument_list RPAREN\n",line_count);
	  	$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		
	}
	| LPAREN expression RPAREN	{
		$$->data_type=$2->data_type;
		//fprintf(fp2,"At line No %d factor	: LPAREN expression RPAREN\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
		//fprintf(fp2,"%s\n\n",$$->getName().c_str());

		if(error_count==0)
		{
			$$->code=$2->code;
			$$->Symbol=$2->Symbol;
			$$->setType($2->getType());
		}
	}

	| CONST_INT 	{
					$$->data_type="INT";
					//fprintf(fp2,"At line No %d factor	: CONST_INT\n",line_count);
					$$->setName($1->getName());
					//fprintf(fp2,"%s\n\n",$$->getName().c_str());

					if(error_count==0)
					{
						$$->code="";
						$$->Symbol=$1->Symbol;
					}
					}
	| CONST_FLOAT	{
					$$->data_type="FLOAT";
					//fprintf(fp2,"At line No %d factor	: CONST_FLOAT\n",line_count);
					$$->setName($1->getName()); 
					//fprintf(fp2,"%s\n\n",$$->getName().c_str());
					
					if(error_count==0)
					{
						$$->code="";
						$$->Symbol=$1->Symbol;
					}
				}
	| variable INCOP 	{
						$$->data_type=$1->data_type;
						//fprintf(fp2,"At line No %d factor	: variable INCOP\n",line_count);
						$$->setName($1->getName()+" "+$2->getName());
						//fprintf(fp2,"%s\n\n",$$->getName().c_str());

						if(error_count==0)
						{
							$$->code="";
							char *temp=newTemp();
							if($1->getType()=="array")
							{
								$$->code+="\tMOV AX,"+$1->Symbol+"[BX]\n";
								$$->code+="\tMOV "+string(temp)+",AX\n";
								$$->code+="\tINC AX\n";
								$$->code+="\tMOV "+$1->Symbol+"[BX],AX\n";
							}
							else
							{
								$$->code+="\tMOV AX,"+$1->Symbol+"\n";
								$$->code+="\tMOV "+string(temp)+",AX\n";
								$$->code+="\tINC "+$1->Symbol+"\n";
							}
							$$->Symbol=string(temp);
							variable_for_asm.push_back($$->Symbol);
							if(current_function.compare("main")!=0 && current_function.compare("")!=0)
							{
								table->Lookup(current_function)->variableNames.push_back($$->Symbol);
							}
							
						}
					}
	| variable DECOP	{
						$$->data_type=$1->data_type;
						//fprintf(fp2,"At line No %d factor	: variable DECOP\n",line_count);
						$$->setName($1->getName()+" "+$2->getName());
						//fprintf(fp2,"%s\n\n",$$->getName().c_str());

						if(error_count==0)
						{
							$$->code="";
							char *temp=newTemp();
							if($1->getType()=="array")
							{
								$$->code+="\tMOV AX,"+$1->Symbol+"[BX]\n";
								$$->code+="\tMOV "+string(temp)+",AX\n";
								$$->code+="\tDEC AX\n";
								$$->code+="\tMOV "+$1->Symbol+"[BX],AX\n";
							}
							else
							{
								$$->code+="\tMOV AX,"+$1->Symbol+"\n";
								$$->code+="\tMOV "+string(temp)+",AX\n";
								$$->code+="\tDEC "+$1->Symbol+"\n";
							}
							$$->Symbol=string(temp);
							variable_for_asm.push_back($$->Symbol);
							if(current_function.compare("main")!=0 && current_function.compare("")!=0)
							{
								table->Lookup(current_function)->variableNames.push_back($$->Symbol);
							}
							
						}
					}
	;
	
argument_list : arguments	
{
	i=0;
	while(i<$1->argumentList.size())
		{
			$$->argumentList[i]=$1->argumentList[i];
			if(error_count==0)
			{
				$$->argumentNames[i]=$1->argumentNames[i];
			}
			i++;
		}
	
	//fprintf(fp2,"At line No %d argument_list : arguments\n",line_count);
	$$->setName($1->getName());
	//fprintf(fp2,"%s\n\n",$$->getName().c_str());

	if(error_count==0)
	{
		$$->code=$1->code;
	}
}
			  |	{
				  //fprintf(fp2,"At line No %d argument_list : \n",line_count);
				  }
			  ;
	
arguments : arguments COMMA logic_expression	
	{
			
			i=0;
			while(i<$1->argumentList.size())
			{
				argument=$1->argumentList[i];
				$$->argumentList[i]=argument;
				if(error_count==0)
				{
					argument=$1->argumentNames[i];
					$$->argumentNames[i]=argument;
				}
				i++;
			}
			$$->argumentList.push_back($3->data_type);
			if(error_count==0)
			{
				$$->argumentNames.push_back($3->Symbol);
				$$->code=$1->code+$3->code;
			}
			//fprintf(fp2,"At line No %d arguments : arguments COMMA logic_expression\n",line_count);
			$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			//fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}

	      | logic_expression	
		  {
				$$->argumentList.push_back($1->data_type);
				if(error_count==0)
				{
					$$->argumentNames.push_back($1->Symbol);
					$$->code=$1->code;
				}
				//fprintf(fp2,"At line No %d arguments : logic_expression\n",line_count);
				$$->setName($1->getName()); 
				//fprintf(fp2,"%s\n\n",$$->getName().c_str());
				}
	      ;
 

%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	
	//fp2= fopen(argv[2],"w");
	//fp3= fopen(argv[3],"w");
	fp3= fopen(argv[2],"w");
	table=new SymbolTable(11);

	yyin=fp;
	yyparse();
	//fprintf(fp2,"			Symbol Table\n\n");
	//table->PrintAll();
	fprintf(fp3,"Total Lines: %d \n",--line_count);
	fprintf(fp3,"Total Errors: %d \n",error_count);	
	//fprintf(fp2,"Total Errors: %d \n",error_count);	
	//fprintf(fp2,"Total Lines: %d \n",--line_count);	


	//fclose(fp2);
	fclose(fp3);
	
	return 0;
}

