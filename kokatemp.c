/*-------------------------------------------------------------------------
kokalib v1.2.0
いろいろな関数を用意しています。sugoi

作成者:kokastar(GitHub:starkoka)
最終更新:2023/7/19
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int randNum(int min,int max);
int putint(char txt[]);
int stop(int sec,int nsec);

int main(){
	
	return 0;
}


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
name : putint
explanation : intの入力を受け取る。
return : int

char txt[] : 入力時に表示する文字列
-------------------------------------------------------------------------*/

int putint(char txt[]){
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
int nsec : 停止時間[ns]
-------------------------------------------------------------------------*/

int stop(int sec,int nsec){
	struct timespec ts,rem;
	ts.tv_sec = sec;
	ts.tv_nsec = nsec;

	nanosleep(&ts,&rem);
}
