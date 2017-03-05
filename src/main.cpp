#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "func.h"
#include "debug.h"


void* thread1(void* pParam); //スレッド１
void* thread2(void* pParam); //スレッド２
void* thread3(void* pParam); //スレッド３
int count1=0;
int count2=0;
pthread_mutex_t mutex; //2つのスレッド間で変数の保護を行う


int main(int argc, char *argv[]){

  dbgLevel = DBG_LEVEL_1;
  
  pthread_t tid1, tid2, tid3; // スレッド識別変数

  pthread_mutex_init(&mutex, NULL);

  // スレッドの作成
  pthread_create(&tid1, NULL, thread1, NULL);
  pthread_create(&tid2, NULL, thread2, NULL);
  pthread_create(&tid3, NULL, thread3, NULL);

  // スレッド終了待ち
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);

  pthread_mutex_destroy(&mutex); 
  return 0;
}

//スレッド１
void* thread1(void* pParam)
{
  int i;
  while(1){
    //mutex 間は他のスレッドから変数を変更できない
    pthread_mutex_lock(&mutex);
    //printf("count1:");
    //for(i=0;i<10;i++){
    //printf("%d:",count1);
    //  count1++;
    //}
    //printf("\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);
    
    //mutex で変数を保護しないと他のスレッドから変数を変更できる
    //printf("count2:");
    //for(i=0;i<10;i++){
    //  printf("%d:",count2);
    //  count2++;
    //}
    //printf("\n");
    sleep(1);
  }
}

//スレッド２
extern int tcp_client(void);
void* thread2(void* pParam)
{
  tcp_client();
}


// thread 3
extern int tcp_server(void);
void* thread3(void* pParam)
{
  tcp_server() ;
}
