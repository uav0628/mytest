#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// キューの定義
typedef struct {
  int front;
  int rear;
  int count;
  int size;
  unsigned int *buff;
} QueueTable;

// キューの生成
QueueTable *createQueue(int n)
{
  QueueTable *que = (QueueTable *)malloc(sizeof(QueueTable));

  if (que != NULL) {
    que->front = 0;
    que->rear = 0;
    que->count = 0;
    que->size = n;
    que->buff = (unsigned int*)malloc(sizeof(unsigned int) * n);
    if (que->buff == NULL) {
      free(que);
      return NULL;
    }
  }
  return que;
}

void ShowQueueTable(QueueTable *que)
{
  printf("*--------------------------------*\n");
  printf("que->front       %d\n",que->front);
  printf("que->rear        %d\n",que->rear);
  printf("que->count       %d\n",que->count);
  printf("que->size        %d\n",que->size);
  printf("que->buff          \n");
  for(int i=0;i<que->size;i++){
    printf("%x ",que->buff[i]);
  }
  printf("\n");
  printf("*--------------------------------*\n");
  return;
}
// キューは満杯か
bool is_full(QueueTable *que)
{
  return que->count == que->size;
}

// キューは空か
bool is_empty(QueueTable *que)
{
  return que->count == 0;
}

// データの挿入
bool enQueue(QueueTable *que, unsigned int x)
{
  if (is_full(que)) {
    return false;
  }

  que->buff[que->rear++] = x;
  que->count++;

  if (que->rear == que->size) {
    que->rear = 0;
  }
  return true;
}

// データを取り出す
unsigned int deQueue(QueueTable *que, bool *err)
{
  if(!que) {
    *err = false;
    return 0;
  }

  if (is_empty(que)) {
    *err = false;
    return 0;
  }

  unsigned int x = que->buff[que->front++];
  que->count--;
  *err = true;

  if (que->front == que->size) {
    que->front = 0;
  }

  return x;
}

// 先頭データを参照する
unsigned char top(QueueTable *que, bool *err)
{
  if (is_empty(que)) {
    *err = false;
    return 0;
  }
  return que->buff[que->front];
}

// キューをクリアする
void clear(QueueTable *que)
{
  que->front = que->rear = que->count = 0;
}

// キューの個数を求める
int queue_length(QueueTable *que)
{
  return que->count;
}

// キューの削除
void queue_delete(QueueTable *que)
{
  free(que->buff);
  free(que);
  return;
}

// 簡単なテスト
int queue_main(void)
{
  QueueTable *que = createQueue(8);
  bool err;
  for (int i = 0; i < 4; i++)
    enQueue(que, i);

  printf("%x\n", queue_length(que));
  printf("%x\n", is_empty(que));
  printf("%x\n", is_full(que));

  while (!is_empty(que))
    printf("%.x\n", deQueue(que, &err));

  printf("%x\n", queue_length(que));
  printf("%x\n", is_empty(que));
  printf("%x\n", is_full(que));

  for (int i = 0; i < 8; i++)
    enQueue(que, i);

  printf("%x\n", queue_length(que));
  printf("%x\n", is_empty(que));
  printf("%x\n", is_full(que));

  while (!is_empty(que))
    printf("%x\n", deQueue(que, &err));

  queue_delete(que);

  return 1;
}
