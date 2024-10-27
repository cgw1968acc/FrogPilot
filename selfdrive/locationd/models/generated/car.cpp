#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4843913742274801883) {
   out_4843913742274801883[0] = delta_x[0] + nom_x[0];
   out_4843913742274801883[1] = delta_x[1] + nom_x[1];
   out_4843913742274801883[2] = delta_x[2] + nom_x[2];
   out_4843913742274801883[3] = delta_x[3] + nom_x[3];
   out_4843913742274801883[4] = delta_x[4] + nom_x[4];
   out_4843913742274801883[5] = delta_x[5] + nom_x[5];
   out_4843913742274801883[6] = delta_x[6] + nom_x[6];
   out_4843913742274801883[7] = delta_x[7] + nom_x[7];
   out_4843913742274801883[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3141489684841063801) {
   out_3141489684841063801[0] = -nom_x[0] + true_x[0];
   out_3141489684841063801[1] = -nom_x[1] + true_x[1];
   out_3141489684841063801[2] = -nom_x[2] + true_x[2];
   out_3141489684841063801[3] = -nom_x[3] + true_x[3];
   out_3141489684841063801[4] = -nom_x[4] + true_x[4];
   out_3141489684841063801[5] = -nom_x[5] + true_x[5];
   out_3141489684841063801[6] = -nom_x[6] + true_x[6];
   out_3141489684841063801[7] = -nom_x[7] + true_x[7];
   out_3141489684841063801[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_622781938203757755) {
   out_622781938203757755[0] = 1.0;
   out_622781938203757755[1] = 0;
   out_622781938203757755[2] = 0;
   out_622781938203757755[3] = 0;
   out_622781938203757755[4] = 0;
   out_622781938203757755[5] = 0;
   out_622781938203757755[6] = 0;
   out_622781938203757755[7] = 0;
   out_622781938203757755[8] = 0;
   out_622781938203757755[9] = 0;
   out_622781938203757755[10] = 1.0;
   out_622781938203757755[11] = 0;
   out_622781938203757755[12] = 0;
   out_622781938203757755[13] = 0;
   out_622781938203757755[14] = 0;
   out_622781938203757755[15] = 0;
   out_622781938203757755[16] = 0;
   out_622781938203757755[17] = 0;
   out_622781938203757755[18] = 0;
   out_622781938203757755[19] = 0;
   out_622781938203757755[20] = 1.0;
   out_622781938203757755[21] = 0;
   out_622781938203757755[22] = 0;
   out_622781938203757755[23] = 0;
   out_622781938203757755[24] = 0;
   out_622781938203757755[25] = 0;
   out_622781938203757755[26] = 0;
   out_622781938203757755[27] = 0;
   out_622781938203757755[28] = 0;
   out_622781938203757755[29] = 0;
   out_622781938203757755[30] = 1.0;
   out_622781938203757755[31] = 0;
   out_622781938203757755[32] = 0;
   out_622781938203757755[33] = 0;
   out_622781938203757755[34] = 0;
   out_622781938203757755[35] = 0;
   out_622781938203757755[36] = 0;
   out_622781938203757755[37] = 0;
   out_622781938203757755[38] = 0;
   out_622781938203757755[39] = 0;
   out_622781938203757755[40] = 1.0;
   out_622781938203757755[41] = 0;
   out_622781938203757755[42] = 0;
   out_622781938203757755[43] = 0;
   out_622781938203757755[44] = 0;
   out_622781938203757755[45] = 0;
   out_622781938203757755[46] = 0;
   out_622781938203757755[47] = 0;
   out_622781938203757755[48] = 0;
   out_622781938203757755[49] = 0;
   out_622781938203757755[50] = 1.0;
   out_622781938203757755[51] = 0;
   out_622781938203757755[52] = 0;
   out_622781938203757755[53] = 0;
   out_622781938203757755[54] = 0;
   out_622781938203757755[55] = 0;
   out_622781938203757755[56] = 0;
   out_622781938203757755[57] = 0;
   out_622781938203757755[58] = 0;
   out_622781938203757755[59] = 0;
   out_622781938203757755[60] = 1.0;
   out_622781938203757755[61] = 0;
   out_622781938203757755[62] = 0;
   out_622781938203757755[63] = 0;
   out_622781938203757755[64] = 0;
   out_622781938203757755[65] = 0;
   out_622781938203757755[66] = 0;
   out_622781938203757755[67] = 0;
   out_622781938203757755[68] = 0;
   out_622781938203757755[69] = 0;
   out_622781938203757755[70] = 1.0;
   out_622781938203757755[71] = 0;
   out_622781938203757755[72] = 0;
   out_622781938203757755[73] = 0;
   out_622781938203757755[74] = 0;
   out_622781938203757755[75] = 0;
   out_622781938203757755[76] = 0;
   out_622781938203757755[77] = 0;
   out_622781938203757755[78] = 0;
   out_622781938203757755[79] = 0;
   out_622781938203757755[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8331812568446399394) {
   out_8331812568446399394[0] = state[0];
   out_8331812568446399394[1] = state[1];
   out_8331812568446399394[2] = state[2];
   out_8331812568446399394[3] = state[3];
   out_8331812568446399394[4] = state[4];
   out_8331812568446399394[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8331812568446399394[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8331812568446399394[7] = state[7];
   out_8331812568446399394[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4433888243299038369) {
   out_4433888243299038369[0] = 1;
   out_4433888243299038369[1] = 0;
   out_4433888243299038369[2] = 0;
   out_4433888243299038369[3] = 0;
   out_4433888243299038369[4] = 0;
   out_4433888243299038369[5] = 0;
   out_4433888243299038369[6] = 0;
   out_4433888243299038369[7] = 0;
   out_4433888243299038369[8] = 0;
   out_4433888243299038369[9] = 0;
   out_4433888243299038369[10] = 1;
   out_4433888243299038369[11] = 0;
   out_4433888243299038369[12] = 0;
   out_4433888243299038369[13] = 0;
   out_4433888243299038369[14] = 0;
   out_4433888243299038369[15] = 0;
   out_4433888243299038369[16] = 0;
   out_4433888243299038369[17] = 0;
   out_4433888243299038369[18] = 0;
   out_4433888243299038369[19] = 0;
   out_4433888243299038369[20] = 1;
   out_4433888243299038369[21] = 0;
   out_4433888243299038369[22] = 0;
   out_4433888243299038369[23] = 0;
   out_4433888243299038369[24] = 0;
   out_4433888243299038369[25] = 0;
   out_4433888243299038369[26] = 0;
   out_4433888243299038369[27] = 0;
   out_4433888243299038369[28] = 0;
   out_4433888243299038369[29] = 0;
   out_4433888243299038369[30] = 1;
   out_4433888243299038369[31] = 0;
   out_4433888243299038369[32] = 0;
   out_4433888243299038369[33] = 0;
   out_4433888243299038369[34] = 0;
   out_4433888243299038369[35] = 0;
   out_4433888243299038369[36] = 0;
   out_4433888243299038369[37] = 0;
   out_4433888243299038369[38] = 0;
   out_4433888243299038369[39] = 0;
   out_4433888243299038369[40] = 1;
   out_4433888243299038369[41] = 0;
   out_4433888243299038369[42] = 0;
   out_4433888243299038369[43] = 0;
   out_4433888243299038369[44] = 0;
   out_4433888243299038369[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4433888243299038369[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4433888243299038369[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4433888243299038369[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4433888243299038369[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4433888243299038369[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4433888243299038369[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4433888243299038369[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4433888243299038369[53] = -9.8000000000000007*dt;
   out_4433888243299038369[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4433888243299038369[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4433888243299038369[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4433888243299038369[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4433888243299038369[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4433888243299038369[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4433888243299038369[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4433888243299038369[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4433888243299038369[62] = 0;
   out_4433888243299038369[63] = 0;
   out_4433888243299038369[64] = 0;
   out_4433888243299038369[65] = 0;
   out_4433888243299038369[66] = 0;
   out_4433888243299038369[67] = 0;
   out_4433888243299038369[68] = 0;
   out_4433888243299038369[69] = 0;
   out_4433888243299038369[70] = 1;
   out_4433888243299038369[71] = 0;
   out_4433888243299038369[72] = 0;
   out_4433888243299038369[73] = 0;
   out_4433888243299038369[74] = 0;
   out_4433888243299038369[75] = 0;
   out_4433888243299038369[76] = 0;
   out_4433888243299038369[77] = 0;
   out_4433888243299038369[78] = 0;
   out_4433888243299038369[79] = 0;
   out_4433888243299038369[80] = 1;
}
void h_25(double *state, double *unused, double *out_5793819887660240129) {
   out_5793819887660240129[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2516470844129107004) {
   out_2516470844129107004[0] = 0;
   out_2516470844129107004[1] = 0;
   out_2516470844129107004[2] = 0;
   out_2516470844129107004[3] = 0;
   out_2516470844129107004[4] = 0;
   out_2516470844129107004[5] = 0;
   out_2516470844129107004[6] = 1;
   out_2516470844129107004[7] = 0;
   out_2516470844129107004[8] = 0;
}
void h_24(double *state, double *unused, double *out_2496335967820069887) {
   out_2496335967820069887[0] = state[4];
   out_2496335967820069887[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7262980171095616038) {
   out_7262980171095616038[0] = 0;
   out_7262980171095616038[1] = 0;
   out_7262980171095616038[2] = 0;
   out_7262980171095616038[3] = 0;
   out_7262980171095616038[4] = 1;
   out_7262980171095616038[5] = 0;
   out_7262980171095616038[6] = 0;
   out_7262980171095616038[7] = 0;
   out_7262980171095616038[8] = 0;
   out_7262980171095616038[9] = 0;
   out_7262980171095616038[10] = 0;
   out_7262980171095616038[11] = 0;
   out_7262980171095616038[12] = 0;
   out_7262980171095616038[13] = 0;
   out_7262980171095616038[14] = 1;
   out_7262980171095616038[15] = 0;
   out_7262980171095616038[16] = 0;
   out_7262980171095616038[17] = 0;
}
void h_30(double *state, double *unused, double *out_4968131473625943860) {
   out_4968131473625943860[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4400219497362509751) {
   out_4400219497362509751[0] = 0;
   out_4400219497362509751[1] = 0;
   out_4400219497362509751[2] = 0;
   out_4400219497362509751[3] = 0;
   out_4400219497362509751[4] = 1;
   out_4400219497362509751[5] = 0;
   out_4400219497362509751[6] = 0;
   out_4400219497362509751[7] = 0;
   out_4400219497362509751[8] = 0;
}
void h_26(double *state, double *unused, double *out_3828177990640053280) {
   out_3828177990640053280[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6257974163003163228) {
   out_6257974163003163228[0] = 0;
   out_6257974163003163228[1] = 0;
   out_6257974163003163228[2] = 0;
   out_6257974163003163228[3] = 0;
   out_6257974163003163228[4] = 0;
   out_6257974163003163228[5] = 0;
   out_6257974163003163228[6] = 0;
   out_6257974163003163228[7] = 1;
   out_6257974163003163228[8] = 0;
}
void h_27(double *state, double *unused, double *out_6961563688736381866) {
   out_6961563688736381866[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2225456185562084840) {
   out_2225456185562084840[0] = 0;
   out_2225456185562084840[1] = 0;
   out_2225456185562084840[2] = 0;
   out_2225456185562084840[3] = 1;
   out_2225456185562084840[4] = 0;
   out_2225456185562084840[5] = 0;
   out_2225456185562084840[6] = 0;
   out_2225456185562084840[7] = 0;
   out_2225456185562084840[8] = 0;
}
void h_29(double *state, double *unused, double *out_4024621620724281425) {
   out_4024621620724281425[0] = state[1];
}
void H_29(double *state, double *unused, double *out_512093458692533807) {
   out_512093458692533807[0] = 0;
   out_512093458692533807[1] = 1;
   out_512093458692533807[2] = 0;
   out_512093458692533807[3] = 0;
   out_512093458692533807[4] = 0;
   out_512093458692533807[5] = 0;
   out_512093458692533807[6] = 0;
   out_512093458692533807[7] = 0;
   out_512093458692533807[8] = 0;
}
void h_28(double *state, double *unused, double *out_5086138867559320604) {
   out_5086138867559320604[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4570305558376996767) {
   out_4570305558376996767[0] = 1;
   out_4570305558376996767[1] = 0;
   out_4570305558376996767[2] = 0;
   out_4570305558376996767[3] = 0;
   out_4570305558376996767[4] = 0;
   out_4570305558376996767[5] = 0;
   out_4570305558376996767[6] = 0;
   out_4570305558376996767[7] = 0;
   out_4570305558376996767[8] = 0;
}
void h_31(double *state, double *unused, double *out_7244414972042669883) {
   out_7244414972042669883[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2485824882252146576) {
   out_2485824882252146576[0] = 0;
   out_2485824882252146576[1] = 0;
   out_2485824882252146576[2] = 0;
   out_2485824882252146576[3] = 0;
   out_2485824882252146576[4] = 0;
   out_2485824882252146576[5] = 0;
   out_2485824882252146576[6] = 0;
   out_2485824882252146576[7] = 0;
   out_2485824882252146576[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_4843913742274801883) {
  err_fun(nom_x, delta_x, out_4843913742274801883);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3141489684841063801) {
  inv_err_fun(nom_x, true_x, out_3141489684841063801);
}
void car_H_mod_fun(double *state, double *out_622781938203757755) {
  H_mod_fun(state, out_622781938203757755);
}
void car_f_fun(double *state, double dt, double *out_8331812568446399394) {
  f_fun(state,  dt, out_8331812568446399394);
}
void car_F_fun(double *state, double dt, double *out_4433888243299038369) {
  F_fun(state,  dt, out_4433888243299038369);
}
void car_h_25(double *state, double *unused, double *out_5793819887660240129) {
  h_25(state, unused, out_5793819887660240129);
}
void car_H_25(double *state, double *unused, double *out_2516470844129107004) {
  H_25(state, unused, out_2516470844129107004);
}
void car_h_24(double *state, double *unused, double *out_2496335967820069887) {
  h_24(state, unused, out_2496335967820069887);
}
void car_H_24(double *state, double *unused, double *out_7262980171095616038) {
  H_24(state, unused, out_7262980171095616038);
}
void car_h_30(double *state, double *unused, double *out_4968131473625943860) {
  h_30(state, unused, out_4968131473625943860);
}
void car_H_30(double *state, double *unused, double *out_4400219497362509751) {
  H_30(state, unused, out_4400219497362509751);
}
void car_h_26(double *state, double *unused, double *out_3828177990640053280) {
  h_26(state, unused, out_3828177990640053280);
}
void car_H_26(double *state, double *unused, double *out_6257974163003163228) {
  H_26(state, unused, out_6257974163003163228);
}
void car_h_27(double *state, double *unused, double *out_6961563688736381866) {
  h_27(state, unused, out_6961563688736381866);
}
void car_H_27(double *state, double *unused, double *out_2225456185562084840) {
  H_27(state, unused, out_2225456185562084840);
}
void car_h_29(double *state, double *unused, double *out_4024621620724281425) {
  h_29(state, unused, out_4024621620724281425);
}
void car_H_29(double *state, double *unused, double *out_512093458692533807) {
  H_29(state, unused, out_512093458692533807);
}
void car_h_28(double *state, double *unused, double *out_5086138867559320604) {
  h_28(state, unused, out_5086138867559320604);
}
void car_H_28(double *state, double *unused, double *out_4570305558376996767) {
  H_28(state, unused, out_4570305558376996767);
}
void car_h_31(double *state, double *unused, double *out_7244414972042669883) {
  h_31(state, unused, out_7244414972042669883);
}
void car_H_31(double *state, double *unused, double *out_2485824882252146576) {
  H_31(state, unused, out_2485824882252146576);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
