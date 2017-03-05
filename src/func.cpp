#include <stdio.h>
#include "func.h"
#include "debug.h"


//#define DbgLOG							\
#define DBGLOG if(dbgLevel == DBG_LEVEL_1) {			          \
    printf("DbgLOG: >>enter %s [%d, %s]\n",__func__,__LINE__,__FILE__);   \
}                                                                         \

/*  
#define DbgLOG(A,B)  \
if(dbgLevel == DBG_LEVEL_1) {						  \
    printf("DbgLOG: >> " A "[%d, %s]\n",B,__func__,__LINE__,__FILE__);	  \
}                                                                         \
*/

int test1(void)
{
  return 1;
}


int test2(void)
{

  unsigned int recSignal = 0;
  int ret = 0;

  DBGLOG

  switch(recSignal) {
      case 0:
	ret = test1();
        break;
      case 1:
	ret = test1();
        break;
      case 2:
	ret = test1();
        break;
      default:
        break;
  }

  return ret;
}
