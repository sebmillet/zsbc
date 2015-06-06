/* lexer.l

Expression lexer.
Inspired from
   http://www-h.eng.cam.ac.uk/help/tpl/languages/flexbison/

Sébastien Millet 2015 */

%{

#include "common.h"
#include <gmp.h>
#include <string.h>
#include "parser.h"
#include <stdarg.h>

#define YY_NO_INPUT
#define YY_NO_UNISTD_H

int yycolumn = 1;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;

#define BUILD_AND_RETURN_MP_INTEGER(m, t, b) \
	m = (mpz_t *)malloc(sizeof(mpz_t)); \
	mpz_init_set_str(*(m), t, b); \
	COUNT_MPZ_INC; \
	return INTEGER;

%}

%option 8bit
%option warn
%option yylineno
%option noyywrap
%option nounput
/*%option outfile="expr-lexer.c" header-file="expr-lexer.h"*/

hexint1		0x[[:xdigit:]]+
hexint2		[[:xdigit:]]+_h(ex)?
octint1		0o[0-7]+
octint2		[0-7]+_o(ct)?
binint1		0b[01]+
binint2		[01]+_b(in)?
decint		[[:digit:]]+
unicodeAny	[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEF][\x80-\xBF][\x80-\xBF]
identifier	([_[:alpha:]]|{unicodeAny})([[:alnum:]]|{unicodeAny})*

%%

[ \t]+		{ }

"="		return '=';
"+"		return '+';
"-"		return '-';
"*"		return '*';
"/"		return '/';
"("		return '(';
")"		return ')';
"^"		return '^';
"%"		return '%';

{binint1}	{ BUILD_AND_RETURN_MP_INTEGER(yylval.mp, yytext + 2, 2); }

{binint2}	{
	unsigned int s = strlen(yytext);
	if (s >= 4 && !strcmp(yytext + s - 4, "_bin")) {
		yytext[s - 4] = '\0';
	} else if (s >= 2 && !strcmp(yytext + s - 2, "_b")) {
		yytext[s - 2] = '\0';
	}
	BUILD_AND_RETURN_MP_INTEGER(yylval.mp, yytext, 2);
}

{octint1}	{ BUILD_AND_RETURN_MP_INTEGER(yylval.mp, yytext + 2, 8); }

{octint2}	{
	unsigned int s = strlen(yytext);
	if (s >= 4 && !strcmp(yytext + s - 4, "_oct")) {
		yytext[s - 4] = '\0';
	} else if (s >= 2 && !strcmp(yytext + s - 2, "_o")) {
		yytext[s - 2] = '\0';
	}
	BUILD_AND_RETURN_MP_INTEGER(yylval.mp, yytext, 8);
}

{decint}	{
	yylval.mp = (mpz_t *)malloc(sizeof(mpz_t));
	mpz_init_set_str(*(yylval.mp), yytext, 10);
	COUNT_MPZ_INC;
	return INTEGER;
}

{hexint1}	{ BUILD_AND_RETURN_MP_INTEGER(yylval.mp, yytext, 0); }

{hexint2}	{
	unsigned int s = strlen(yytext);
	if (s >= 4 && !strcmp(yytext + s - 4, "_hex")) {
		yytext[s - 4] = '\0';
	} else if (s >= 2 && !strcmp(yytext + s - 2, "_h")) {
		yytext[s - 2] = '\0';
	}
	BUILD_AND_RETURN_MP_INTEGER(yylval.mp, yytext, 16);
}

(?i:quit)		return QUIT;
(?i:exit)		return QUIT;
(?i:out)		return OUTPUT;
(?i:outbase)	return OUTPUT;
(?i:vars)		return VARS;
(?i:variables)	return VARS;

{identifier}	{
	unsigned int l = strlen(yytext) + 1;
	yylval.id = (char *)malloc(l);
	strncpy(yylval.id, yytext, l);
	return IDENTIFIER;
}

"\n"	{ yycolumn = 1; return NEWLINE; }
.		{ yyerror("illegal character: %s", yytext); }

%%

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

