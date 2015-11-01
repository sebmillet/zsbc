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

#ifndef _MSC_VER
#include <unistd.h>
#endif

#define YY_NO_UNISTD_H

int yycolumn = 1;
void cleanup_inputnumber(char *s);

	/* Defined in this file */
void yyerror(char *s, ...);

void rl_input(char *buf, int *result, int max);

	/* the 2 below are defined in main.c */
FILE *input_get_next();
const char *input_get_name();

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;

	/* Have input call the following function */
#undef  YY_INPUT
#define YY_INPUT(buf,result,max_size) \
		rl_input((char *)buf, &result, max_size)

%}

%option 8bit
%option warn
%option yylineno
%option nounput

number			([A-Z0-9])([A-Za-z0-9]|\\\n)*(\.([A-Za-z0-9]|\\\n)*)?|\.([A-Za-z0-9]|\\\n)+
/*unicodeAny	[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEF][\x80-\xBF][\x80-\xBF]*/
/*identifier	([_[:alpha:]]|{unicodeAny})([[:alnum:]]|{unicodeAny})**/
identifier		[a-z_][[:alnum:]_]*|\.
string			\"[^\"]*\"

%%

	/*
	   This code is not very efficient. bc's way is much more powerful
	   (it manages the input directly, without regex...).
	   BUT this approach avoids opening the hood of input file stream
	   reading code. It just relies on regex management of flex.
	*/
\/\*([^*]|\n|(\*[^/]))*\*\/ {
/*    int i;*/
/*    for (i = 0; yytext[i] != '\0'; ++i) {*/
/*        if (yytext[i] == '\n')*/
/*            ++yylineno;*/
/*    }*/
/*    fprintf(stderr, "\n\n[=====\n");*/
/*    fputs(yytext, stderr);*/
/*    fprintf(stderr, "\n=====]\n\n");*/
}

[ \t]+		{ }

\\\n		{ }

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
	int r;
	if ((r = num_construct_from_str(yytext, &yylval.num)) != ERROR_NONE) {
		yyerror("Illegal number");
	} else
		return INTEGER;
}

	/* The sequence below (left commented) is for insensitive matching */
	/* (?i:quit)		return QUIT;	*/

quit			return QUIT;
libswitch|lib	return LIBSWITCH;
liblist			return LIBLIST;
symbols			return SYMBOLS;
while			return WHILE;
for				return FOR;
define			return DEFINE;
void			return VOID;
return			return RETURN;
break			return BREAK;
continue		return CONTINUE;
if				return IF;
else			return ELSE;
auto			return AUTOLIST;
print			return PRINT;

{identifier} {
	const char *what = yytext;
	if (!strcmp(yytext, "."))
		what = VAR_LAST;

	s_alloc_and_copy(&yylval.str, what);
	return IDENTIFIER;
}

{string} {
	unsigned int len = strlen(yytext);
	assert(yytext[len - 1] == '"');
	yytext[len - 1] = '\0';

/*    int i;*/
/*    for (i = 1; yytext[i] != '\0'; ++i) {*/
/*        if (yytext[i] == '\n')*/
/*            ++yylineno;*/
/*    }*/

	s_alloc_and_copy(&yylval.str, yytext + 1);
	return STRING;
}

"\n"		{ yycolumn = 1; return NEWLINE; }

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
	out_dbg("Location reset\n");
	yylloc.first_column = 1;
	yylloc.first_line = 1;
	yylloc.last_column = 1;
	yylloc.last_line = 1;
	yycolumn = 1;
	yylineno = 1;
}

const code_location_t code_loc(const YYLTYPE yl)
{
	code_location_t loc;
	loc.is_set = TRUE;
	loc.file_name = strlen(input_get_name()) >= 1 ? input_get_name() : NULL;
	loc.first_line = yl.first_line;
	loc.first_column = yl.first_column;
	loc.last_line = yl.last_line;
	loc.last_column = yl.last_column;
	return loc;
}

void yyerror(char *s, ...)
{
	va_list ap;
	va_start(ap, s);

	out_dbg("yyerror() invocation\n");

	if (strlen(input_get_name()) >= 1)
		fprintf(stderr, "%s: ", input_get_name());
	if(yylloc.first_line) {
		fprintf(stderr, "%d.%d-%d.%d: ", yylloc.first_line, yylloc.first_column,
		yylloc.last_line, yylloc.last_column);
	}
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
	hackbc_terminate();
}

int yywrap()
{
	FILE *next = input_get_next();
	out_dbg("Call to yywrap. File given by argf_get_next(): %lu\n", next);
	out_dbg("\tyyin: %s\n", next == stdin ? "is being assigned to stdin" :
			(next == NULL ? "yyin won't be assigned, lexer terminating" : "yyin is being assigned to an input file (not stdin)"));

	loc_reset();

	if (next == NULL) {
		out_dbg("\tyywrap returns 1 (non zero means TERMINATE)\n");
		return 1;
	} else {
		out_dbg("\tyywrap returns 0 (zero means CONTINUE)\n");
		yyin = next;
		return 0;
	}

}

