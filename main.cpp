/**
 * @title This application explores the working of a simple neural network.
 * This neural network is used to correlate sleep time and study time with test scores
 *
 * @author Michael Smithwick
 */

#include <iomanip>
#include <iostream>
#include <array>
#include <cmath>
#include <random>
#include <functional>
#include <ctime>
#include <fstream>

#include "data_in.h"
#include "weight_in.h"

// Using Artificial Neural Network (ANN) for AI machine learning

const double MAXSCORE=100.0;
const int INLAYERSZ=2;
const int OUTLAYERSZ=1;
const int HIDDENLAYERSZ=3;

//double normalize(double value, const double maxvalue);
double activationfunction(double value);
double forward(std::array<double,3> &hidden, din::data_in d_in, std::array<weight_in,2> w_in);
double second_stage(std::array<double,3> &secondstage_out, std::array<std::array<double,3>,3> hidden_result, std::array<double,3> weight_out);

int main()
{
   std::array<din::data_in,3> d_in; // input data - object contains sleep & study hours
   std::array<double,3> m_out; // Test score to be correlated with sleep and study hours input
   std::array<weight_in,2> w_in;
   std::array<double,3> hidden; // derived hidden values
   std::array<double,2> norm; // holds normalized values
   std::array<std::array<double,3>,3> hidden_result;
   std::array<double,3> weight_out;
   std::array<double,3> secondstage_out;
   std::default_random_engine generator;
   std::uniform_int_distribution<int> distribution(0,100000);
   auto wfactor=std::bind(distribution,generator);
   int i;
   double _zz=100000.0;

   // 1rst parameter = sleep hours
   // 2nd parameter = study hours
   d_in[0].load(3.0,5.0);
   d_in[1].load(5.0,1.0);
   d_in[2].load(10.0,2.0);

   m_out[0]=75.0;
   m_out[1]=82.0;
   m_out[2]=93.0;

   generator.seed((long)time(NULL));
   std::cout<<distribution(generator)<<"   "<<(double)distribution(generator)<<std::endl;
   w_in[0].load((double)distribution(generator)/_zz,(double)distribution(generator)/_zz,(double)distribution(generator)/_zz);
   w_in[1].load((double)distribution(generator)/_zz,(double)distribution(generator)/_zz,(double)distribution(generator)/_zz);

   for(i=0;i<2;i++){
      std::cout<<w_in[i][0]<<"  "<<w_in[i][1]<<"  "<<w_in[i][2]<<std::endl;
   }

   weight_out[0]=((double)wfactor())/100000.0;
   weight_out[1]=((double)wfactor())/100000.0;
   weight_out[2]=((double)wfactor())/100000.0;

   i=0;
   //std::cout<<std::setfill(' ');
   //std::cout<<std::setiosflags(std::ios::right);
   std::cout<<std::fixed;
   std::cout<<std::setprecision(5);
   for(auto a:d_in){
      a.n.normalize();

      std::cout<<"-----------------"<<std::endl;
      std::cout<<"Sleep : "<<std::setw(8)<<a[din::SLEEP]<<" hours : "<<a.n.sleep()<<" normalized : "<<activationfunction(a.n.sleep())<<" activated"<<std::endl;
      std::cout<<"Study : "<<std::setw(8)<<a[din::STUDY]<<" hours : "<<a.n.study()<<" normalized : "<<activationfunction(a.n.study())<<" activated"<<std::endl;
      std::cout<<std::endl;

      norm[0]=a.n.sleep();
      norm[1]=a.n.study();

      forward(hidden,a,w_in);
      std::cout<<"hidden 0 "<<hidden[0]<<" activated : "<<activationfunction(hidden[0])<<std::endl;
      std::cout<<"hidden 1 "<<hidden[1]<<" activated : "<<activationfunction(hidden[1])<<std::endl;
      std::cout<<"hidden 2 "<<hidden[2]<<" activated : "<<activationfunction(hidden[2])<<std::endl<<std::endl;
      hidden_result[i][0]=hidden[0];
      hidden_result[i][1]=hidden[1];
      hidden_result[i][2]=hidden[2];
      i++;
   }

   std::cout<<"-----------------"<<std::endl;
   for(auto a:hidden_result){
      std::cout<<"hidden result: 0: "<<a[0]<<" 1: "<<a[1]<<" 2: "<<a[2]<<std::endl;
      a[0]=activationfunction(a[0]);
      a[1]=activationfunction(a[1]);
      a[2]=activationfunction(a[2]);
      std::cout<<"activated result: 0: "<<a[0]<<" 1: "<<a[1]<<" 2: "<<a[2]<<std::endl;
   }

   std::cout<<std::endl;

   second_stage(secondstage_out,hidden_result,weight_out);
   std::cout<<"-----------------"<<std::endl;
   for(i=0;i<HIDDENLAYERSZ;i++){
      std::cout<<"second_stage["<<i<<"]: "<<secondstage_out[i]<<" activated: "<<activationfunction(secondstage_out[i])<<std::endl;
      secondstage_out[i]=activationfunction(secondstage_out[i]);
   }

   /*
   std::fstream f("C:\\Users\\Mike\\Desktop\\tdata.txt",std::ios_base::out);
   for(double i=0.0;i<1.0;i+=0.01){
      f<<i<<","<<activationfunction(i)<<std::endl;
      if(i>1.0) break;
   }
   f.close();
   */

   return 0;
}
/*
double normalize(double value, const double maxvalue){
   return value/maxvalue;
}
*/
double activationfunction(double value){
   return 1.0/(1.0+exp(-((value*20.0)-10.0)));
}

double forward(std::array<double,3> &hidden, din::data_in d_in, std::array<weight_in,2> w_in){
   for(int i=0;i<HIDDENLAYERSZ;i++){
      hidden[i]=(d_in.n.sleep()*w_in[0][i])+(d_in.n.study()*w_in[1][i]);
   }
   return 0.0;
}

double second_stage(std::array<double,3> &secondstage_out, std::array<std::array<double,3>,3> hidden_result, std::array<double,3> weight_out){
   for(int i=0;i<HIDDENLAYERSZ;i++)
      secondstage_out[i]=(hidden_result[i][0]*weight_out[0])+(hidden_result[i][1]*weight_out[1])+(hidden_result[i][2]*weight_out[2]);
   return 0.0;
}

