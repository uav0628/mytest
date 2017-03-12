#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "func.h"
#include "debug.h"
#include "pipe.h"

void* thread1(void* pParam); //thread 1
void* thread2(void* pParam); //thread 2
void* thread3(void* pParam); //thread 3
void* thread4(void* pParam); //thread 4
void* thread5(void* pParam); //thread 5
void* thread6(void* pParam); //thread 6

int count1=0;
int count2=0;
pthread_mutex_t mutex; //2つのスレッド間で変数の保護を行う


int main(int argc, char *argv[])
{
  dbgLevel = DBG_LEVEL_1;

  //pthread_t tid1;
  //pthread_t tid2;
  //pthread_t tid3;
  //pthread_t tid4;
  pthread_t tid5;
  pthread_t tid6; // スレッド識別変数

  pthread_mutex_init(&mutex, NULL);

  // スレッドの作成
  //hread_create(&tid1, NULL, thread1, NULL);
  //hread_create(&tid2, NULL, thread2, NULL);
  //hread_create(&tid3, NULL, thread3, NULL);
  //hread_create(&tid4, NULL, thread4, NULL);
  pthread_create(&tid5, NULL, thread5, NULL);
  pthread_create(&tid6, NULL, thread6, NULL);

  // スレッド終了待ち
  //hread_join(tid1,NULL);
  //hread_join(tid2,NULL);
  //hread_join(tid3,NULL);
  //hread_join(tid4,NULL);
  pthread_join(tid5,NULL);
  pthread_join(tid6,NULL);

  pthread_mutex_destroy(&mutex);
  return 0;
}


// thread 1
void* thread1(void* pParam)
{
  //int i;
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
  return NULL;
}

// thread 2
extern int tcp_client(void);
void* thread2(void* pParam)
{
  tcp_client();
  return NULL;
}

// thread 3
extern int tcp_server(void);
void* thread3(void* pParam)
{
  tcp_server() ;
  return NULL;
}

// thread 4
extern int queue_main(void);
void* thread4(void* pParam)
{
  queue_main();
  return NULL;
}

// thread 5
QueueTable *queue_1;
void* thread5(void* pParam)
{
  const int BUFF_LEN = 255;
  unsigned int buff[BUFF_LEN];
  queue_1 = createQueue(8);
  while(1) {
    int rc;
    memset(buff,0,sizeof(buff));
    rc = read(STDIN_FILENO, buff, BUFF_LEN);
    if (rc == -1) {
    } else {
      printf("echo: [%c] [%d, %s]\n",buff[0],__LINE__,__FILE__);
      fwrite(buff, 1, rc, stdout);
      enQueue(queue_1, buff[0]);
      printf("[%d, %s]\n",__LINE__,__FILE__);
      ShowQueueTable(queue_1);
    }
  }
  return NULL;
}

void* thread6(void* pParam)
{
  while(1) {
    unsigned int ret = 0;
    bool err = false;
    ret = deQueue(queue_1, &err);
    if( err == true) {
      ShowQueueTable(queue_1);
      printf("[deQueue]%c[%d, %s]\n",ret,__LINE__,__FILE__);
    }
  }
  return NULL;
}
