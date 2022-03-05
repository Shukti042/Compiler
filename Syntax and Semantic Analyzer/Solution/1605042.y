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
vector<pair<string,string> > parameterNames;
FILE *fp,*fp2,*fp3;
int i=0;
void yyerror(char* st)
{
	error_count++;
	fprintf(fp3,"Error at Line No %d :%s\n\n",line_count,st);
}


%}

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
		fprintf(fp2,"At line No %d start : program\n",line_count);
		$$->setName($1->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());

	}
	;

program : program unit 
	{
		fprintf(fp2,"At line No %d program : program unit\n",line_count);
		$$->setName($1->getName()+$2->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
	| unit	{fprintf(fp2,"At line No %d program : unit\n",line_count);
		$$->setName($1->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	;
	
unit : var_declaration
	{
		fprintf(fp2,"At line No %d unit : var_declaration\n",line_count);
		$$->setName($1->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
     | func_declaration
	{
		fprintf(fp2,"At line No %d unit : func_declaration\n",line_count);
		$$->setName($1->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
     | func_definition
	{
		fprintf(fp2,"At line No %d unit : func_definition\n",line_count);
		$$->setName($1->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON	
	{

		if(table->Lookup($2->getName())==0)
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
		fprintf(fp2,"At line No %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	
	}
		| type_specifier ID LPAREN RPAREN SEMICOLON
			{
				if(table->Lookup($2->getName())==0)
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
				fprintf(fp2,"At line No %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n",line_count);
				$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName());
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
			}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN
	{
		if(table->Lookup($2->getName())==0)
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
	} compound_statement
	{
		fprintf(fp2,"At line No %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$7->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
		| type_specifier ID LPAREN RPAREN 
			{
				if(table->Lookup($2->getName())==0)
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
			} compound_statement	
		{
			fprintf(fp2,"At line No %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n",line_count);
			$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$6->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
			
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID	
	{
		fprintf(fp2,"At line No %d parameter_list  : parameter_list COMMA type_specifier ID\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
		parameterList.push_back($3->getType());
		parameterNames.push_back(make_pair($3->getType(),$4->getName()));
	}
		| parameter_list COMMA type_specifier	
		{
			fprintf(fp2,"At line No %d parameter_list  : parameter_list COMMA type_specifier\n",line_count);
			$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
			parameterList.push_back($3->getType());
		}
 		| type_specifier ID	
		 {
			 fprintf(fp2,"At line No %d parameter_list  : type_specifier ID\n",line_count);
			 $$->setName($1->getName()+" "+$2->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
			parameterList.push_back($1->getType());
			parameterNames.push_back(make_pair($1->getType(),$2->getName()));
			}
		| type_specifier
			{
				fprintf(fp2,"At line No %d parameter_list  : type_specifier\n",line_count);
				$$->setName($1->getName());
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
				parameterList.push_back($1->getType());
			}
 		;

 		
compound_statement : LCURL {table->EnterScope(11);
 while(!parameterNames.empty())
{
	table->Insert(parameterNames.back().second,"ID");
	table->Lookup(parameterNames.back().second)->data_type=parameterNames.back().first;
	parameterNames.pop_back();
}} statements RCURL	
	{
		fprintf(fp2,"At line No %d compound_statement : LCURL statements RCURL\n",line_count);
		$$->setName($1->getName()+" "+$3->getName()+" "+$4->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
		table->ExitScope();
	}
 		    | LCURL {table->EnterScope(11);
			 while(!parameterNames.empty())
{
				table->Insert(parameterNames.back().second,"ID");
				table->Lookup(parameterNames.back().second)->data_type=parameterNames.back().first;
				parameterNames.pop_back();
			}} RCURL	
			 {
				 fprintf(fp2,"At line No %d compound_statement : LCURL RCURL	compound_statement\n",line_count);
				 $$->setName($1->getName()+" "+$3->getName());
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
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
		fprintf(fp2,"At line No %d var_declaration : type_specifier declaration_list SEMICOLON\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
 		 ;
 		 
type_specifier	: INT	
	{
		fprintf(fp2,"At line No %d type_specifier	: INT\n",line_count);
		$$->setName($1->getName());
		$$->setType("INT");
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
 		| FLOAT
		 	{
				 fprintf(fp2,"At line No %d type_specifier	:  FLOAT\n",line_count);
				 $$->setName($1->getName());
				 $$->setType("FLOAT");
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
			}
 		| VOID	
		 {
			 fprintf(fp2,"At line No %d type_specifier	: VOID\n",line_count);
			 $$->setName($1->getName());
			 $$->setType("VOID");
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
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
		
		fprintf(fp2,"At line No %d declaration_list : declaration_list COMMA ID\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
		
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
				}
			   fprintf(fp2,"At line No %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n",line_count);
			   $$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName());
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
				

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
				
			   fprintf(fp2,"At line No %d declaration_list : ID\n",line_count);
			   $$->setName($1->getName());
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
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
			   }
				
			   fprintf(fp2,"At line No %d declaration_list :ID LTHIRD CONST_INT RTHIRD\n",line_count);
			   $$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName());
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
				
				
		   }
 		  ;
 		  
statements : statement	
	{
	fprintf(fp2,"At line No %d statements : statement\n",line_count);
	$$->setName($1->getName());
	fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
	   | statements statement
	   {
		   fprintf(fp2,"At line No %d statements : statements statement\n",line_count);
	   		$$->setName($1->getName()+" "+$2->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
	   ;
	   
statement : var_declaration	{fprintf(fp2,"At line No %d statement : var_declaration\n",line_count);
							$$->setName($1->getName());
							fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	  | expression_statement	{fprintf(fp2,"At line No %d statement : expression_statement\n",line_count);
	  							$$->setName($1->getName());
								fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	  | compound_statement	{fprintf(fp2,"At line No %d statement : compound_statement\n",line_count);
	  						$$->setName($1->getName());
							fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement	
	  {
		  fprintf(fp2,"At line No %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n",line_count);
	  	$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName()+" "+$7->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE	
	  {
		  fprintf(fp2,"At line No %d statement : IF LPAREN expression RPAREN statement\n",line_count);
	  		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
	  | IF LPAREN expression RPAREN statement ELSE statement	{fprintf(fp2,"At line No %d statement : IF LPAREN expression RPAREN statement ELSE statement\n",line_count);
	  															$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName()+" "+$7->getName());
																fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	  | WHILE LPAREN expression RPAREN statement	{fprintf(fp2,"At line No %d statement : WHILE LPAREN expression RPAREN statement\n",line_count);
	  												$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName());
													fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	   {
		  	 if(table->Lookup($3->getName())==0)
			   {
				   fprintf(fp3,"Error at Line No %d : Undeclared Variable : %s \n\n",line_count,$3->getName().c_str());
				   error_count++;
			   }
		    fprintf(fp2,"At line No %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n",line_count);
	  		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
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
		  fprintf(fp2,"At line No %d statement : RETURN expression SEMICOLON\n",line_count);
	  		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
		| error SEMICOLON {yyerrok;}
	  ;
	  
expression_statement 	: SEMICOLON		{fprintf(fp2,"At line No %d expression_statement 	: SEMICOLON\n",line_count);
										$$->setName($1->getName());
										fprintf(fp2,"%s\n\n",$$->getName().c_str());}		
			| expression SEMICOLON 	
			{
				$$->data_type=$1->data_type;
				fprintf(fp2,"At line No %d expression_statement 	: expression SEMICOLON\n",line_count);
				$$->setName($1->getName()+" "+$2->getName());
				fprintf(fp2,"%s\n\n",$$->getName().c_str());
			}
			;
	  
variable : ID 		{
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
					}
					fprintf(fp2,"At line No %d variable : ID \n",line_count);
					$$->setName($1->getName());
					$$->setType("ID");
					fprintf(fp2,"%s\n\n",$$->getName().c_str());
					}
	 | ID LTHIRD expression RTHIRD 	{
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
		 							fprintf(fp2,"At line No %d variable : ID LTHIRD expression RTHIRD\n",line_count);
	 								$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName());
									fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	 ;
	 
 expression : logic_expression	{
	 							$$->data_type=$1->data_type;
	 							fprintf(fp2,"At line No %d expression : logic_expression\n",line_count);
 								$$->setName($1->getName());
								fprintf(fp2,"%s\n\n",$$->getName().c_str());}
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
		   fprintf(fp2,"At line No %d expression : variable ASSIGNOP logic_expression\n",line_count);
	   		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}	
	   ;
			
logic_expression : rel_expression 	
	{
		$$->is_array=$1->is_array;
		$$->data_type=$1->data_type;
		fprintf(fp2,"At line No %d logic_expression : rel_expression\n",line_count);
		$$->setName($1->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}	
		 | rel_expression LOGICOP rel_expression 	
		{
			$$->data_type="INT";
			fprintf(fp2,"At line No %d logic_expression : rel_expression LOGICOP rel_expression\n",line_count);
		 	$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
		 ;
			
rel_expression	: simple_expression 			
	{
		$$->is_array=$1->is_array;
		$$->data_type=$1->data_type;
		fprintf(fp2,"At line No %d rel_expression	: simple_expression\n",line_count);
		$$->setName($1->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
		| simple_expression RELOP simple_expression		
		{
			$$->data_type="INT";
			fprintf(fp2,"At line No %d rel_expression	: simple_expression RELOP simple_expression\n",line_count);
			$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
		}
		;
				
simple_expression : term 	{
							$$->is_array=$1->is_array;
							$$->data_type=$1->data_type;
							fprintf(fp2,"At line No %d simple_expression : term \n",line_count);
							$$->setName($1->getName());
							fprintf(fp2,"%s\n\n",$$->getName().c_str());
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
			 fprintf(fp2,"At line No %d simple_expression : simple_expression ADDOP term \n",line_count);
		  									$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
											fprintf(fp2,"%s\n\n",$$->getName().c_str());}
		  ;
					
term :	unary_expression	{$$->data_type=$1->data_type;
							fprintf(fp2,"At line No %d term :	unary_expression\n",line_count);
							$$->setName($1->getName());
							fprintf(fp2,"%s\n\n",$$->getName().c_str());}
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
		 							fprintf(fp2,"At line No %d term :	term MULOP unary_expression\n",line_count);
	 								$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
									fprintf(fp2,"%s\n\n",$$->getName().c_str());}
     ;

unary_expression : ADDOP unary_expression 	{$$->data_type=$2->data_type;
											fprintf(fp2,"At line No %d unary_expression : ADDOP unary_expression\n",line_count);
											$$->setName($1->getName()+" "+$2->getName());
											fprintf(fp2,"%s\n\n",$$->getName().c_str());} 
		 | NOT unary_expression 	{$$->data_type=$2->data_type;
			 						fprintf(fp2,"At line No %d unary_expression : NOT unary_expression\n",line_count);
		 							$$->setName($1->getName()+" "+$2->getName());
									fprintf(fp2,"%s\n\n",$$->getName().c_str());} 
		 | factor 	{
			 		$$->is_array=$1->is_array;
			 		$$->data_type=$1->data_type;
			 		fprintf(fp2,"At line No %d unary_expression :factor\n",line_count);
		 			$$->setName($1->getName());
					fprintf(fp2,"%s\n\n",$$->getName().c_str());} 
		 ;
	
factor	: variable 	{
						$$->is_array=$1->is_array;
						$$->data_type=$1->data_type;
						fprintf(fp2,"At line No %d factor	: variable\n",line_count);
						$$->setName($1->getName()); 
						fprintf(fp2,"%s\n\n",$$->getName().c_str());
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
		
		fprintf(fp2,"At line No %d factor	: ID LPAREN argument_list RPAREN\n",line_count);
	  	$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}
	| LPAREN expression RPAREN	{
		$$->data_type=$2->data_type;
		fprintf(fp2,"At line No %d factor	: LPAREN expression RPAREN\n",line_count);
		$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
		fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}

	| CONST_INT 	{
					$$->data_type="INT";
					fprintf(fp2,"At line No %d factor	: CONST_INT\n",line_count);
					$$->setName($1->getName());
					fprintf(fp2,"%s\n\n",$$->getName().c_str());
					}
	| CONST_FLOAT	{
					$$->data_type="FLOAT";
					fprintf(fp2,"At line No %d factor	: CONST_FLOAT\n",line_count);
					$$->setName($1->getName()); 
					fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	| variable INCOP 	{$$->data_type=$1->data_type;
						fprintf(fp2,"At line No %d factor	: variable INCOP\n",line_count);
						$$->setName($1->getName()+" "+$2->getName());
						fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	| variable DECOP	{$$->data_type=$1->data_type;
						fprintf(fp2,"At line No %d factor	: variable DECOP\n",line_count);
						$$->setName($1->getName()+" "+$2->getName());
						fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	;
	
argument_list : arguments	
{
	i=0;
	while(i<$1->argumentList.size())
		{
			$$->argumentList[i]=$1->argumentList[i];
			i++;
		}
	
	fprintf(fp2,"At line No %d argument_list : arguments\n",line_count);
	$$->setName($1->getName());
	fprintf(fp2,"%s\n\n",$$->getName().c_str());
}
			  |	{fprintf(fp2,"At line No %d argument_list : \n",line_count);}
			  ;
	
arguments : arguments COMMA logic_expression	
	{
			
			i=0;
			while(i<$1->argumentList.size())
			{
				argument=$1->argumentList[i];
				$$->argumentList[i]=argument;
				i++;
			}
			$$->argumentList.push_back($3->data_type);
			fprintf(fp2,"At line No %d arguments : arguments COMMA logic_expression\n",line_count);
			$$->setName($1->getName()+" "+$2->getName()+" "+$3->getName());
			fprintf(fp2,"%s\n\n",$$->getName().c_str());
	}

	      | logic_expression	
		  {
				$$->argumentList.push_back($1->data_type);
				fprintf(fp2,"At line No %d arguments : logic_expression\n",line_count);
				$$->setName($1->getName()); 
				fprintf(fp2,"%s\n\n",$$->getName().c_str());}
	      ;
 

%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	
	fp2= fopen(argv[2],"w");
	fp3= fopen(argv[3],"w");
	table=new SymbolTable(11);

	yyin=fp;
	yyparse();
	fprintf(fp2,"			Symbol Table\n\n");
	table->PrintAll();
	fprintf(fp3,"Total Errors: %d \n",error_count);	
	fprintf(fp2,"Total Errors: %d \n",error_count);	
	fprintf(fp2,"Total Lines: %d \n",--line_count);	


	fclose(fp2);
	fclose(fp3);
	
	return 0;
}

