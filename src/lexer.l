/*
 * =====================================================================================
 *
 *       Filename:  lexer.l
 *
 *    Description:  Manages scanner of zsbc input.
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

/*
 * Inspired from
 * http://www-h.eng.cam.ac.uk/help/tpl/languages/flexbison/
 */


%{

#include "common.h"
#include "numwrap.h"
#include "expr.h"
#include "vars.h"
#include "program.h"
#include "parser.h"

#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#define YY_NO_INPUT
#define YY_NO_UNISTD_H

int yycolumn = 1;
void cleanup_inputnumber(char *s);

	/* Defined in this file */
void yyerror(char *s, ...);

	/* the 2 below are defined in main.c */
FILE *argf_get_next();
char *argf_get_curname();

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;

%}

%option 8bit
%option warn
%option yylineno
%option nounput

number			([A-Z0-9]|\\\n)+(\.([A-Z0-9]|\\\n)*)?
/*unicodeAny	[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEF][\x80-\xBF][\x80-\xBF]*/
/*identifier	([_[:alpha:]]|{unicodeAny})([[:alnum:]]|{unicodeAny})**/
identifier		[a-z][[:alnum:]]*
string			\"[^\"]*\"

%%

[ \t]+		{ }

"="|"+="|"-="|"*="|"/="|"^="|"%=" {
	s_alloc_and_copy(&yylval.str, yytext);
	return OP_AND_ASSIGN;
}
"+"			return '+';
"-"			return '-';
"*"			return '*';
"/"			return '/';
"("			return '(';
")"			return ')';
"^"			return '^';
"%"			return '%';
"++"|"--" {
	s_alloc_and_copy(&yylval.str, yytext);
	return PLUSPLUS_MINMIN;
}
";"			return ';';
","			return ',';
"["			return '[';
"]"			return ']';
"{"			return '{';
"}"			return '}';
"||"		return LOGIC_OR;
"&&"		return LOGIC_AND;
"!"			return LOGIC_NOT;
"<"|"<="|">"|">="|"=="|"!=" {
	s_alloc_and_copy(&yylval.str, yytext);
	return COMPARISON;
}

{number} {
	cleanup_inputnumber(yytext);
	yylval.num = num_construct_from_str(yytext, 10);
	return INTEGER;
}

	/* The sequence below (left commented) is for insensitive matching */
	/* (?i:quit)		return QUIT;	*/

quit			return QUIT;
libswitch|lib	return LIBSWITCH;
liblist			return LIBLIST;
vars			return VARS;
while			return WHILE;
for				return FOR;
define			return DEFINE;
void			return VOID;
return			return RETURN;
break			return BREAK;
continue		return CONTINUE;
if				return IF;
else			return ELSE;

{identifier} {
	s_alloc_and_copy(&yylval.str, yytext);
	return IDENTIFIER;
}

{string} {
	unsigned int len = strlen(yytext);
	assert(yytext[len - 1] == '"');
	yytext[len - 1] = '\0';
	s_alloc_and_copy(&yylval.str, yytext + 1);
	return STRING;
}

"\n"		{ yycolumn = 1; return NEWLINE; }
\\\n
. {
		/* The code below is taken from bc source, with some minor variations */
	char c = yytext[0];
	if (c < ' ')
		yyerror("illegal character: ^%c", '@' + c);
	else if (c > '~')
		yyerror("illegal character: \\%03o", (int)c);
	else
		yyerror("illegal character: %c", c);
}

%%

	/*
	 * Remove escaped newlines from string = newline characters that
	 * follow a \ character.
	 * */
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

	out_dbg("yyerror() invocation\n");

	if (strlen(argf_get_curname()) >= 1)
		fprintf(stderr, "%s: ", argf_get_curname());
	if(yylloc.first_line) {
		fprintf(stderr, "%d.%d-%d.%d: ", yylloc.first_line, yylloc.first_column,
		yylloc.last_line, yylloc.last_column);
	}
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

int yywrap()
{
	FILE *next = argf_get_next();
	out_dbg("Call to yywrap. File given by argf_get_next(): %lu\n", next);
	out_dbg("\tyyin: %s\n", next == stdin ? "is being assigned to stdin" :
			(next == NULL ? "yyin won't be assigned, lexer terminating" : "yyin is being assigned to an input file (not stdin)"));

	if (next == NULL) {
		out_dbg("\tyywrap returns 1 (non zero means TERMINATE)\n");
		return 1;
	} else {
		out_dbg("\tyywrap returns 0 (zero means CONTINUE)\n");
		yyin = next;
		return 0;
	}

	loc_reset();
}

