/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: Dataflow
 * File: GeneralDefines.h
 * Author: k1008014
 * Created: July 13, 2020
 *******************************************************************/

#ifndef GENERAL_DEFINES_H
#define GENERAL_DEFINES_H

//#define _DATAFLOW_LOGGER

#include <bur/plctypes.h>

namespace dataflow
{

	enum _types { _INT, _DOUBLE, _FLOAT, _CHAR, _STRING, _REAL, _BOOL };
	enum _fubs  { _LT, _GT, _AND, _OR, _OUT, _CONST, _VAR };

}


#endif