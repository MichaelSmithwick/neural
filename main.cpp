#include <iostream>
#include <array>
#include <cmath>
#include <random>
#include <functional>
#include <ctime>
#include <fstream>

// Using Artificial Neural Network (ANN) for AI machine learning

const double MAXSCORE=100.0;
const double MAXSLEEP=8.0;
const double MAXSTUDY=8.0;
const int INLAYERSZ=2;
const int OUTLAYERSZ=1;
const int HIDDENLAYERSZ=3;

double normalize(double value, const double maxvalue);
double activationfunction(double value);
double forward(std::array<double,3> &hidden, std::array<double,2> m_in, std::array<std::array<double,3>,2> weight_in);
double second_stage(std::array<double,3> &secondstage_out, std::array<std::array<double,3>,3> hidden_result, std::array<double,3> weight_out);

int main()
{
   std::array<std::array<double,2>,3> m_in; // the first column is number of hours of sleep, second column is number of hours of study
   std::array<double,3> m_out; // Test score to be correlated with sleep and study hours input
   std::array<std::array<double,3>,2> weight_in; // the 2x3 array to use to derive the hidden values
   std::array<double,3> hidden; // derived hidden values
   std::array<double,2> norm; // holds normalized values
   std::array<std::array<double,3>,3> hidden_result;
   std::array<double,3> weight_out;
   std::array<double,3> secondstage_out;
   std::default_random_engine generator;
   std::uniform_int_distribution<int> distribution(0,100000);
   auto wfactor=std::bind(distribution,generator);
   int i;

   m_in[0][0]=3.0;
   m_in[0][1]=5.0;
   m_in[1][0]=5.0;
   m_in[1][1]=1.0;
   m_in[2][0]=10.0;
   m_in[2][1]=2.0;

   m_out[0]=75.0;
   m_out[1]=82.0;
   m_out[2]=93.0;

   generator.seed((long)time(NULL));
   std::cout<<wfactor()<<std::endl;
   weight_in[0][0]=((double)wfactor())/100000.0;
   weight_in[0][1]=((double)wfactor())/100000.0;
   weight_in[0][2]=((double)wfactor())/100000.0;
   weight_in[1][0]=((double)wfactor())/100000.0;
   weight_in[1][1]=((double)wfactor())/100000.0;
   weight_in[1][2]=((double)wfactor())/100000.0;

   weight_out[0]=((double)wfactor())/100000.0;
   weight_out[1]=((double)wfactor())/100000.0;
   weight_out[2]=((double)wfactor())/100000.0;

   i=0;
   for(auto a:m_in){
      std::cout<<"Sleep "<<a[0]<<" : "<<normalize(a[0],MAXSLEEP)<<" : "<<activationfunction(normalize(a[0],MAXSLEEP))<<std::endl;
      std::cout<<"Study "<<a[1]<<" : "<<normalize(a[1],MAXSTUDY)<<" : "<<activationfunction(normalize(a[1],MAXSTUDY))<<std::endl;
      norm[0]=normalize(a[0],MAXSLEEP);
      norm[1]=normalize(a[1],MAXSTUDY);
      forward(hidden,norm,weight_in);
      std::cout<<"hidden 0 "<<hidden[0]<<" activated : "<<activationfunction(hidden[0])<<std::endl;
      std::cout<<"hidden 1 "<<hidden[1]<<" activated : "<<activationfunction(hidden[1])<<std::endl;
      std::cout<<"hidden 2 "<<hidden[2]<<" activated : "<<activationfunction(hidden[2])<<std::endl<<std::endl;
      hidden_result[i][0]=hidden[0];
      hidden_result[i][1]=hidden[1];
      hidden_result[i][2]=hidden[2];
      i++;
   }

   for(auto a:hidden_result){
      std::cout<<"hidden result: 0: "<<a[0]<<" 1: "<<a[1]<<" 2: "<<a[2]<<std::endl;
      a[0]=activationfunction(a[0]);
      a[1]=activationfunction(a[1]);
      a[2]=activationfunction(a[2]);
      std::cout<<"activated result: 0: "<<a[0]<<" 1: "<<a[1]<<" 2: "<<a[2]<<std::endl;
   }

   std::cout<<std::endl;

   second_stage(secondstage_out,hidden_result,weight_out);
   for(i=0;i<HIDDENLAYERSZ;i++){
      std::cout<<"second_stage["<<i<<"]: "<<secondstage_out[i]<<" activated: "<<activationfunction(secondstage_out[i])<<std::endl;
      secondstage_out[i]=activationfunction(secondstage_out[i]);
   }

   std::fstream f("C:\\Users\\Mike\\Desktop\\tdata.txt",std::ios_base::out);
   for(double i=0.0;i<1.0;i+=0.01){
      f<<i<<","<<activationfunction(i)<<std::endl;
      if(i>1.0) break;
   }
   f.close();

   return 0;
}

double normalize(double value, const double maxvalue){
   return value/maxvalue;
}

double activationfunction(double value){
   return 1.0/(1.0+exp(-((value*20.0)-10.0)));
}

double forward(std::array<double,3> &hidden, std::array<double,2> m_in, std::array<std::array<double,3>,2> weight_in){
   for(int i=0;i<HIDDENLAYERSZ;i++){
      hidden[i]=(m_in[0]*weight_in[0][i])+(m_in[1]*weight_in[1][i]);
   }
   return 0.0;
}

double second_stage(std::array<double,3> &secondstage_out, std::array<std::array<double,3>,3> hidden_result, std::array<double,3> weight_out){
   for(int i=0;i<HIDDENLAYERSZ;i++)
      secondstage_out[i]=(hidden_result[i][0]*weight_out[0])+(hidden_result[i][1]*weight_out[1])+(hidden_result[i][2]*weight_out[2]);
   return 0.0;
}

