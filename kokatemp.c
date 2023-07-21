/*-------------------------------------------------------------------------
kokaTemplate_C v1.2.0
いろいろな関数を用意しています。sugoi

作成者:kokastar(GitHub:starkoka)
最終更新:2023/7/19
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
char* replaceStr(char string[],char before[],char after[]);

int main(){

    return 0;
}
//replaceStr関数使用時は、free関数で開放するのを忘れないように

/*-------------------------------------------------------------------------
name : randNum
explanation : min~maxまでの乱数を返す。
return : int(エラー時-1)

min : 最小値。正の整数のみを受け付ける
max : 最大値。正の整数のみを受け付ける
-------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------
name : putInt
explanation : intの入力を受け取る。
return : int

char txt[] : 入力時に表示する文字列
-------------------------------------------------------------------------*/

int putInt(char txt[]){
    int num;
    printf("%s",txt);
    scanf("%d",&num);
    return num;
}

/*------------------------------------------------------------------------
name : stop
explanation : 指定した時間プログラムを待機させる
return : なし

int sec  : 停止時間[s]
int nSec : 停止時間[ns]
-------------------------------------------------------------------------*/

void stop(int sec,int nSec){
    struct timespec ts,rem;
    ts.tv_sec = sec;
    ts.tv_nsec = nSec;

    nanosleep(&ts,&rem);
}

/*------------------------------------------------------------------------
name : equalStr
explanation : 文字列を比較し、等しいかどうか判定する
return : bool

char a[]  　　　: 文字列a
char b[]       : 文字列b
bool perfect   : aがbを含む場合の文字列の処理。trueの場合point引数は無視される
int point      : aの何文字目から確認したいかを指定(0オリジン)
-------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------
name : replaceStr
explanation : 文字列の特定のワードを、別のワードで置き換える
return : char*

char string[]  : 文字列
char before[] : 置き換え前文字列
char after[]   : 置き換え後の文字列
-------------------------------------------------------------------------*/
char* replaceStr(char string[],char before[],char after[]){

    /*出てくる回数をカウントして、確保すべきメモリを計算*/
    int num = 0;
    for(int i=0;i<strlen(string);i++){
        if(equalStr(string,before,false,i)){
            num++;
        }
    }
    int siz = strlen(string) - (strlen(before)-strlen(after)) * sizeof(char);

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

    return new;
}
