
// キューの定義
struct QueueTable;
// キューの生成
QueueTable *createQueue(int n);
// キューは満杯か
bool is_full(QueueTable *que);
// キューは空か
bool is_empty(QueueTable *que);
// データの挿入
bool enQueue(QueueTable *que, unsigned int x);
// データを取り出す
unsigned int deQueue(QueueTable *que, bool *err);
// 先頭データを参照する
unsigned char top(QueueTable *que, bool *err);
// キューをクリアする
void clear(QueueTable *que);
// キューの個数を求める
int queue_length(QueueTable *que);
// キューの削除
void queue_delete(QueueTable *que);
// キューテーブルのDump
void ShowQueueTable(QueueTable *que);
