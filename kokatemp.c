/*-------------------------------------------------------------------------
kokaTemplate_C v3.0.0
いろいろな関数を用意しています。sugoi

作成者:kokastar(GitHub:starkoka)
最終更新:2023/11/17
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int randNum(int min,int max);
int putInt(char txt[]);
void stop(int sec,int nSec);
bool equalStr(char a[],char b[],bool perfect,int point);
int countWord(char string[],char word[]);
char* replaceStr(char string[],char before[],char after[]);
char* joinStr(char strA[],char strB[]);

/***
 * 2つの変数を入れ替える
 * @param type 交換したい変数の型
 * @param a 交換したい変数
 * @param b 交換したい変数
 */
#define swap(type,a,b) {type temp=a;a=b;b=temp;}

int main(){
	
}
//replaceStr,joinStr関数使用時は、free関数で開放するのを忘れないように

/***
 * min~maxまでの乱数を返す
 * @param min 最小値。正の整数のみを受け付ける
 * @param max 最大値。正の整数のみを受け付ける
 * @returns int
 */
int randNum(int min,int max){
    static int flag = 0;
    if(flag == 0){
        flag = 1;
        srand((unsigned)time(NULL));
    }

    if(min >= 0 && max >= 0 && min<max){
        return rand()%(max-min+1)+min ;
        flag = 1;
    }
    else{
        return -1;
    }
}

/***
 * intの入力を受け取る
 * @param txt[] 入力時に表示する文字列
 * @returns int
 */
int putInt(char txt[]){
    int num;
    printf("%s",txt);
    scanf("%d",&num);
    return num;
}

/***
 * 指定した時間プログラムを待機させる
 * @param sec 停止時間[s]
 * @param nSec 停止時間[ns]
 * @returns void
 */
void stop(int sec,int nSec){
    struct timespec ts,rem;
    ts.tv_sec = sec;
    ts.tv_nsec = nSec;

    nanosleep(&ts,&rem);
}

/***
 * 文字列を比較し、等しいかどうか判定する
 * @param a[] 文字列a
 * @param b[] 文字列b
 * @param perfect aがbを含む場合の文字列の処理。truの場合point引数は無視される
 * @param point aのなん文字目から確認したいかを指定(0オリジン)
 * @returns bool
 */
bool equalStr(char a[],char b[],bool perfect,int point){
    if(perfect){
        if(strlen(a) != strlen(b))return false;
        for(int i=0;i<strlen(a);i++){
            if(a[i]!=b[i]){
                return false;
            }
        }
        return true;
    }
    else{
        if(strlen(a)-point<strlen(b))return false;
        for(int i=0;i<strlen(b);i++){
            if(a[i+point]!=b[i]){
                return false;
            }
        }
        return true;
    }
}

/***
 * 文字列の中に特定のワードが何回出てくるかカウントする
 * @param string[] 文字列
 * @param word[] カウントする単語
 * @returns int*
 */
int countWord(char string[],char word[]){
    /*出てくる回数をカウントして、確保すべきメモリを計算*/
    int num = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (equalStr(string, word, false, i)) {
            num++;
        }
    }

    return num;
}

/***
 * 文字列の特定のワードを、別のワードで置き換える
 * @param string[] 文字列
 * @param before[] 置き換え前の文字列
 * @param after[] 置き換え後の文字列
 * @returns char*
 */
char* replaceStr(char string[],char before[],char after[]){

    /*出てくる回数をカウントして、確保すべきメモリを計算*/
    countWord(string,before);
    int siz = strlen(string) - (strlen(before)-strlen(after)) * sizeof(char)+1;

    /*メモリ領域を確保し、ポインタ変数に格納*/
    char *new = (char*)malloc(siz);
    if(new == NULL){
        printf("メモリ確保失敗：replaceStr\n");
        exit(2);
    }

    int i=0;//stringの参照位置
    int j=0;//newへの書き込み位置
    for(;i<strlen(string);j++){
        if(equalStr(string,before,false,i)){
            i += strlen(before);
            for(int k=0;k<strlen(after);k++){
                new[j] = after[k];
                j++;
            }
            j--; //forでjの更新処理が入るので、それを打ち消す
        }
        else{
            new[j] = string[i];
            i++;
        }

    }
    new[j]='\0';

    return new;
}

/***
 * 2つの文字列を結合する
 * @param strA[] 結合する前側の文字列
 * @param strB[] 結合する後側の文字列
 * @returns char*
 */
char* joinStr(char strA[],char strB[]){
	int siz = strlen(strA) + strlen(strB) + 1;
	char *str = (char *)malloc(sizeof(char)*siz);
	for(int i=0;i<strlen(strA);i++){
		str[i] = strA[i];
	}
	for(int i=strlen(strA);i<siz-1;i++){
		str[i] = strB[i-strlen(strA)];
	}
	str[siz-1] = '\0';
	return str;
}
