#include <stdio.h>
#include "func.h"
#include "debug.h"

#define TRCLOG if(dbgLevel==DBG_LEVEL_1){printf("DbgLOG: >>enter %s [%d, %s]\n",__func__,__LINE__,__FILE__);}
#define DBGLOG if(dbgLevel==DBG_LEVEL_1)

enum {
  STATE_FIRST,
  STATE_A,
  STATE_B,
  STATE_C,
  STATE_END,
};

unsigned char state = STATE_A;
unsigned char isState[STATE_END];

int test1(unsigned char *buff)
{
    TRCLOG
    DBGLOG printf("DbgLOG: >>buff[0] %x [%d, %s]\n",buff[0],__LINE__,__FILE__);
    return 1;
}

int set_isState(void){
  isState[STATE_A] = 1;
  isState[STATE_B] = 1;
  isState[STATE_C] = 1;
  return 1;
}

int show_state(unsigned char isSomething,unsigned char state){
{
  if(!isSomething) {
    printf("No Message\n");
    return 1;
  }

  DBGLOG printf("DbgLOG: >>state %x [%d, %s]\n",state,__LINE__,__FILE__);
  switch(state){
  case STATE_A:
    printf("State A   Message\n");
    break;
  case STATE_B:
    printf("State B   Message\n");
    break;
  case STATE_C:
    printf("State C   Message\n");
    break;
  default:
      break;
    }
 }

 return 1;
}

int stateUP(unsigned char *buff)
{

  unsigned char isSomething = 0;
  unsigned char count = 0;
  int ret = 0;

  while(count < STATE_END) {
    state -= 1;
    if(state == STATE_FIRST) {
      state = STATE_C;
    }

    // 表示物があれば抜ける
    if(isState[state]){
      isSomething = 1;
      break;
    }
    count += 1;
  }

  ret = show_state(isSomething,state);
  return ret;
}

int stateDOWN(unsigned char *buff)
{

  unsigned char isSomething = 0;
  unsigned char count = 0;
  int ret = 0;

  while(count < STATE_END) {
    state += 1;
    if(state == STATE_END) {
      state = STATE_A;
    }

    // 表示物があれば抜ける
    if(isState[state]){
      isSomething = 1;
      break;
    }
    count += 1;
  }

  ret = show_state(isSomething,state);
  return ret;
}


int test2(unsigned char *buff)
{

  unsigned int recSignal = 0;
  int ret = 0;

  TRCLOG
  DBGLOG printf("mDbgLOG: >>recSignal %x buff[0] %x [%d, %s]\n",recSignal,buff[0],__LINE__,__FILE__);

  set_isState();
  switch(buff[0]) {
      case 'u':  case 'U':
	ret = stateUP(buff);
        break;
      case 'd':  case 'D':
	ret = stateDOWN(buff);
        break;
      case '2':
	ret = test1(buff);
        break;
      default:
        break;
  }

  return ret;
}
