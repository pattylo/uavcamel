/* OOQP                                                               *
 * Authors: E. Michael Gertz, Stephen J. Wright                       *
 * (C) 2001 University of Chicago. See Copyright Notification in OOQP */

#include "QpGenData.h"
#include "QpGenVars.h"
#include "QpGenResiduals.h"
#include "GondzioSolver.h"
#include "QpGenSparseMa27.h"

#include <iostream>
#include <string.h>

using namespace std;

// const int nx   = 2;
// double    c[]  = { 1.5,  -2 };

// double  xupp[] = { 20,   0 };
// char   ixupp[] = {  1,   0 };

// double  xlow[] = {  0,   0 };
// char   ixlow[] = {  1,   1 };

// const int nnzQ = 3;
// int    irowQ[] = {  0,   1,   1 }; 
// int    jcolQ[] = {  0,   0,   1 };
// double    dQ[] = {  8,   2,  10 };

// int my         = 0;
// double * b     = 0;
// int nnzA       = 0;
// int * irowA    = 0;
// int * jcolA    = 0;
// double * dA    = 0;

// const int mz   = 2;
// double clow[]  = { 2,   0 };
// char  iclow[]  = { 1,   0 };
// double cupp[]  = { 0,   6 };
// char  icupp[]  = { 0,   1 };

// const int nnzC = 4;
// int   irowC[]  = { 0,   0,   1,   1};
// int   jcolC[]  = { 0,   1,   0,   1};
// double   dC[]  = { 2,   1,  -1,   2};

/*------------------------------------------------------------TesT2*/
// //b_all
// const int nx   = 2;
// double    c[]  = { -2,  -6 };
// //l u
// double  xupp[] = { 0 };
// char   ixupp[] = { 0 };
// double  xlow[] = {  0 };
// char   ixlow[] = {  0 };
// // Q_all
// const int nnzQ = 3;
// int    irowQ[] = {  0,   1,   1 }; 
// int    jcolQ[] = {  0,   0,   1 };
// double    dQ[] = {  1,  -1,   2 };
// //Aeqbeq
// int my         = 1;
// double b[]     = {0};
// int nnzA       = 2;
// int irowA[]    = {0,0};
// int jcolA[]    = {0,1};
// double dA[]    = {1,1};
// // int my         = 0;
// // double b[]     = {0};
// // int nnzA       = 0;
// // int *irowA    = 0;
// // int *jcolA    = 0;
// // double *dA    = 0;
// //AieqBieq
// const int mz   = 3;
// double clow[]  = {0,0,0};
// char  iclow[]  = {0,0,0};
// double cupp[]  = {2,2,3};
// char  icupp[]  = {1,1,1};
// const int nnzC = 6;
// int   irowC[]  = {0,0,1,1,2,2};
// int   jcolC[]  = {0,1,0,1,0,1};
// double   dC[]  =  {1,1,-1,2,2,1};
// // const int mz   = 0;
// // double *clow  = 0;
// // char  *iclow  = 0;
// // double *cupp  = 0;
// // char  *icupp  = 0;
// // const int nnzC = 0;
// // int   *irowC  = 0;
// // int   *jcolC  = 0;
// // double   *dC  = 0;

/*------------------------------------------------------------Q_all*/
const int nnzQ = 6;
int    irowQ[] = {  3,   4,   4,    8,    9,     9}; 
int    jcolQ[] = {  3,   3,   4,    8,    8,     9};
double    dQ[] = {40,90,268,40,270,1878};
/*------------------------------------------------------------b_all*/
int nx   = 10;
double   c[]  = {0,0,0,0,0,0,0,0,0,0};  
/*------------------------------------------------------------lbub*/
double  xupp[] = {0};
char   ixupp[] = {0};
double  xlow[] = {0};
char   ixlow[] = {0};
/*----------------------------------------------------------AeqBeq*/
int my         = 9;
double  b[]    = {0,0,0,1,0,0,0,0,0};
int nnzA     = 90;
int irowA[]    = {0,0,0,0,0,0,0,0,0,0,
                  1,1,1,1,1,1,1,1,1,1,
                  2,2,2,2,2,2,2,2,2,2,
                  3,3,3,3,3,3,3,3,3,3,
                  4,4,4,4,4,4,4,4,4,4,
                  5,5,5,5,5,5,5,5,5,5,
                  6,6,6,6,6,6,6,6,6,6,
                  7,7,7,7,7,7,7,7,7,7,
                  8,8,8,8,8,8,8,8,8,8};
int   jcolA[]  = {0,1,2,3,4,5,6,7,8,9,
                  0,1,2,3,4,5,6,7,8,9,
                  0,1,2,3,4,5,6,7,8,9,
                  0,1,2,3,4,5,6,7,8,9,
                  0,1,2,3,4,5,6,7,8,9,
                  0,1,2,3,4,5,6,7,8,9,
                  0,1,2,3,4,5,6,7,8,9,
                  0,1,2,3,4,5,6,7,8,9,
                  0,1,2,3,4,5,6,7,8,9};
double   dA[]  = {1,0,0,0,0,0,0,0,0,0,
                  0,1,0,0,0,0,0,0,0,0,
                  0,0,2,0,0,0,0,0,0,0,
                  0,0,0,0,0,1,2,5,11,25,
                  0,0,0,0,0,0,1,4,15,44,
                  0,0,0,0,0,0,0,2,13,60,
                  1,1,1,1,1,-1,-1,-1,-1,-1,
                  0,1,2,3,5,0,-1,-2,-3,-5,
                  0,0,2,6,15,0,0,-2,-6,-15};
// /*------------------------------------------------------------AieqBieq*/
// const int mz   = 2;
// double clow[]  = {0,0};
// char   iclow[] = {0,0};
// double cupp[]  = {2,1};
// char  icupp[]  = {1,1};
// const int nnzC = 20;
// int  irowC[]  = {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1};
// int  jcolC[]  = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
// double   dC[] = {0,0,0,0,0,1,1.11,1.25,1.39,1.56,
//                  0,0,0,0,0,-1,-1.11,-1.25,-1.39,-1.56};
// int mz   = 1;
// char   iclow[] = {1}; 
// double clow[]  = {1}; //d
// char  icupp[]  = {1}; 
// double cupp[]  = {2}; //f
// int nnzC = 10;
// int   irowC[]  = {0,0,0,0,0,0,0,0,0,0};
// int   jcolC[]  = {0,1,2,3,4,5,6,7,8,9};
// double   dC[]  = {0,0,0,0,0,1,1.11,1.25,1.39,1.56};

const int mz   = 0;
double *clow  = 0;
char  *iclow  = 0;
double *cupp  = 0;
char  *icupp  = 0;
const int nnzC = 0;
int   *irowC  = 0;
int   *jcolC  = 0;
double   *dC  = 0;

/* Testing stuff start ehere */

void MJwp_Generator(){ // Generate a tasting set of WP for MinJerkTraj
  MJwaypoints.clear();
  Vec4 wp; // x y z yaw
  wp << 0, 0, 1, 0;
  MJwaypoints.push_back(wp);
  wp << 1, 0, 1, 0;
  MJwaypoints.push_back(wp);
  // wp << 1, 1, 1, 0;
  // MJwaypoints.push_back(wp);
  // wp << 0, 1, 1, 0;
  // MJwaypoints.push_back(wp);
  // wp << 0, 0, 1, 0;
  // MJwaypoints.push_back(wp);
}

void MinJerkTraj(deque<Vec4> MJwaypoints, double velocity){  //Min Jerk Trajectory main
  cout << "------------------------------------------------------------------------------" << endl;
  cout << "------------------------------------------------------------------------------" << endl;
  cout << "Start generating MinJerkTraj " << endl;
  //              x,y,z,yaw   (xyz in meter yaw in rad)
  double V0[4] = {0,0,0,0};
  double A0[4] = {0,0,0,0};
  double V1[4] = {0,0,0,0};
  double A1[4] = {0,0,0,0};
  double totaldist = 0;
  double totalyawrad = 0;
  int n_order = 5;
  double CorridorSize;
  /* Arrange time according to every wpts using their distance and the total velocity. */
  deque<double> dist; //Distance between each waypoints
  deque<double> yaws; //Yaw changes between each waypoints
  deque<double> ts;   //Time cost between each waypoints
  dist.clear(); yaws.clear(); ts.clear();
  /* Calc total dist and yaw*/
  for (int i = 0; i< MJwaypoints.size()-1; i++){
    Vec4 wp    = MJwaypoints.at(i);
    Vec4 nextwp = MJwaypoints.at(i+1);
    totaldist = totaldist + sqrt(pow(nextwp(0)-wp(0),2)+pow(nextwp(1)-wp(1),2)+pow(nextwp(2)-wp(2),2));
    dist.push_back(sqrt(pow(nextwp(0)-wp(0),2)+pow(nextwp(1)-wp(1),2)+pow(nextwp(2)-wp(2),2)));
  }
  double totaltime = totaldist/velocity;
  double k = totaltime/totaldist;
  ts.clear();
  ts.push_back(0);
  for (int i=0;i<dist.size();i++){
    double tss = ts.back()+dist.at(i)*k;
    ts.push_back(tss);
  }
  MinJerkPoly(MJwaypoints,0,ts,n_order,V0[1],A0[1],V1[1],A1[1]); //Second input x=0;

  // cout << "------------------------------------------------------------------------------" << endl;
  // cout << "------------------------------------------------------------------------------" << endl;
  // cout << "Minimun Jerk Traj Waypoint counts: " << wpcounts <<endl;
  // cout << "Total dist: " << totaldist << endl;
  // cout << "Total Yaw: " << totalyawrad << endl;
  // // cout << "TS count: " << ts.at(3) << endl;
  // cout << "------------------------------------------------------------------------------" << endl;
  // cout << "------------------------------------------------------------------------------" << endl;
}

int main( int argc, char * argv[] )
{
  bool useOOQP = 1;
if (useOOQP == 1){  //OOQP
  int usage_ok = 1, quiet = 0;
  // cout <<" OKOK "<<endl;
  if( argc > 2 ) usage_ok = 0;
  if( argc == 2 ) {
    if( 0 == strcmp( "--quiet", argv[1] ) ) {
      quiet = 1;
    } else {
      usage_ok = 0;
    }
  } 
  if( !usage_ok ) {
    cerr << "Usage: " <<  argv[0] << " [ --quiet ]\n";
    return 1;
  }
    
  QpGenSparseMa27 * qp 
    = new QpGenSparseMa27( nx, my, mz, nnzQ, nnzA, nnzC );
  
  QpGenData      * prob = (QpGenData * ) qp->copyDataFromSparseTriple(
        c,      irowQ,  nnzQ,   jcolQ,  dQ,
        xlow,   ixlow,  xupp,   ixupp,
        irowA,  nnzA,   jcolA,  dA,     b,
        irowC,  nnzC,   jcolC,  dC,
        clow,   iclow,  cupp,   icupp );

  QpGenVars      * vars 
    = (QpGenVars *) qp->makeVariables( prob );
  QpGenResiduals * resid 
    = (QpGenResiduals *) qp->makeResiduals( prob );
  
  GondzioSolver  * s     = new GondzioSolver( qp, prob );
  
  if( !quiet ) s->monitorSelf();
  int ierr = s->solve(prob,vars, resid);
  
  if( ierr == 0 ) {
    cout.precision(4);
    cout << "Solution: \n";
    vars->x->writefToStream( cout, "x[%{index}] = %{value}" );
  } else {
    cout << "Could not solve the problem.\n";
  }
  return ierr;
}
}