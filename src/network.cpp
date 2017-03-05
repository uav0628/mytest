#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#define PORT 9876 //クライアントプログラムとポート番号を合わせてください

int tcp_server(void){

  int srcSocket; //自分
  int dstSocket; //相手
  // sockaddr_in 構造体

  struct sockaddr_in srcAddr;
  struct sockaddr_in dstAddr;
  int dstAddrSize = sizeof(dstAddr);
  // 各種パラメータ
  int numrcv;
  unsigned char buf[1024];

  while(1){//ループで回すことによって何度でもクライアントからつなぐことができる
    // sockaddr_in 構造体のセット
    bzero((char *)&srcAddr, sizeof(srcAddr));
    srcAddr.sin_port = htons(PORT);
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_addr.s_addr = INADDR_ANY;
    
    // ソケットの生成（ストリーム型）
    srcSocket = socket(AF_INET, SOCK_STREAM, 0);
    // ソケットのバインド
    bind(srcSocket, (struct sockaddr *)&srcAddr, sizeof(srcAddr));
    // 接続の許可
    listen(srcSocket, 1);
    
    // 接続の受付け
    printf("[SER]接続を待っています\nクライアントプログラムを動かして下さい\n");
    dstSocket = accept(srcSocket, (struct sockaddr *)&dstAddr, (socklen_t *)&dstAddrSize);
    printf("[SER]%s から接続を受けました\n",inet_ntoa(dstAddr.sin_addr));
    close(srcSocket);
        
    while(1){
      //パケットの受信
      numrcv = read(dstSocket, buf, 1024);
      if(numrcv ==0 || numrcv ==-1 ){
	close(dstSocket); break;
      }
      // fprintf(stdout,">>",buf);
      extern int test2(unsigned char *buff);
      test2(buf);
      // パケットの送信
      // write(dstSocket, buf, 1024);
    }
  }
  return(0);
}


int tcp_client(void){
  // IP アドレス，ソケット，sockaddr_in 構造体
  int dstSocket;
  struct sockaddr_in dstAddr;

  //struct sockaddr_in addr;
  struct hostent *hp;
  char   buf[1024];
  int    numrcv;

  // 相手先アドレスの入力と送る文字の入力
  char destination[] = "192.168.1.24";

  //sockaddr_in 構造体のセット
  bzero((char *)&dstAddr, sizeof(dstAddr));
  dstAddr.sin_family = AF_INET;
  dstAddr.sin_port = htons(PORT);
  
  hp = gethostbyname(destination);
  bcopy(hp->h_addr, &dstAddr.sin_addr, hp->h_length);

  //ソケットの生成
  dstSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  //接続
  if (connect(dstSocket, (struct sockaddr *)&dstAddr, sizeof(dstAddr)) < 0){
    printf("[CLI]%s に接続できませんでした\n",destination);
    return(-1);
  }
  printf("[CLI]%s に接続しました\n",destination);
  printf("[CLI]適当なアルファベットを入力してください\n");
  
  while (1){
    scanf("%s",buf);
    //パケットの送信
    write(dstSocket, buf, 1024);
    //パケットの受信
    //numrcv = read(dstSocket, buf, 1024);
  }
  close(dstSocket);
  return(0);
}
