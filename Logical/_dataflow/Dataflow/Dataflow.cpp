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

#ifdef _SG4 /*IF B&R system*/ //TODO -> Add where needed
#include <bur/plctypes.h>
#include "plcdeclarations.h"
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif
#endif

#include "generaldefines.h"
#include "Manager.hpp"

unsigned long bur_heap_size=0xFFFFF;

dataflow::Manager* t_man; 
extern DataFlow test;
dataflow::INode* ptr;
bool _trigflag;

#define _TEST_NODE_A 0
#define _TEST_NODE_B 1

void ManagerSetup()
{
	/*Prepare manager*/
	t_man->ClearManager();
	t_man->AddNode(new dataflow::NOT()); // _TEST_NODE_A
	t_man->AddNode(new dataflow::NOT()); // _TEST_NODE_B
	t_man->InitExecution();
	/*Set nodes links*/
	/***********************************************/
	/***********************************************/
//_TEST_NODE_A
	ptr = t_man->GetNodePtr(_TEST_NODE_A);
	ptr->SetInput(&test.I_In,0);
	//ptr->SetOutput(&test.O_Out,0); //Forcing output to a different location
	/***********************************************/
	/***********************************************/
//_TEST_NODE_B
	ptr = t_man->GetNodePtr(_TEST_NODE_B);
	/*Output is created with node init
	 *when an output channel is created its memory is allocated for the type declared
	 */
	ptr->SetInput(t_man->GetNodePtr(_TEST_NODE_A)->GetOutputPtr(0),0); 
	ptr->SetOutput(&test.O_Out,0); //Forcing output to a different location
}

void _INIT DataflowInit(void)
{
	//ManagerSetup();
}


void _CYCLIC DataflowCyclic(void)
{
	/*Manager cyclic*/
	if(test.I_In && (_trigflag != test.I_In))
	{
		ManagerSetup();
	}
	/*R_TRIG*/
	_trigflag = test.I_In;
	
	/*Adds control to execution, only for test purposes*/
	if(test.I_Enable)
	{
		t_man->CyclicExecution(); 
	}
	test.O_Out = test.O_Out; 
}
