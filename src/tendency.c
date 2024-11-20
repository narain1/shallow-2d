
#include <stdio.h>
/*****************************************************************/
// The functions dudx_at_h, dvdy_at_h,dhdx_at_u,dhdy_at_v                    
// need to be modified for parallelization. Use flux_x and flux_y as guides      
/*****************************************************************/
/*****************************************************************/
// void  dudx_at_h( double ** fl_x, double ** restrict  dudx, double dx, int nx, int ny) { 
//   int ix , iy;
//   for (iy = 0; iy <= ny - 1; iy++) {
//       for (ix = 0; ix <= nx - 2; ix++) {
//           dudx[iy][ix] = (fl_x[iy][ix + 1] - fl_x[iy][ix]) / dx;
//       }
//   }

//   for (iy = 0; iy <= ny - 1; iy++) {
//       dudx[iy][nx - 1] = (fl_x[iy][0] - fl_x[iy][nx - 1]) / dx;
//   }
// } 
void dudx_at_h(double ** fl_x, double ** restrict dudx, double dx, int nx, int ny, int j_st, int j_en) {
  int ix, iy;
  for (iy = j_st; iy <= j_en; iy++) {
    for (ix = 0; ix < nx - 1; ix++) {
      dudx[iy][ix] = (fl_x[iy][ix + 1] - fl_x[iy][ix]) / dx;
    }
    dudx[iy][nx - 1] = (fl_x[iy][0] - fl_x[iy][nx - 1]) / dx;
  }
}

/*****************************************************************/
// void  dvdy_at_h(  double ** fl_y, double ** restrict  dvdy, double dy, int nx, int ny) {
//   int ix , iy ;
//   for (iy = 0; iy <= ny - 2; iy++) {
//       for (ix = 0; ix <= nx - 1; ix++) {
//           dvdy[iy][ix] = (fl_y[iy + 1][ix] - fl_y[iy][ix]) / dy;
//       }
//   }

//   for (ix = 0; ix <= nx - 1; ix++) {
//       dvdy[ny - 1][ix] = (fl_y[0][ix] - fl_y[ny - 1][ix]) / dy;
//   }
// }

void dvdy_at_h(double ** fl_y, double ** restrict dvdy, double dy, int nx, int ny, int j_st, int j_en) {
    int ix, iy;
    for (iy = j_st; iy <= j_en; iy++) {
        for (ix = 0; ix < nx; ix++) {
            if (iy < ny - 1) {
                dvdy[iy][ix] = (fl_y[iy + 1][ix] - fl_y[iy][ix]) / dy;
            } else {
                dvdy[iy][ix] = (fl_y[0][ix] - fl_y[ny - 1][ix]) / dy;
            }
        }
    }
}

/*****************************************************************/
// void  dhdx_at_u(  double ** fl_x, double ** restrict  dhdx, double dx, int nx, int ny) {
//   int ix , iy;

//   for(  iy = 0; iy <= ny-1;  iy++ )
//     { for(  ix = 1; ix <= nx-1;  ix++ )
//         {
//           dhdx[iy][ix]=(fl_x[iy][ix]-fl_x[iy][ix-1])/dx;
//         }
//     }

//   for(  iy = 0; iy <= ny-1;  iy++ )
//     {
//       dhdx[iy][0]=(fl_x[iy][0]-fl_x[iy][nx-1])/dx;
//     }
// }

void dhdx_at_u(double ** fl_x, double ** restrict dhdx, double dx, int nx, int ny, int j_st, int j_en) {
    int ix, iy;
    for (iy = j_st; iy <= j_en; iy++) {
        dhdx[iy][0] = (fl_x[iy][0] - fl_x[iy][nx - 1]) / dx;
        for (ix = 1; ix < nx; ix++) {
            dhdx[iy][ix] = (fl_x[iy][ix] - fl_x[iy][ix - 1]) / dx;
        }
    }
}

// void  dhdy_at_v( double ** fl_y,  double ** restrict  dhdy, double dy, int nx, int ny) {
//   int ix , iy;


//   for(  iy = 1; iy <= ny-1;  iy++ )
//   { for(  ix = 0; ix <= nx-1;  ix++ )
//       {
//         dhdy[iy][ix]=(fl_y[iy][ix]-fl_y[iy-1][ix])/dy;
//       }
//   }

//   for(  ix = 0; ix <= nx-1;  ix++ )
//     {
//       dhdy[0][ix]=(fl_y[0][ix]-fl_y[ny-1][ix])/dy;
//     }
// }

void dhdy_at_v(double ** fl_y, double ** restrict dhdy, double dy, int nx, int ny, int j_st, int j_en) {
    int ix, iy;
    for (iy = j_st; iy <= j_en; iy++) {
        for (ix = 0; ix < nx; ix++) {
            if (iy > 0) {
                dhdy[iy][ix] = (fl_y[iy][ix] - fl_y[iy - 1][ix]) / dy;
            } else {
                dhdy[iy][ix] = (fl_y[0][ix] - fl_y[ny - 1][ix]) / dy;
            }
        }
    }
}