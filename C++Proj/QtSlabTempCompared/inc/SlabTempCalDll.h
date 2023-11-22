#pragma once

#ifndef SLABTEMPCALDLL_H
#define SLABTEMPCALDLL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>

//#include "MDLData.h"

#define DLLEXP extern "C" __declspec(dllexport)

DLLEXP void Tempcalc(int um, double *para, int cnt, int m,
	int matcode, int FCENo, double h, double Enttemp,
	double COFIX_REC, double COFIX_PRE, double COFIX_HEAT1, double COFIX_HEAT2, double COFIX_SOAK);


int Mspline_(int     count, double *xpts, double *ypts, double  xval, double *yval, double *slope);
void wangge_huafen(int FCENo, double h);
void ini_temp(double Entrytemp);
void fai_chaxun(int FCENo,double cacl_x, double COFIX_REC, double COFIX_PRE, double COFIX_HEAT1, double COFIX_HEAT2, double COFIX_SOAK);
void ThermalParams(double _T, int	 MatCode, double *k, double *c, double *d);
double HeatFlux(double EntryTemp, double T_dsur);
void exchange_temp();
void fz_js(int n, int FCENo, int Enttemp, double calc_x);
int  CalcDistX(int n, int FCENo, int Enttemp, double calc_x,
	double hu,		  // 上表面总括热吸收率
	double *hl,		  // 下表面总括热吸收率
	double q,			  // 热流密度
	double hact,		  // 活动梁总括热吸收率
	double ratio_out,   // 板坯脱离固定梁比例
	double ratio_in    // 板坯接触固定梁比例
);
int  CalcDistY(int n, int FCENo, int Enttemp, double calc_x,
	double hu,		  // 上表面总括热吸收率
	double *hl,		  // 下表面总括热吸收率
	double q,			  // 热流密度
	double hact,		  // 活动梁总括热吸收率
	double ratio_out,   // 板坯脱离固定梁比例
	double ratio_in    // 板坯接触固定梁比例
);

#endif
