%{
#define YYSTYPE char *
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 10000
#define MAXL 5000
int yyerror(const char* s);
int yylex(void);
FILE *yyin;

void MatToStr(int mat[], int l, int w, char* str);
void StrToMat(char *str, int mat[], int *l, int *w);
void MatAdd(int mat1[], int mat2[], int l, int w, int mat_res[]);
void MatMinus(int mat1[], int mat2[], int l, int w, int mat_res[]);
void MatMul(int mat1[], int mat2[], int l, int w, int mat_res[]);
void MatDiv(int mat1[], int mat2[], int l, int w, int mat_res[]);
void MatNeg(int mat[], int l, int w, int mat2[]);
void MatRev(int mat[], int l, int w, int mat2[]);
int MatMean(int mat[], int l, int w);
int MatSum(int mat[], int l, int w);
char* Add(char *str1, char *str2);
char* Minus(char *str1, char *str2);
char* Dot(char *str1, char *str2);
char* Div(char *str1, char *str2);
char* Mean(char *str);
char* Sum(char *str);
char* Neg(char *str);
char* Rev(char *str);
void BuildMat(int mat1[], int val, int l, int w);

void OutputRes(char *p1);
void RmWs(char* str);
char *FFormat(const char* str);
%}
%token LB RB MAT ADD MINUS DIV NEG REV DOT
%%
/* grammar rules and actions follow in {}*/

input: input line
	| line
	;

line: 	'\n'
        | expr '\n' {printf("res %s\n", $1);OutputRes($1);}
	;

// start of your grammar rules and actions 

expr: expr '+' exp2 { $$ = Add($1, $3); }
	| expr '-' exp2 { $$ = Minus($1, $3); }
	| exp2 { $$ = $1; }
	;

exp2: exp2 '*' exp3 { $$ = Dot($1, $3); }
	| exp2 '/' exp3 { $$ = Div($1, $3); }
	| exp3 { $$ = $1; }
	;

exp3: REV exp3 { $$ = Rev($2); }
	| NEG exp3 { $$ = Neg($2); }
	| exp4 { $$ = $1; }
	;

exp4: MAT { $$ = $1; }
	| '(' expr ')' { $$ = $2; }
	;

// end of your grammar rules and actions

%%
#include<ctype.h>
int main(int argc, char *argv[]){
	// If input from command line, use this
	//return yyparse();
	// If input from file, comment out above line
	// clear the result file
	FILE *fp = fopen("results.txt","w");
	if(fp==NULL){printf("fail to output\n");return -1;}
	fclose(fp);
	// load the testcases
	fp = fopen(argv[1], "r");
    	if (!fp)
    	{
        	printf ("Error reading file!\n");
        	return -1;
    	}
	// pass the testcases to parser
    	yyin = fp;
	return yyparse();
}

int yyerror(const char* s)
{
    extern int yylineno;
    extern char *yytext;
    printf("\n^%d: %s at %s #%d\n", yylineno, s, yytext, (int)(*yytext));
    return 0;
}

char *FFormat(const char* str){
	char temp[MAXL],*a;
	int i, j ,len;
	a = (char*)malloc(sizeof(a)*MAXL);
	strcpy(temp,str);
	RmWs(temp);
	len = strlen(temp);
	for(i=0; i < len; i ++){
		a[i] = temp[i];
	}
	a[i] = '\0';
	return a;
}

void OutputRes(char *p1){
	FILE *fp = fopen("results.txt","a");
	if(fp==NULL){printf("fail to output\n");return;}
	fprintf(fp,"%s\n",p1);
	fclose(fp);
	return;
}

char* Add(char *str1, char *str2){
	char *a = (char*)malloc(sizeof(char)*MAXL);
	int *mat1 = (int*)malloc(sizeof(int)*MAXL);
	int *mat2 = (int*)malloc(sizeof(int)*MAXL);
	int *mat3 = (int*)malloc(sizeof(int)*MAXL);
	int l1 = 0, w1 = 0, l2 = 0, w2 = 0;
	StrToMat(str1,mat1,&l1,&w1);
	StrToMat(str2,mat2,&l2,&w2);
	if(l1!=l2 || w1 != w2){
		if(l1 == 1 && w1 == 1){
			l1 = l2;
			w1 = w2;
			BuildMat(mat1,mat1[0],l1,w1);
		}
		else if(l2 == 1 && w2 == 1){
			BuildMat(mat2,mat2[0],l1,w1);
		}
		else{
			printf("matrix dimension must be the same\n");
			while(1);
		}
	}
	MatAdd(mat1,mat2,l1,w1,mat3);
	MatToStr(mat3,l1,w1,a);
	free(mat1);
	free(mat2);
	free(mat3);
	return a;
}

char* Minus(char *str1, char *str2){
	char *a = (char*)malloc(sizeof(char)*MAXL);
	int *mat1 = (int*)malloc(sizeof(int)*MAXL);
	int *mat2 = (int*)malloc(sizeof(int)*MAXL);
	int *mat3 = (int*)malloc(sizeof(int)*MAXL);
	int l1 = 0, w1 = 0, l2 = 0, w2 = 0;
	StrToMat(str1,mat1,&l1,&w1);
	StrToMat(str2,mat2,&l2,&w2);
	if(l1!=l2 || w1 != w2){
		if(l1 == 1 && w1 == 1){
			l1 = l2;
			w1 = w2;
			BuildMat(mat1,mat1[0],l1,w1);
		}
		else if(l2 == 1 && w2 == 1){
			BuildMat(mat2,mat2[0],l1,w1);
		}
		else{
			printf("matrix dimension must be the same\n");
			while(1);
		}
	}
	MatMinus(mat1,mat2,l1,w1,mat3);
	MatToStr(mat3,l1,w1,a);
	free(mat1);
	free(mat2);
	free(mat3);
	return a;
}

char* Dot(char *str1, char *str2){
	char *a = (char*)malloc(sizeof(char)*MAXL);
	int *mat1 = (int*)malloc(sizeof(int)*MAXL);
	int *mat2 = (int*)malloc(sizeof(int)*MAXL);
	int *mat3 = (int*)malloc(sizeof(int)*MAXL);
	int l1 = 0, w1 = 0, l2 = 0, w2 = 0;
	StrToMat(str1,mat1,&l1,&w1);
	StrToMat(str2,mat2,&l2,&w2);
	if(l1!=l2 || w1 != w2){
		if(l1 == 1 && w1 == 1){
			l1 = l2;
			w1 = w2;
			BuildMat(mat1,mat1[0],l1,w1);
		}
		else if(l2 == 1 && w2 == 1){
			BuildMat(mat2,mat2[0],l1,w1);
		}
		else{
			printf("matrix dimension must be the same\n");
			while(1);
		}
	}
	MatMul(mat1,mat2,l1,w1,mat3);
	MatToStr(mat3,l1,w1,a);
	free(mat1);
	free(mat2);
	free(mat3);
	return a;
}

char* Div(char *str1, char *str2){
	char *a = (char*)malloc(sizeof(char)*MAXL);
	int *mat1 = (int*)malloc(sizeof(int)*MAXL);
	int *mat2 = (int*)malloc(sizeof(int)*MAXL);
	int *mat3 = (int*)malloc(sizeof(int)*MAXL);
	int l1 = 0, w1 = 0, l2 = 0, w2 = 0;
	StrToMat(str1,mat1,&l1,&w1);
	StrToMat(str2,mat2,&l2,&w2);
	if(l1!=l2 || w1 != w2){
		if(l1 == 1 && w1 == 1){
			l1 = l2;
			w1 = w2;
			BuildMat(mat1,mat1[0],l1,w1);
		}
		else if(l2 == 1 && w2 == 1){
			BuildMat(mat2,mat2[0],l1,w1);
		}
		else{
			printf("matrix dimension must be the same\n");
			while(1);
		}
	}
	MatDiv(mat1,mat2,l1,w1,mat3);
	MatToStr(mat3,l1,w1,a);
	free(mat1);
	free(mat2);
	free(mat3);
	return a;
}

char* Mean(char *str){
	char *a = (char*)malloc(sizeof(char)*MAXL);
	int *mat = (int*)malloc(sizeof(int)*MAXL);
	int val[1] = {0};
	int l = 0, w = 0;
	StrToMat(str,mat,&l,&w);
	val[0] = MatMean(mat,l,w);
	MatToStr(val,1,1,a);
	free(mat);
	return a;
}

char* Neg(char *str){
	char *a = (char*)malloc(sizeof(char)*MAXL);
	int *mat = (int*)malloc(sizeof(int)*MAXL);
	int *mat2 = (int*)malloc(sizeof(int)*MAXL);
	int val[1] = {0};
	int l = 0, w = 0;
	StrToMat(str,mat,&l,&w);
	MatNeg(mat,l,w,mat2);
	MatToStr(mat2,l,w,a);
	free(mat);
	free(mat2);
	return a;
}

char* Rev(char *str){
	char *a = (char*)malloc(sizeof(char)*MAXL);
	int *mat = (int*)malloc(sizeof(int)*MAXL);
	int *mat2 = (int*)malloc(sizeof(int)*MAXL);
	int val[1] = {0};
	int l = 0, w = 0;
	StrToMat(str,mat,&l,&w);
	MatRev(mat,l,w,mat2);
	MatToStr(mat2,l,w,a);
	free(mat);
	free(mat2);
	return a;
}

char* Sum(char *str){
	char *a = (char*)malloc(sizeof(char)*MAXL);
	int *mat = (int*)malloc(sizeof(int)*MAXL);
	int val[1] = {0};
	int l = 0, w = 0;
	StrToMat(str,mat,&l,&w);
	val[0] = MatSum(mat,l,w);
	MatToStr(val,1,1,a);
	free(mat);
	return a;
}

void MatToStr(int mat[], int l, int w, char* str){
	int i,j, len = 0;
	char str_num[50];
	str[0] = '[';
	len = 1;
	str[len] = '\0';
	for(i = 0 ; i < l; i ++){
		len = strlen(str);
		if(i>0){
			str[len] = ',';
			len++;
		}
		str[len] = '[';
		len++;
		str[len] = '\0';
		for(j=0;j<w;j++){
			memset(str_num,0,sizeof(str_num));
			sprintf(str_num,"%d",mat[i*w+j]);
			strcat(str,str_num);
			len = strlen(str);
			if(j < w - 1)
				str[len] = ',';
			else
				str[len] = ']';
			len++;
			str[len] = '\0';
		}
	}
	str[len] = ']';
	len++;
	str[len] = '\0';
	memset(str_num,0,sizeof(str_num));
	return;
}

void StrToMat(char *str, int mat[], int *l, int *w){
	int i, j , tempcount = 0, temp_ls[1000], len = strlen(str);
	int curr_num = 0;
	int templ = 0;
	int count = 0, prev_count = 0;
	int isneg = 0;
	for(i = 0 ; i < len - 1 ; i ++){
		if(str[i] == '['){
			if(str[i+1] != '['){
				templ++;
				prev_count = count;
				count = 0;
			}
			continue;
		}
		if(str[i] == '-'){
			isneg = 1;
			continue;
		}
		if(str[i] == ',' || str[i] == ']'){
			if(str[i] == ',' && str[i-1] == ']')
				continue;
			if(isneg){
				curr_num = -curr_num;
				isneg = 0;
			}
			mat[tempcount] = curr_num;
			tempcount++;
			count++;
			if(str[i] == ']'){
				if(prev_count != 0 && count != prev_count){
					printf("Input string must be a matrix, with fixed length and width\n");
					while(1);
				}
			}
			curr_num = 0;
			continue;
		}
		curr_num = curr_num * 10 + str[i] - '0';
	}
	*l = templ;
	*w = count;
	return;
}

void MatAdd(int mat1[], int mat2[], int l, int w, int mat_res[]){
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			mat_res[i*w+j] = mat1[i*w+j] + mat2[i*w+j];
		}
	}
	return;
}

void MatMinus(int mat1[], int mat2[], int l, int w, int mat_res[]){
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			mat_res[i*w+j] = mat1[i*w+j] - mat2[i*w+j];
		}
	}
	return;
}

void MatMul(int mat1[], int mat2[], int l, int w, int mat_res[]){
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			mat_res[i*w+j] = mat1[i*w+j] * mat2[i*w+j];
		}
	}
	return;
}

void MatDiv(int mat1[], int mat2[], int l, int w, int mat_res[]){
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			if(mat2[i*w+j] == 0){
				printf("cannot be divided by 0\n");
				while(1);
			}
			mat_res[i*w+j] = mat1[i*w+j] / mat2[i*w+j];
		}
	}
	return;
}

void MatNeg(int mat[], int l, int w, int mat2[]){
	int sum = 0,i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			mat2[i*w+j] = -mat[i*w+j];
		}
	}
	return;
}

void MatRev(int mat[], int l, int w, int mat2[]){
	int sum = 0,i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			mat2[i*w+j] = mat[(l-i-1)*w+(w-j-1)];
		}
	}
	return;
}

int MatMean(int mat[], int l, int w){
	int sum = 0,i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			sum += mat[i*w+j];
		}
	}
	sum /= (l*w);
	return sum;
}

int MatSum(int mat[], int l, int w){
	int sum = 0,i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			sum += mat[i*w+j];
		}
	}
	return sum;
}

void BuildMat(int mat1[], int val, int l, int w){
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<w;j++){
			mat1[i*w+j] = val;
		}
	}
	return;
}
