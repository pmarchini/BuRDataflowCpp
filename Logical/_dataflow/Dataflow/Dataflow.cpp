/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: Dataflow
 * File: Dataflow.cpp
 * Author: k1008014
 * Created: July 13, 2020
 ********************************************************************
 * Implementation of program Dataflow
 ********************************************************************/

#include <bur/plctypes.h>
#include "plcdeclarations.h"
#include "generaldefines.h"
#include "Manager.hpp"

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

unsigned long bur_heap_size=0xFFFFF;

dataflow::Manager* t_man; 
extern DataFlow test;
dataflow::INode* ptr;
bool _trigflag;


void _INIT DataflowInit(void)
{
	/*Istantiate Manager*/
	t_man = new dataflow::Manager();
	/*Add a _TestFun function*/
	t_man->AddNode(new dataflow::NOT());
	ptr = t_man->GetLastNode();
	/*Structure created -> init nodes*/
	t_man->InitExecution();
	/*Set node input*/
	ptr->SetInput(&test.I_In,0);
	/*Set node ouput*/
	ptr->SetOutput(&test.O_Out,0);
	
}


void _CYCLIC DataflowCyclic(void)
{
	/*Manager cyclic*/
	if(test.I_In && (_trigflag != test.I_In))
	{
		t_man->ClearManager();
		t_man->AddNode(new dataflow::NOT());
		ptr = t_man->GetLastNode();
		t_man->InitExecution();
		/*Set node input*/
		ptr->SetInput(&test.I_In,0);
		/*Set node ouput*/
		ptr->SetOutput(&test.O_Out,0);
	}
	/*R_TRIG*/
	_trigflag = test.I_In;
	
	t_man->CyclicExecution(); 
	test.O_Out = test.O_Out; 
}
