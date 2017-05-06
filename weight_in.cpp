#include "weight_in.h"

using namespace din;

weight_in::weight_in(){
   load(0,0,0);
}

weight_in::weight_in(double w0,double w1,double w2){
   load(w0,w1,w2);
}

weight_in::~weight_in(){
}

weight_in& weight_in::load(double w0,double w1,double w2){
   _weight[0]=w0;
   _weight[1]=w1;
   _weight[2]=w2;

   return *this;
}

double weight_in::operator[](int index){
   double result=-1.0;

   if((index>=0) && (index<=3)){
      result=_weight[index];
   }

   return result;
}

