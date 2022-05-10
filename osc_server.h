#include "osc.h"

class localOSC  : public OSC
{
  public:
    void getParams(int &param1, int &param2, int &param3, int &param4, int &param5);
    void getTypes(int &type1, int &type2, int &type3, int &type4);
    void getSelect(int &fxSel);

    int realcallback(const char *path,const char *types,lo_arg **argv,int argc);

    int int1;
    int int2;
    int int3;
    int int4;
    int int5;

    int int6;
    int int7;
    int int8;
    int int9;

    int int10;

    int type1;
    int type2;
    int type3;
    int type4;

    int param1;
    int param2;
    int param3;
    int param4;
    int param5;

    int fxSel;

};
