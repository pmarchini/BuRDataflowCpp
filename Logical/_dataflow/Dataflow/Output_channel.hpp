/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: Dataflow
 * File: Output_channel.hpp
 * Author: k1008014
 * Created: July 13, 2020
 *******************************************************************/

#ifndef OUTPUT_CHANNEL_HPP
#define OUTPUT_CHANNEL_HPP

#include <bur/plctypes.h>
#include "generaldefines.h"
#include <cstdlib>



/*Template class for every type in input*/
class Output_channel {
	
	void* value;
	int Type;
	
	public:
	
	Output_channel(int type)
	{
		this->Type = type;
		/*Alloc internal memory for the value*/
		AllocDynamicOutput();
	} 
	//Return type name of the input demangled
	//[typeid return from type_info is compiler dependant and needs to be demangled]
	int getType() 
	{
		/*std::type_info  &ti = typeid(this->value);
		return abi::__cxa_demangle(ti.name(), 0, 0, 0);*/
		return this->Type;
	}
	//Return value
	void* getVal()
	{
		return value;	
	}
	//Return pointer to value
	void* getPointer()
	{
		return this->value;
	}
	
	void setPointer(void* ptr)
	{
		this->value = ptr;
	}
	
	//Type must be defined at alloc time
	//alloc memory in order to get space into memory for the type
	//and then cast the void* to type*
	void AllocDynamicOutput()
	{
		switch (this->Type)
		{
			case dataflow::_INT:	
				//value = malloc(sizeof(int));
				static_cast<int*>(value);
				break;
			case dataflow::_FLOAT:
				//value = malloc(sizeof(float));
				static_cast<float*>(value);
				break;
			case dataflow::_CHAR:
				value = malloc(sizeof(char));
				static_cast<char*>(value);
				break;
			case dataflow::_DOUBLE:
				//value = malloc(sizeof(double));
				static_cast<double*>(value);
				break;	
			case dataflow::_BOOL:
				//value = malloc(sizeof(plcbit));
				static_cast<plcbit*>(value);
				break;
			default:
				break;
		}
	}
};

#endif