// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

// global 
#define VERSION 1.0

// mapgraphics
const int SECTORSIZE = 200000; // 100000 in all directions

// naventry
enum NavCompare
{
	NAVPOS=1,
	NAVSECTOR=2,
	NAVTYPE=4,
	NAVNAME=8,
	NAVVALUE=16,
	NAVPARENT=32,
	NAVID=64,
	NAVRANGE=128,
	NAVTRILAT=256
};

// navdata
#define NAVHEADER "Map Log Locations"
#define NAVOUT "Nav Output"
#define TRILATOUT "Trilateration.csv"
#define MAXZERO 0.0001
const int VISITRANGE = 5000;

// route
const double MAXINT = 1.7E+308;