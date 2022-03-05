%option noyywrap
%x SLCOMMENT
%x SLCINTER
%x MLCOMMENT
%x STRINGST
%x STRINTER
%x DUMMY
%{
#include<stdio.h>
#include<stdlib.h>
#include "1605042_Symbol_Table.cpp"
#include<bits/stdc++.h>
int line_count=1;
SymbolTable st(11);;
FILE *logout;
FILE *tokenout;
string stprint;
string commentprint;
int spelinecount;
int errorcount;
string modifyChar(char* s)
{
	string modified="a";
	if(s[1]==92 && s[2]=='n')
	{
		modified[0]='\n';
		return modified;
	}
	else if(s[1]==92 && s[2]=='v')
	{
		modified[0]='\v';
		return modified;
	}
	else if(s[1]==92 && s[2]=='0')
	{
		modified[0]='\0';
		return modified;
	}
	else if(s[1]==92 && s[2]=='b')
	{
		modified[0]='\b';
		return modified;
	}
	else if(s[1]==92 && s[2]=='a')
	{
		modified[0]='\a';
		return modified;
	}
	else if(s[1]==92 && s[2]=='r')
	{
		modified[0]='\r';
		return modified;
	}
	else if(s[1]==92 && s[2]=='f')
	{
		modified[0]='\f';
		return modified;
	}
	else if(s[1]==92 && s[2]=='t')
	{
		modified[0]='\t';
		return modified;
	}
	else if(s[1]==92 && s[2]==92)
	{
		modified[0]='\\';
		return modified;
	}
	else if(s[1]==92&& s[2]==39)
	{
		modified[0]='\'';
		return modified;
	}
	modified[0]=s[1];
	return modified;
} 	

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n

%%

{NEWLINE} {line_count++;}

"if"	{
			fprintf(tokenout,"<IF>");
			fprintf(logout,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);
		}
"do"	{
			fprintf(tokenout,"<DO>");
			fprintf(logout,"Line no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);
		}
"for"	{
			fprintf(tokenout,"<FOR>");
			fprintf(logout,"Line no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);
		}
"int"	{
			fprintf(tokenout,"<INT>");
			fprintf(logout,"Line no %d: TOKEN <INT> Lexeme %s found\n",line_count,yytext);
		}
"float"	{
			fprintf(tokenout,"<FLOAT>");
			fprintf(logout,"Line no %d: TOKEN <FLOAT> Lexeme %s found\n",line_count,yytext);
		}
"void"	{
			fprintf(tokenout,"<VOID>");
			fprintf(logout,"Line no %d: TOKEN <VOID> Lexeme %s found\n",line_count,yytext);
		}
"switch"	{
			fprintf(tokenout,"<SWITCH>");
			fprintf(logout,"Line no %d: TOKEN <SWITCH> Lexeme %s found\n",line_count,yytext);
		}
"default"	{
			fprintf(tokenout,"<DEFAULT>");
			fprintf(logout,"Line no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);
		}
		
"else"	{
			fprintf(tokenout,"<ELSE>");
			fprintf(logout,"Line no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);
		}
"while"	{
			fprintf(tokenout,"<WHILE>");
			fprintf(logout,"Line no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);
		}
"break"	{
			fprintf(tokenout,"<BREAK>");
			fprintf(logout,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
		}
"char"	{
			fprintf(tokenout,"<CHAR>");
			fprintf(logout,"Line no %d: TOKEN <CHAR> Lexeme %s found\n",line_count,yytext);
		}
"double" 	{
			fprintf(tokenout,"<DOUBLE>");
			fprintf(logout,"Line no %d: TOKEN <DOUBLE> Lexeme %s found\n",line_count,yytext);
		}
"return"	{
			fprintf(tokenout,"<RETURN>");
			fprintf(logout,"Line no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);
		}
"case"	{
			fprintf(tokenout,"<CASE>");
			fprintf(logout,"Line no %d: TOKEN <CASE> Lexeme %s found\n",line_count,yytext);
		}
"continue"	{
			fprintf(tokenout,"<CONTINUE>");
			fprintf(logout,"Line no %d: TOKEN <CONTINUE> Lexeme %s found\n",line_count,yytext);
		}

"++"|"--"	{
			fprintf(tokenout,"<INCOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <INCOP> Lexeme %s found\n",line_count,yytext);
			fclose(logout);
			st.Insert(yytext,"INCOP");
			logout= fopen("1605042_log.txt","a");
			}

"+"|"-"		{
			fprintf(tokenout,"<ADDOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
			fclose(logout);
			st.Insert(yytext,"ADDOP");
			logout= fopen("1605042_log.txt","a");
			}
"*"|"/"|"%" {
			fprintf(tokenout,"<MULOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <MULOP> Lexeme %s found\n",line_count,yytext);
			fclose(logout);
			st.Insert(yytext,"MULOP");
			logout= fopen("1605042_log.txt","a");
			}
"<"|"<="|">"|">="|"=="|"!="	{
							fprintf(tokenout,"<RELOP,%s>",yytext);
							fprintf(logout,"Line no %d: TOKEN <RELOP> Lexeme %s found\n",line_count,yytext);
							fclose(logout);
							st.Insert(yytext,"RELOP");
							logout= fopen("1605042_log.txt","a");
							}	
"&&"|"\|\|"	{
			fprintf(tokenout,"<LOGICOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n",line_count,yytext);
			fclose(logout);
			st.Insert(yytext,"LOGICOP");
			logout= fopen("1605042_log.txt","a");
			}
"="	{
			fprintf(tokenout,"<ASSIGNOP,%s>",yytext);
			fprintf(logout,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n",line_count,yytext);
			fclose(logout);
			st.Insert(yytext,"ASSIGNOP");
			logout= fopen("1605042_log.txt","a");
			}
"&"|"\|"|"^"|"<<"|">>"	{
						fprintf(tokenout,"<BITOP,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <BITOP> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"BITOP");
						logout= fopen("1605042_log.txt","a");
						}
"!"						{
						fprintf(tokenout,"<NOT,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <NOT> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"NOT");
						logout= fopen("1605042_log.txt","a");
						}
"\("						{
						fprintf(tokenout,"<LPAREN,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <LPAREN> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"LPAREN");
						logout= fopen("1605042_log.txt","a");
						}
"\)"						{
						fprintf(tokenout,"<RPAREN,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <RPAREN> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"RPAREN");
						logout= fopen("1605042_log.txt","a");
						}
"\{"						{
						fprintf(tokenout,"<LCURL,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <LCURL> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"LCURL");
						logout= fopen("1605042_log.txt","a");
						}
"\}"						{
						fprintf(tokenout,"<RCURL,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <RCURL> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"RCURL");
						logout= fopen("1605042_log.txt","a");
						}
"\["						{
						fprintf(tokenout,"<LTHIRD,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <LTHIRD> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"LTHIRD");
						logout= fopen("1605042_log.txt","a");
						}
"\]"						{
						fprintf(tokenout,"<RTHIRD,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <RTHIRD> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"RTHIRD");
						logout= fopen("1605042_log.txt","a");
						}
"\,"						{
						fprintf(tokenout,"<COMMA,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <COMMA> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"COMMA");
						logout= fopen("1605042_log.txt","a");
						}
";"						{
						fprintf(tokenout,"<SEMICOLON,%s>",yytext);
						fprintf(logout,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n",line_count,yytext);
						fclose(logout);
						st.Insert(yytext,"SEMICOLON");
						logout= fopen("1605042_log.txt","a");
						}


{DIGIT}+ 	{
				fprintf(tokenout,"<CONST_INT,%s>",yytext);
				fprintf(logout,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,yytext);
				fclose(logout);
				st.Insert(yytext,"CONST_INT");
				logout= fopen("1605042_log.txt","a");
			}
({DIGIT}*\.{DIGIT}+([E][-+]?{DIGIT}+)?)|({DIGIT}+([E][-+]?{DIGIT}+))|({DIGIT}+\.{DIGIT}*([E][-+]?{DIGIT}+)?)	{
																		fprintf(tokenout,"<CONST_FLOAT, %s>",yytext);
																		fprintf(logout,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
																		fclose(logout);
																		st.Insert(yytext,"CONST_FLOAT");
																		logout= fopen("1605042_log.txt","a");
																	}


\'"\\"\'	{
	errorcount++;
	fprintf(logout,"Error at line %d:	Unterminated character %s\n",line_count,yytext);
}


\'.\'|\'"\\t"\'|\'"\\n"\'|\'"\\0"\'|\'"\\a"\'|\'"\\b"\'|\'"\\f"\'|\'"\\r"\'|\'"\\v"\'|\'"\\\'"\'|\'"\\\\"\'	{ 
																												string s=modifyChar(yytext);
																											
																												char carray[s.size()+1];
																												int i;
																												for(i=0;i<s.size();i++)
																												{
																													carray[i]=s[i];
																												}
																												carray[s.size()]='\0';
																												fprintf(tokenout,"<CONST_CHAR, %s>",carray);
																												fprintf(logout,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
																												fclose(logout);
																												st.Insert(s,"CONST_CHAR");
																												logout= fopen("1605042_log.txt","a");
																											}	

[_a-zA-Z][_a-zA-Z0-9]*	{
							fprintf(tokenout,"<ID,%s>",yytext);
							fprintf(logout,"Line no %d: TOKEN <ID> Lexeme %s found\n",line_count,yytext);
							fclose(logout);
							st.Insert(yytext,"ID");
							logout= fopen("1605042_log.txt","a");
						}		

"//"	{
			commentprint.clear();
			spelinecount=line_count;
			commentprint.push_back('/');
			commentprint.push_back('/');
			BEGIN SLCOMMENT;
		}
<SLCOMMENT>[\n\r]|"\n\r"	{
							char commentarr[commentprint.size()+1];
							int i;
							for(i=0;i<commentprint.size();i++)
							{
								commentarr[i]=commentprint[i];
							}
							commentarr[i]='\0';
							fprintf(logout,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n",spelinecount,commentarr);
							BEGIN INITIAL;
						}
<SLCOMMENT><<EOF>>		{
							char commentarr[commentprint.size()+1];
							int i;
							for(i=0;i<commentprint.size();i++)
							{
									commentarr[i]=commentprint[i];
							}
							commentarr[i]='\0';
							fprintf(logout,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n",spelinecount,commentarr);
							line_count--;
							fclose(logout);
							st.PrintAll();
							logout= fopen("1605042_log.txt","a");
							fprintf(logout,"Total Lines : %d\n",line_count);
							fprintf(logout,"Total Errors: %d",errorcount);
							return 0;
						}
<SLCOMMENT>"\\"	{
					commentprint.push_back('\\');
					BEGIN SLCINTER;			
				}
<SLCOMMENT>.		{
											commentprint.push_back(yytext[0]);
									}
<SLCINTER>{NEWLINE}	{
						line_count++;
						commentprint.push_back('\n');
						BEGIN	SLCOMMENT;
					}
<SLCINTER>"\\"	{
					commentprint.push_back('\\');
				}
<SLCINTER>[^\n\r\\]	{
							commentprint.push_back(yytext[0]);
							BEGIN SLCOMMENT;
					}
<SLCINTER><<EOF>>		{
							char commentarr[commentprint.size()+1];
							int i;
							for(i=0;i<commentprint.size();i++)
							{
									commentarr[i]=commentprint[i];
							}
							commentarr[i]='\0';
							fprintf(logout,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n",spelinecount,commentarr);
							line_count--;
							fclose(logout);
							st.PrintAll();
							logout= fopen("1605042_log.txt","a");
							fprintf(logout,"Total Lines : %d\n",line_count);
							fprintf(logout,"Total Errors: %d",errorcount);
							return 0;
						}
"/*"	{
			commentprint.clear();
			spelinecount=line_count;
			commentprint.push_back('/');
			commentprint.push_back('*');
			BEGIN MLCOMMENT;
		}
<MLCOMMENT>"*/"	{
					commentprint.push_back('*');
					commentprint.push_back('/');
					char commentarr[commentprint.size()+1];
					int i;
					for(i=0;i<commentprint.size();i++)
					{
								commentarr[i]=commentprint[i];
					}
					commentarr[i]='\0';
					fprintf(logout,"Line no %d: TOKEN <COMMENT> Lexeme %s found\n",spelinecount,commentarr);
					BEGIN INITIAL;
				}
<MLCOMMENT><<EOF>>	{
					char commentarr[commentprint.size()+1];
					int i;
					for(i=0;i<commentprint.size();i++)
					{
								commentarr[i]=commentprint[i];
					}
					commentarr[i]='\0';
					errorcount++;
					fprintf(logout,"Error at line %d:	Unterminated comment %s\n",spelinecount,commentarr);
					line_count--;
					fclose(logout);
					st.PrintAll();
					logout= fopen("1605042_log.txt","a");
					fprintf(logout,"Total Lines : %d\n",line_count);
					fprintf(logout,"Total Errors: %d",errorcount);
					return 0;
				}
<MLCOMMENT>{NEWLINE}	{
							line_count++;
							commentprint.push_back('\n');
						}
<MLCOMMENT>.	{
									commentprint.push_back(yytext[0]);
								}


"\""	{
			stprint.clear();
			stprint.push_back('"');
			BEGIN STRINGST;
			spelinecount=line_count;
		}
<STRINGST>{NEWLINE}	{
	char carr[stprint.size()+1];
					int i,j;
					for(i=0,j=0;i<stprint.size();i++,j++)
					{
						carr[j]=stprint[i];	
					}
					carr[j]='\0';
					errorcount++;
					fprintf(logout,"Error at line %d:	Unterminated string %s\n",spelinecount,carr);
					line_count++;
					BEGIN INITIAL;
					}
<STRINGST><<EOF>>	{
	char carr[stprint.size()+1];
					int i,j;
					for(i=0,j=0;i<stprint.size();i++,j++)
					{
						carr[j]=stprint[i];	
					}
					carr[j]='\0';
					errorcount++;
					fprintf(logout,"Error at line %d:	Unterminated string found %s\n",spelinecount,carr);
					line_count--;
					fclose(logout);
					st.PrintAll();
					logout= fopen("1605042_log.txt","a");
					fprintf(logout,"Total Lines : %d\n",line_count);
					fprintf(logout,"Total Errors: %d",errorcount);
					return 0;
					}
<STRINGST>"\""	{
					stprint.push_back('"');
					int i,j,k=0;
					for(int i=0;i<stprint.size()-1;i++)
					{
						if(stprint[i]==92&&(stprint[i+1]=='n'||stprint[i+1]=='t'||stprint[i+1]=='0'||stprint[i+1]==92||stprint[i+1]=='a'||stprint[i+1]=='b'||stprint[i+1]=='v'||stprint[i+1]=='\''||stprint[i+1]=='f'||stprint[i+1]=='"'||stprint[i+1]=='r'||stprint[i+1]=='\n'||stprint[i+1]=='\r'))
						{
							k=i+1;
							i++;
						}
					}
					if(k!=stprint.size()-1)
					{
						char carr[stprint.size()+1];
						for(i=0,j=0;i<stprint.size();i++,j++)
						{
							carr[j]=stprint[i];	
						}
						carr[j]='\0';
						fprintf(logout,"Line no %d: TOKEN <STRING> Lexeme %s found\n",spelinecount,carr);
						for(i=1,j=0;i<stprint.size()-1;i++,j++)
						{
							if(stprint[i]==92 && i!=stprint.size()-1)
							{
								if(stprint[i+1]=='n')
								{
									carr[j]='\n';
									i++;
									continue;
								}
								else if(stprint[i+1]=='t')
								{
									carr[j]='\t';
									i++;
									continue;
								}
								else if(stprint[i+1]=='0')
								{
									carr[j]='\0';
									i++;
									continue;
								}
								else if(stprint[i+1]==92)
								{
									carr[j]='\\';
									i++;
									continue;
								}
								else if(stprint[i+1]=='a')
								{
									carr[j]='\a';
									i++;
									continue;
								}
								else if(stprint[i+1]=='b')
								{
									carr[j]='\b';
									i++;
									continue;
								}
								else if(stprint[i+1]=='v')
								{
									carr[j]='\v';
									i++;
									continue;
								}
								else if(stprint[i+1]=='\'')
								{
									carr[j]='\'';
									i++;
									continue;
								}
								else if(stprint[i+1]=='f')
								{
									carr[j]='\f';
									i++;
									continue;
								}
								else if(stprint[i+1]=='"')
								{
									carr[j]='\"';
									i++;
									continue;
								}
								else if(stprint[i+1]=='r')
								{
									carr[j]='\r';
									i++;
									continue;
								}
								else if(stprint[i+1]=='\n'||stprint[i+1]=='\r')
								{
									i++;
									j--;
								}
								else
								{
									j--;
								}


							}
							else
							{
								carr[j]=stprint[i];
							}

						}
						carr[j]='\0';
						fprintf(tokenout,"<STRING, %s>",carr);
						BEGIN INITIAL;

					}
					
				}
<STRINGST>"\\"	{
					stprint.push_back(yytext[0]);
					BEGIN STRINTER;
				}
<STRINGST>.	{
				stprint.push_back(yytext[0]);
			}

<STRINTER>{NEWLINE}	{
								stprint.push_back(yytext[0]);
								line_count++;
								BEGIN STRINGST;
							}
<STRINTER>[^\n\r]	{
							stprint.push_back(yytext[0]);
							BEGIN STRINGST;
						}

{WHITESPACE}	{}
{DIGIT}*\.({DIGIT}*)?(\.({DIGIT}*)?)+	{
										errorcount++;
										fprintf(logout,"Error at line %d:	Too many decimal point %s\n",line_count,yytext);
										}
[-+]?({DIGIT}*[E][-+]?{DIGIT}*)+\.({DIGIT}|[E])*	{
										errorcount++;
										fprintf(logout,"Error at line %d:	Ill formed number %s\n",line_count,yytext);
									}
[0-9][_a-zA-Z0-9]*	{
						errorcount++;
						fprintf(logout,"Error at line %d:	Invalid suffix on number or invalid prefix on identifier %s\n",line_count,yytext);
					}
\'..+\'		{
				errorcount++;
				fprintf(logout,"Error at line %d:	Multi character constant error %s\n",line_count,yytext);
			}
\'[^\'\n\r]*[\n\r]	{
					errorcount++;
					fprintf(logout,"Error at line %d:	Unterminated character constant error %s\n",line_count,yytext);
					}
"\'\'"	{
					errorcount++;
					fprintf(logout,"Error at line %d:	Empty character constant error %s\n",line_count,yytext);
}
<<EOF>>	{
	line_count--;
	fclose(logout);
	st.PrintAll();
	logout= fopen("1605042_log.txt","a");
	fprintf(logout,"Total Lines : %d\n",line_count);
	fprintf(logout,"Total Errors: %d",errorcount);
	return 0;
}
.	{
	errorcount++;
	fprintf(logout,"Error at line %d:	Unrecognized character %s\n",line_count,yytext);
}







												

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	logout= fopen("1605042_log.txt","w");
	tokenout= fopen("1605042_token.txt","w");
	errorcount=0;
	yyin= fin;
	yylex();
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	out.close();
	return 0;
}
