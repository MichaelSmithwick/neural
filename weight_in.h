#ifndef _WEIGHT_IN_
#define _WEIGHT_IN_

namespace din{

class weight_in{
public:
   weight_in();
   weight_in(double w0,double w1,double w2);
   virtual ~weight_in();
   weight_in& load(double w0,double w1,double w2);
   double operator[](int);
private:
   double _weight[3];
};

}

#endif // _WEIGHT_IN_
