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
void err_fun(double *nom_x, double *delta_x, double *out_344773025285735819) {
   out_344773025285735819[0] = delta_x[0] + nom_x[0];
   out_344773025285735819[1] = delta_x[1] + nom_x[1];
   out_344773025285735819[2] = delta_x[2] + nom_x[2];
   out_344773025285735819[3] = delta_x[3] + nom_x[3];
   out_344773025285735819[4] = delta_x[4] + nom_x[4];
   out_344773025285735819[5] = delta_x[5] + nom_x[5];
   out_344773025285735819[6] = delta_x[6] + nom_x[6];
   out_344773025285735819[7] = delta_x[7] + nom_x[7];
   out_344773025285735819[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8115144850596300460) {
   out_8115144850596300460[0] = -nom_x[0] + true_x[0];
   out_8115144850596300460[1] = -nom_x[1] + true_x[1];
   out_8115144850596300460[2] = -nom_x[2] + true_x[2];
   out_8115144850596300460[3] = -nom_x[3] + true_x[3];
   out_8115144850596300460[4] = -nom_x[4] + true_x[4];
   out_8115144850596300460[5] = -nom_x[5] + true_x[5];
   out_8115144850596300460[6] = -nom_x[6] + true_x[6];
   out_8115144850596300460[7] = -nom_x[7] + true_x[7];
   out_8115144850596300460[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2122213824906596317) {
   out_2122213824906596317[0] = 1.0;
   out_2122213824906596317[1] = 0;
   out_2122213824906596317[2] = 0;
   out_2122213824906596317[3] = 0;
   out_2122213824906596317[4] = 0;
   out_2122213824906596317[5] = 0;
   out_2122213824906596317[6] = 0;
   out_2122213824906596317[7] = 0;
   out_2122213824906596317[8] = 0;
   out_2122213824906596317[9] = 0;
   out_2122213824906596317[10] = 1.0;
   out_2122213824906596317[11] = 0;
   out_2122213824906596317[12] = 0;
   out_2122213824906596317[13] = 0;
   out_2122213824906596317[14] = 0;
   out_2122213824906596317[15] = 0;
   out_2122213824906596317[16] = 0;
   out_2122213824906596317[17] = 0;
   out_2122213824906596317[18] = 0;
   out_2122213824906596317[19] = 0;
   out_2122213824906596317[20] = 1.0;
   out_2122213824906596317[21] = 0;
   out_2122213824906596317[22] = 0;
   out_2122213824906596317[23] = 0;
   out_2122213824906596317[24] = 0;
   out_2122213824906596317[25] = 0;
   out_2122213824906596317[26] = 0;
   out_2122213824906596317[27] = 0;
   out_2122213824906596317[28] = 0;
   out_2122213824906596317[29] = 0;
   out_2122213824906596317[30] = 1.0;
   out_2122213824906596317[31] = 0;
   out_2122213824906596317[32] = 0;
   out_2122213824906596317[33] = 0;
   out_2122213824906596317[34] = 0;
   out_2122213824906596317[35] = 0;
   out_2122213824906596317[36] = 0;
   out_2122213824906596317[37] = 0;
   out_2122213824906596317[38] = 0;
   out_2122213824906596317[39] = 0;
   out_2122213824906596317[40] = 1.0;
   out_2122213824906596317[41] = 0;
   out_2122213824906596317[42] = 0;
   out_2122213824906596317[43] = 0;
   out_2122213824906596317[44] = 0;
   out_2122213824906596317[45] = 0;
   out_2122213824906596317[46] = 0;
   out_2122213824906596317[47] = 0;
   out_2122213824906596317[48] = 0;
   out_2122213824906596317[49] = 0;
   out_2122213824906596317[50] = 1.0;
   out_2122213824906596317[51] = 0;
   out_2122213824906596317[52] = 0;
   out_2122213824906596317[53] = 0;
   out_2122213824906596317[54] = 0;
   out_2122213824906596317[55] = 0;
   out_2122213824906596317[56] = 0;
   out_2122213824906596317[57] = 0;
   out_2122213824906596317[58] = 0;
   out_2122213824906596317[59] = 0;
   out_2122213824906596317[60] = 1.0;
   out_2122213824906596317[61] = 0;
   out_2122213824906596317[62] = 0;
   out_2122213824906596317[63] = 0;
   out_2122213824906596317[64] = 0;
   out_2122213824906596317[65] = 0;
   out_2122213824906596317[66] = 0;
   out_2122213824906596317[67] = 0;
   out_2122213824906596317[68] = 0;
   out_2122213824906596317[69] = 0;
   out_2122213824906596317[70] = 1.0;
   out_2122213824906596317[71] = 0;
   out_2122213824906596317[72] = 0;
   out_2122213824906596317[73] = 0;
   out_2122213824906596317[74] = 0;
   out_2122213824906596317[75] = 0;
   out_2122213824906596317[76] = 0;
   out_2122213824906596317[77] = 0;
   out_2122213824906596317[78] = 0;
   out_2122213824906596317[79] = 0;
   out_2122213824906596317[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3194357031179583653) {
   out_3194357031179583653[0] = state[0];
   out_3194357031179583653[1] = state[1];
   out_3194357031179583653[2] = state[2];
   out_3194357031179583653[3] = state[3];
   out_3194357031179583653[4] = state[4];
   out_3194357031179583653[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3194357031179583653[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3194357031179583653[7] = state[7];
   out_3194357031179583653[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8656604033789363826) {
   out_8656604033789363826[0] = 1;
   out_8656604033789363826[1] = 0;
   out_8656604033789363826[2] = 0;
   out_8656604033789363826[3] = 0;
   out_8656604033789363826[4] = 0;
   out_8656604033789363826[5] = 0;
   out_8656604033789363826[6] = 0;
   out_8656604033789363826[7] = 0;
   out_8656604033789363826[8] = 0;
   out_8656604033789363826[9] = 0;
   out_8656604033789363826[10] = 1;
   out_8656604033789363826[11] = 0;
   out_8656604033789363826[12] = 0;
   out_8656604033789363826[13] = 0;
   out_8656604033789363826[14] = 0;
   out_8656604033789363826[15] = 0;
   out_8656604033789363826[16] = 0;
   out_8656604033789363826[17] = 0;
   out_8656604033789363826[18] = 0;
   out_8656604033789363826[19] = 0;
   out_8656604033789363826[20] = 1;
   out_8656604033789363826[21] = 0;
   out_8656604033789363826[22] = 0;
   out_8656604033789363826[23] = 0;
   out_8656604033789363826[24] = 0;
   out_8656604033789363826[25] = 0;
   out_8656604033789363826[26] = 0;
   out_8656604033789363826[27] = 0;
   out_8656604033789363826[28] = 0;
   out_8656604033789363826[29] = 0;
   out_8656604033789363826[30] = 1;
   out_8656604033789363826[31] = 0;
   out_8656604033789363826[32] = 0;
   out_8656604033789363826[33] = 0;
   out_8656604033789363826[34] = 0;
   out_8656604033789363826[35] = 0;
   out_8656604033789363826[36] = 0;
   out_8656604033789363826[37] = 0;
   out_8656604033789363826[38] = 0;
   out_8656604033789363826[39] = 0;
   out_8656604033789363826[40] = 1;
   out_8656604033789363826[41] = 0;
   out_8656604033789363826[42] = 0;
   out_8656604033789363826[43] = 0;
   out_8656604033789363826[44] = 0;
   out_8656604033789363826[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8656604033789363826[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8656604033789363826[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8656604033789363826[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8656604033789363826[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8656604033789363826[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8656604033789363826[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8656604033789363826[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8656604033789363826[53] = -9.8000000000000007*dt;
   out_8656604033789363826[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8656604033789363826[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8656604033789363826[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8656604033789363826[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8656604033789363826[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8656604033789363826[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8656604033789363826[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8656604033789363826[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8656604033789363826[62] = 0;
   out_8656604033789363826[63] = 0;
   out_8656604033789363826[64] = 0;
   out_8656604033789363826[65] = 0;
   out_8656604033789363826[66] = 0;
   out_8656604033789363826[67] = 0;
   out_8656604033789363826[68] = 0;
   out_8656604033789363826[69] = 0;
   out_8656604033789363826[70] = 1;
   out_8656604033789363826[71] = 0;
   out_8656604033789363826[72] = 0;
   out_8656604033789363826[73] = 0;
   out_8656604033789363826[74] = 0;
   out_8656604033789363826[75] = 0;
   out_8656604033789363826[76] = 0;
   out_8656604033789363826[77] = 0;
   out_8656604033789363826[78] = 0;
   out_8656604033789363826[79] = 0;
   out_8656604033789363826[80] = 1;
}
void h_25(double *state, double *unused, double *out_721844597343897651) {
   out_721844597343897651[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3342677436150207327) {
   out_3342677436150207327[0] = 0;
   out_3342677436150207327[1] = 0;
   out_3342677436150207327[2] = 0;
   out_3342677436150207327[3] = 0;
   out_3342677436150207327[4] = 0;
   out_3342677436150207327[5] = 0;
   out_3342677436150207327[6] = 1;
   out_3342677436150207327[7] = 0;
   out_3342677436150207327[8] = 0;
}
void h_24(double *state, double *unused, double *out_584620759994682920) {
   out_584620759994682920[0] = state[4];
   out_584620759994682920[1] = state[5];
}
void H_24(double *state, double *unused, double *out_215248162652115809) {
   out_215248162652115809[0] = 0;
   out_215248162652115809[1] = 0;
   out_215248162652115809[2] = 0;
   out_215248162652115809[3] = 0;
   out_215248162652115809[4] = 1;
   out_215248162652115809[5] = 0;
   out_215248162652115809[6] = 0;
   out_215248162652115809[7] = 0;
   out_215248162652115809[8] = 0;
   out_215248162652115809[9] = 0;
   out_215248162652115809[10] = 0;
   out_215248162652115809[11] = 0;
   out_215248162652115809[12] = 0;
   out_215248162652115809[13] = 0;
   out_215248162652115809[14] = 1;
   out_215248162652115809[15] = 0;
   out_215248162652115809[16] = 0;
   out_215248162652115809[17] = 0;
}
void h_30(double *state, double *unused, double *out_6738714166904990674) {
   out_6738714166904990674[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3472016383293447397) {
   out_3472016383293447397[0] = 0;
   out_3472016383293447397[1] = 0;
   out_3472016383293447397[2] = 0;
   out_3472016383293447397[3] = 0;
   out_3472016383293447397[4] = 1;
   out_3472016383293447397[5] = 0;
   out_3472016383293447397[6] = 0;
   out_3472016383293447397[7] = 0;
   out_3472016383293447397[8] = 0;
}
void h_26(double *state, double *unused, double *out_6706356639143715297) {
   out_6706356639143715297[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2685823372039895423) {
   out_2685823372039895423[0] = 0;
   out_2685823372039895423[1] = 0;
   out_2685823372039895423[2] = 0;
   out_2685823372039895423[3] = 0;
   out_2685823372039895423[4] = 0;
   out_2685823372039895423[5] = 0;
   out_2685823372039895423[6] = 0;
   out_2685823372039895423[7] = 1;
   out_2685823372039895423[8] = 0;
}
void h_27(double *state, double *unused, double *out_221665255557764784) {
   out_221665255557764784[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5646779695093872308) {
   out_5646779695093872308[0] = 0;
   out_5646779695093872308[1] = 0;
   out_5646779695093872308[2] = 0;
   out_5646779695093872308[3] = 1;
   out_5646779695093872308[4] = 0;
   out_5646779695093872308[5] = 0;
   out_5646779695093872308[6] = 0;
   out_5646779695093872308[7] = 0;
   out_5646779695093872308[8] = 0;
}
void h_29(double *state, double *unused, double *out_8671243855360228257) {
   out_8671243855360228257[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2961785038979055213) {
   out_2961785038979055213[0] = 0;
   out_2961785038979055213[1] = 1;
   out_2961785038979055213[2] = 0;
   out_2961785038979055213[3] = 0;
   out_2961785038979055213[4] = 0;
   out_2961785038979055213[5] = 0;
   out_2961785038979055213[6] = 0;
   out_2961785038979055213[7] = 0;
   out_2961785038979055213[8] = 0;
}
void h_28(double *state, double *unused, double *out_4780008012103080861) {
   out_4780008012103080861[0] = state[0];
}
void H_28(double *state, double *unused, double *out_998154767413728962) {
   out_998154767413728962[0] = 1;
   out_998154767413728962[1] = 0;
   out_998154767413728962[2] = 0;
   out_998154767413728962[3] = 0;
   out_998154767413728962[4] = 0;
   out_998154767413728962[5] = 0;
   out_998154767413728962[6] = 0;
   out_998154767413728962[7] = 0;
   out_998154767413728962[8] = 0;
}
void h_31(double *state, double *unused, double *out_879031265695026796) {
   out_879031265695026796[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3312031474273246899) {
   out_3312031474273246899[0] = 0;
   out_3312031474273246899[1] = 0;
   out_3312031474273246899[2] = 0;
   out_3312031474273246899[3] = 0;
   out_3312031474273246899[4] = 0;
   out_3312031474273246899[5] = 0;
   out_3312031474273246899[6] = 0;
   out_3312031474273246899[7] = 0;
   out_3312031474273246899[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_344773025285735819) {
  err_fun(nom_x, delta_x, out_344773025285735819);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8115144850596300460) {
  inv_err_fun(nom_x, true_x, out_8115144850596300460);
}
void car_H_mod_fun(double *state, double *out_2122213824906596317) {
  H_mod_fun(state, out_2122213824906596317);
}
void car_f_fun(double *state, double dt, double *out_3194357031179583653) {
  f_fun(state,  dt, out_3194357031179583653);
}
void car_F_fun(double *state, double dt, double *out_8656604033789363826) {
  F_fun(state,  dt, out_8656604033789363826);
}
void car_h_25(double *state, double *unused, double *out_721844597343897651) {
  h_25(state, unused, out_721844597343897651);
}
void car_H_25(double *state, double *unused, double *out_3342677436150207327) {
  H_25(state, unused, out_3342677436150207327);
}
void car_h_24(double *state, double *unused, double *out_584620759994682920) {
  h_24(state, unused, out_584620759994682920);
}
void car_H_24(double *state, double *unused, double *out_215248162652115809) {
  H_24(state, unused, out_215248162652115809);
}
void car_h_30(double *state, double *unused, double *out_6738714166904990674) {
  h_30(state, unused, out_6738714166904990674);
}
void car_H_30(double *state, double *unused, double *out_3472016383293447397) {
  H_30(state, unused, out_3472016383293447397);
}
void car_h_26(double *state, double *unused, double *out_6706356639143715297) {
  h_26(state, unused, out_6706356639143715297);
}
void car_H_26(double *state, double *unused, double *out_2685823372039895423) {
  H_26(state, unused, out_2685823372039895423);
}
void car_h_27(double *state, double *unused, double *out_221665255557764784) {
  h_27(state, unused, out_221665255557764784);
}
void car_H_27(double *state, double *unused, double *out_5646779695093872308) {
  H_27(state, unused, out_5646779695093872308);
}
void car_h_29(double *state, double *unused, double *out_8671243855360228257) {
  h_29(state, unused, out_8671243855360228257);
}
void car_H_29(double *state, double *unused, double *out_2961785038979055213) {
  H_29(state, unused, out_2961785038979055213);
}
void car_h_28(double *state, double *unused, double *out_4780008012103080861) {
  h_28(state, unused, out_4780008012103080861);
}
void car_H_28(double *state, double *unused, double *out_998154767413728962) {
  H_28(state, unused, out_998154767413728962);
}
void car_h_31(double *state, double *unused, double *out_879031265695026796) {
  h_31(state, unused, out_879031265695026796);
}
void car_H_31(double *state, double *unused, double *out_3312031474273246899) {
  H_31(state, unused, out_3312031474273246899);
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
