#ifndef _DATA_IN_
#define _DATA_IN_

namespace din{

const double MAXSLEEP=8.0;
const double MAXSTUDY=8.0;
static const int SLEEP=0;
static const int STUDY=1;
static constexpr double NOVALUE=-1.0;

class norm{
public:
   norm();
   virtual ~norm();
   double sleep(double s=NOVALUE);
   double study(double s=NOVALUE);
   void normalize(double sleep=MAXSLEEP, double study=MAXSTUDY);
   double operator()(int index,double val);
   double operator[](int index);
private:
   double _sleep;
   double _study;
};

class data_in{
public:
   data_in();
   data_in(double sleep, double study);
   virtual ~data_in();
   double sleep(double s=NOVALUE);
   double study(double s=NOVALUE);
   double operator[](int index);
   double operator()(int index,double s=NOVALUE);
   void load(double sleep,double study);

   norm n;

private:
   double _sleep;
   double _study;
};

} // end of namespace din

#endif // _DATA_IN_
