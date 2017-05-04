#include "data_in.h"

using namespace din;

data_in::data_in(){
   _sleep=NOVALUE;
   _study=NOVALUE;
}

data_in::data_in(double sleep,double study){
   load(sleep,study);
}

data_in::~data_in(){
}

void data_in::load(double sleep,double study){
   this->sleep(sleep);
   this->study(study);
}

double data_in::sleep(double s){
   if(s>=0.0) (*this)(SLEEP,s);
   return _sleep;
}

double data_in::study(double s){
   if(s>=0.0) (*this)(STUDY,s);
   return _study;
}

double data_in::operator[](int index){
   double s=NOVALUE;

   switch(index){
   case SLEEP:
      s=_sleep;
      break;
   case STUDY:
      s=_study;
      break;
   default:
      break;
   }

   return s;
}

double data_in::operator()(int index,double s){
   double result;

   if((result=s)>=0.0){
      switch(index){
      case SLEEP:
         _sleep=s;
         n.sleep(s);
         break;
      case STUDY:
         _study=s;
         n.study(s);
         break;
      default:
         break;
      }
   }

   return result;
}

/* class norm function definitions */

norm::norm(){
   _sleep=NOVALUE;
   _study=NOVALUE;
}

norm::~norm(){}

double norm::sleep(double s){
   if(s>=0.0) (*this)(SLEEP,s);
   return _sleep;
}

double norm::study(double s){
   if(s>=0.0) (*this)(STUDY,s);
   return _study;
}

void norm::normalize(double sleep, double study){
   _sleep/=sleep;
   _study/=study;
}

/**
 * This function sets the value of the specified parameter
 * The specified index value can be 'SLEEP' or 'STUDY'
 * @param [in] index specifies the item to normalize
 * @param [in] val specifies the value to use for the either _sleep or _study.
 */
double norm::operator()(int index,double val){
   double s=NOVALUE;

   switch(index){
   case SLEEP:
      _sleep=val;
      s=_sleep;
      break;
   case STUDY:
      _study=val;
      s=_study;
   default:
      break;
   }

   return s;
}

double norm::operator[](int index){
   double s=NOVALUE;

   switch(index){
   case SLEEP:
      s=_sleep;
      break;
   case STUDY:
      s=_study;
   default:
      break;
   }

   return s;
}

