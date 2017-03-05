#include <stdio.h>
#include "func.h"
#include "debug.h"
#define TRCLOG if(dbgLevel==DBG_LEVEL_1){printf("DbgLOG: >>enter %s [%d, %s]\n",__func__,__LINE__,__FILE__);}

/*  
#define DbgLOG(A,B)  \
if(dbgLevel == DBG_LEVEL_1) {						  \
    printf("DbgLOG: >> " A "[%d, %s]\n",B,__func__,__LINE__,__FILE__);	  \
}                                                                         \
*/

int test1(unsigned char *buff)
{
    printf("%x",buff);
    return 1;
}


int test2(unsigned char *buff)
{

  unsigned int recSignal = 0;
  int ret = 0;

  TRCLOG

  printf("%x",buff[0]);
  switch(buff[0]) {
      case '0':
	ret = test1(buff);
        break;
      case 1:
	ret = test1(buff);
        break;
      case 2:
	ret = test1(buff);
        break;
      default:
        break;
  }

  return ret;
}
