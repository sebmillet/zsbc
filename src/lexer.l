/* lexer.l

Expression lexer.
Inspired from
   http://www-h.eng.cam.ac.uk/help/tpl/languages/flexbison/

Sébastien Millet 2015 */

%{

#include <string.h>
#include <stdarg.h>
#include <gmp.h>

#include "common.h"
#include "expr.h"
#include "parser.h"

#define YY_NO_INPUT
#define YY_NO_UNISTD_H

int yycolumn = 1;
void remove_newlines(char *s);

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;

%}

%option 8bit
%option warn
%option yylineno
%option noyywrap
%option nounput

hexint1		0x[[:xdigit:]]+
hexint2		[[:xdigit:]]+_h(ex)?
octint1		0o[0-7]+
octint2		[0-7]+_o(ct)?
binint1		0b[01]+
binint2		[01]+_b(in)?
decint		([[:digit:]]|\\\n)+
unicodeAny	[\xC2-\xDF][\x80-\xBF]|\xE0[\xA0-\xBF][\x80-\xBF]|[\xE1-\xEF][\x80-\xBF][\x80-\xBF]
identifier	([_[:alpha:]]|{unicodeAny})([[:alnum:]]|{unicodeAny})*

%%

"="		return '=';
"+"		return '+';
"-"		return '-';
"*"		return '*';
"/"		return '/';
"("		return '(';
")"		return ')';
"^"		return '^';
"%"		return '%';

{binint1}	{ yylval.mp = mpz_const_from_str(yytext + 2, 2); }

{binint2}	{
	unsigned int s = strlen(yytext);
	if (s >= 4 && !strcmp(yytext + s - 4, "_bin")) {
		yytext[s - 4] = '\0';
	} else if (s >= 2 && !strcmp(yytext + s - 2, "_b")) {
		yytext[s - 2] = '\0';
	}
	yylval.mp = mpz_const_from_str(yytext, 2);
	return INTEGER;
}

{octint1}	{ yylval.mp = mpz_const_from_str(yytext + 2, 8); return INTEGER; }

{octint2}	{
	unsigned int s = strlen(yytext);
	if (s >= 4 && !strcmp(yytext + s - 4, "_oct")) {
		yytext[s - 4] = '\0';
	} else if (s >= 2 && !strcmp(yytext + s - 2, "_o")) {
		yytext[s - 2] = '\0';
	}
	yylval.mp = mpz_const_from_str(yytext, 8);
	return INTEGER;
}

{decint}	{
	yylval.mp = mpz_const_from_str(yytext, 10);
	return INTEGER;
}

{hexint1}	{ yylval.mp = mpz_const_from_str(yytext, 0); return INTEGER; }

{hexint2}	{
	unsigned int s = strlen(yytext);
	if (s >= 4 && !strcmp(yytext + s - 4, "_hex")) {
		yytext[s - 4] = '\0';
	} else if (s >= 2 && !strcmp(yytext + s - 2, "_h")) {
		yytext[s - 2] = '\0';
	}
	yylval.mp = mpz_const_from_str(yytext, 16);
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
[ \t]+		{ }
.		{ yyerror("illegal character: %s", yytext); }

%%

void remove_newlines(char *s)
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

