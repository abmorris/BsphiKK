// -*- mode: c++ -*-
// 
// File AutoAngAccMDF.cxx generated by TMultiDimFit::MakeRealCode
// on Tue Dec  8 11:00:19 2015
// ROOT version 6.04/10
//
// This file contains the function 
//
//    double  AutoAngAcc::MDF(double *x); 
//
// For evaluating the parameterization obtained
// from TMultiDimFit and the point x
// 
// See TMultiDimFit class documentation for more information 
// 
#include "AutoAngAcc.h"
//
// Static data variables
//
int    AutoAngAcc::gNVariables    = 3;
int    AutoAngAcc::gNCoefficients = 12;
double AutoAngAcc::gDMean         = 26.4791;
// Assignment to mean vector.
double AutoAngAcc::gXMean[] = {
  -0.00381592, 0.0011792, -0.00116595 };

// Assignment to minimum vector.
double AutoAngAcc::gXMin[] = {
  -3.14154, -0.999375, -0.999834 };

// Assignment to maximum vector.
double AutoAngAcc::gXMax[] = {
  3.14159, 0.999844, 0.999781 };

// Assignment to coefficients vector.
double AutoAngAcc::gCoefficient[] = {
  -3.82763,
  -8.06874,
  -2.68435,
  -0.247886,
  0.249188,
  0.0385431,
  0.218178,
  -0.102213,
  0.420054,
  0.116095,
  -0.0114655,
  -0.320362
 };

// Assignment to error coefficients vector.
double AutoAngAcc::gCoefficientRMS[] = {
  0.0374871,
  0.0834167,
  0.10995,
  0.11353,
  0.111031,
  0.0652996,
  0.0645075,
  0.0638611,
  0.122134,
  0.141684,
  0.0986679,
  0.146559
 };

// Assignment to powers vector.
// The powers are stored row-wise, that is
//  p_ij = AutoAngAcc::gPower[i * NVariables + j];
int    AutoAngAcc::gPower[] = {
  1,  1,  1,
  1,  1,  3,
  1,  1,  5,
  1,  2,  2,
  2,  1,  2,
  1,  1,  2,
  1,  2,  1,
  2,  1,  1,
  1,  1,  6,
  2,  1,  3,
  1,  1,  4,
  1,  2,  3
};

// 
// The method   double AutoAngAcc::MDF(double *x)
// 
double AutoAngAcc::MDF(double *x) {
  double returnValue = AutoAngAcc::gDMean;
  int    i = 0, j = 0, k = 0;
  for (i = 0; i < AutoAngAcc::gNCoefficients ; i++) {
    // Evaluate the ith term in the expansion
    double term = AutoAngAcc::gCoefficient[i];
    for (j = 0; j < AutoAngAcc::gNVariables; j++) {
      // Evaluate the polynomial in the jth variable.
      int power = AutoAngAcc::gPower[AutoAngAcc::gNVariables * i + j]; 
      double p1 = 1, p2 = 0, p3 = 0, r = 0;
      double v =  1 + 2. / (AutoAngAcc::gXMax[j] - AutoAngAcc::gXMin[j]) * (x[j] - AutoAngAcc::gXMax[j]);
      // what is the power to use!
      switch(power) {
      case 1: r = 1; break; 
      case 2: r = v; break; 
      default: 
        p2 = v; 
        for (k = 3; k <= power; k++) { 
          p3 = p2 * v;
          p3 = ((2 * i - 3) * p2 * v - (i - 2) * p1) / (i - 1);
          p1 = p2; p2 = p3; 
        }
        r = p3;
      }
      // multiply this term by the poly in the jth var
      term *= r; 
    }
    // Add this term to the final result
    returnValue += term;
  }
  return returnValue;
}

// EOF for AutoAngAccMDF.cxx
