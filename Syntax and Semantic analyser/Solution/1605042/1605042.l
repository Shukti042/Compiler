%option noyywrap
%x SLCOMMENT
%x SLCINTER
%x MLCOMMENT
%x STRINGST
%x STRINTER
%x DUMMY
%{
#include "1605042_Symbol_Table.cpp"
#define YYSTYPE SymbolInfo*
#include "y.tab.h"
extern YYSTYPE yylval;
extern int line_count;
void yyerror(char *);
%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n

%%

{NEWLINE} {line_count++;}

"if"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"IF");
			yylval = s;
			return IF;
		}
"for"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"FOR");
			yylval = s;
			return FOR;
		}
"int"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"INT");
			yylval = s;
			return INT;
		}
"float"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"FLOAT");
			yylval = s;
			return FLOAT;
		}
"void"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"VOID");
			yylval = s;
			return VOID;
		}
"switch"	{
			
		}
"default"	{
			
		}
		
"else"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ELSE");
			yylval = s;
			return ELSE;
		}
"while"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"WHILE");
			yylval = s;
			return WHILE;
		}
"break"	{
			
		}
"char"	{
			
		}
"double" 	{
			
		}
"return"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RETURN");
			yylval = s;
			return RETURN;
		}
"case"	{
			
		}
"continue"	{
			
		}

"++"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"INCOP");
			yylval = s;
			return INCOP;
			}
"--"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"DECOP");
			yylval = s;
			return DECOP;
			}


"+"|"-"		{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ADDOP");
			yylval = s;
			return ADDOP;
			}
"*"|"/"|"%" {
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"MULOP");
			yylval = s;
			return MULOP;
			}
"<"|"<="|">"|">="|"=="|"!="	{
							SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RELOP");
							yylval = s;
							return RELOP;
							}	
"&&"|"\|\|"	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LOGICOP");
			yylval = s;
			return LOGICOP;
			}
"="	{
			SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ASSIGNOP");
			yylval = s;
			return ASSIGNOP;
			}
"&"|"\|"|"^"|"<<"|">>"	{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LOGICOP");
						yylval = s;
						return LOGICOP;
					
						}
"!"						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"NOT");
						yylval = s;
						return NOT;
						}
"\("						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LPAREN");
						yylval = s;
						return LPAREN;
						}
"\)"						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RPAREN");
						yylval = s;
						return RPAREN;
						}
"\{"						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LCURL");
						yylval = s;
						return LCURL;
						}
"\}"						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RCURL");
						yylval = s;
						return RCURL;
						}
"\["						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LTHIRD");
						yylval = s;
						return LTHIRD;
						}
"\]"						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RTHIRD");
						yylval = s;
						return RTHIRD;
						}
"\,"						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"COMMA");
						yylval = s;
						return COMMA;
						}
";"						{
						SymbolInfo *s= new  SymbolInfo(yytext, (char *)"SEMICOLON");
						yylval = s;
						return SEMICOLON;
						}


{DIGIT}+ 	{
				SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_INT");
				yylval = s;
				return CONST_INT;
			}
({DIGIT}*\.{DIGIT}+([E][-+]?{DIGIT}+)?)|({DIGIT}+([E][-+]?{DIGIT}+))|({DIGIT}+\.{DIGIT}*([E][-+]?{DIGIT}+)?)	{
																		SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_FLOAT");
																		yylval = s;
																		return CONST_FLOAT;
																	}



[_a-zA-Z][_a-zA-Z0-9]*	{
							SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ID");
							yylval = s;
							return ID;
						}	
"//"	{
			BEGIN SLCOMMENT;
		}
<SLCOMMENT>[\n\r]|"\n\r"	{
							BEGIN INITIAL;
						}
<SLCOMMENT>"\\"	{
					BEGIN SLCINTER;			
				}
<SLCOMMENT>.		{
									}
<SLCINTER>{NEWLINE}	{
						line_count++;
						BEGIN	SLCOMMENT;
					}
<SLCINTER>"\\"	{
				}
<SLCINTER>[^\n\r\\]	{
							BEGIN SLCOMMENT;
					}
"/*"	{
			BEGIN MLCOMMENT;
		}
<MLCOMMENT>"*/"	{
					BEGIN INITIAL;
				}
<MLCOMMENT>{NEWLINE}	{
							line_count++;
						}
<MLCOMMENT>.	{
								}	

{WHITESPACE}	{}









												

%%

