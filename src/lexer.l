/*
 * =====================================================================================
 *
 *       Filename:  lexer.l
 *
 *    Description:  Manage scanner of zsbc input.
 *
 *        Version:  1.0
 *        Created:  03/06/2015 23:22:00
 *       Revision:  none
 *       Compiler:  flex
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */

/* Inspired from
 * http://www-h.eng.cam.ac.uk/help/tpl/languages/flexbison/
 */


%{

#include <string.h>
#include <stdarg.h>

#include "common.h"
#include "numwrap.h"
#include "expr.h"
#include "parser.h"

#define YY_NO_INPUT
#define YY_NO_UNISTD_H

int yycolumn = 1;
void cleanup_inputnumber(char *s);

void yyerror(char *s, ...);

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;

%}

%option 8bit
%option warn
%option yylineno
%option noyywrap
%option nounput

int			([A-Z0-9]|\\\n)+
/*unicodeAny	[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEF][\x80-\xBF][\x80-\xBF]*/
/*identifier	([_[:alpha:]]|{unicodeAny})([[:alnum:]]|{unicodeAny})**/
identifier	[a-z][[:alnum:]]*

%%

[ \t]+		{ }

"="			return '=';
"+"			return '+';
"-"			return '-';
"*"			return '*';
"/"			return '/';
"("			return '(';
")"			return ')';
"^"			return '^';
"%"			return '%';

{int}	{
	cleanup_inputnumber(yytext);
	yylval.num = num_construct_from_str(yytext, 10);
	return INTEGER;
}

(?i:quit)		return QUIT;
(?i:exit)		return QUIT;
out				return OUTPUT;
(?i:outbase)	return OUTPUT;
(?i:vars)		return VARS;
(?i:variables)	return VARS;

{identifier}	{
	unsigned int l = strlen(yytext) + 1;
	yylval.id = (char *)malloc(l);
	s_strncpy(yylval.id, yytext, l);
	return IDENTIFIER;
}

"\n"	{ yycolumn = 1; return NEWLINE; }
\\\n
.		{ yyerror("illegal character: %s", yytext); }

%%

void cleanup_inputnumber(char *s)
{
	char *src = s;
	char *dst = s;
	while (*src != '\0') {
		if (*src == '\\' && src[1] == '\n') {
			src += 2;
			++yylineno;
		} else {
			*dst++ = *src++;
		}
	}
	*dst = '\0';
}

void loc_reset()
{
	yylloc.first_column = 1;
	yylloc.first_line = 1;
	yylloc.last_column = 1;
	yylloc.last_line = 1;
	yycolumn = 1;
	yylineno = 1;
}

void yyerror(char *s, ...)
{
	va_list ap;
	va_start(ap, s);

	if(yylloc.first_line) {
		fprintf(stderr, "%d.%d-%d.%d: ", yylloc.first_line, yylloc.first_column,
		yylloc.last_line, yylloc.last_column);
	}
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

