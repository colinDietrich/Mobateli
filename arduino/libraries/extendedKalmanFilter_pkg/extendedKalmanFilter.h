/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: extendedKalmanFilter1RC.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 28-Jul-2022 14:01:04
 */

#ifndef EXTENDEDKALMANFILTER_H
#define EXTENDEDKALMANFILTER_H

/* Include Files */
//#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  extern double extendedKalmanFilter(double b_I, double I2, double *X, double *Z,
                                     const double SOCOCV[5], const double dSOCOCV[4], double Vt_Actual, double *P_x,
                                     double *P_z, const double *Q_x, const double *Q_z, double *betha_x,
                                     double *betha_z, double *alpha_x, double *alpha_z, double rho_x, double rho_z,
                                     double DeltaT, double Qn_rated);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for extendedKalmanFilter1RC.h
 *
 * [EOF]
 */
