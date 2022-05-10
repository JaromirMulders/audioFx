/**********************************************************************
*          Copyright (c) 2013, Hogeschool voor de Kunsten Utrecht
*                      Hilversum, the Netherlands
*                          All rights reserved
***********************************************************************
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.
*  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************
*
*  File name     : osc_server.cpp
*  System name   : osc++ : Open Sound Control
*
*  Description   : Demo program using C++ wrapper for liblo
*
*
*  Author        : Marc_G
*  E-mail        : marcg@dinkum.nl
*
**********************************************************************/

#include "osc_server.h"

//parameters by refrence so they can be used in main
void localOSC::getParams(int &param1, int &param2, int &param3, int &param4, int &param5)
{
  if(int1 != 0){
    param1 = int1;
    param2 = int2;
    param3 = int3;
    param4 = int4;
    param5 = int5;
  }

}

void localOSC::getTypes(int &type1, int &type2, int &type3, int &type4)
{
  if(int6 != 0){
    type1 = int6 - 1;
    type2 = int7 - 1;
    type3 = int8 - 1;
    type4 = int9 - 1;
  }

}

void localOSC::getSelect(int &fxSel)
{
  if(int10 != 0){
    fxSel = int10 - 1;
  }
}

int localOSC::realcallback(const char *path,const char *types,lo_arg **argv,int argc)
{
string msgpath=path;

  if(!msgpath.compare("/params")){ //getting parameters from osc
    int1 = argv[0]->i;
    int2 = argv[1]->i;
    int3 = argv[2]->i;
    int4 = argv[3]->i;
    int5 = argv[4]->i;

  }//if
  if(!msgpath.compare("/effectType")){ //getting parameters from osc
    int6 = argv[0]->i;
    int7 = argv[1]->i;
    int8 = argv[2]->i;
    int9 = argv[3]->i;

  }//if
  if(!msgpath.compare("/effectSelect")){ //getting parameters from osc
    int10 = argv[0]->i;
  }//if


  return 0;
}; // realcallback()
