/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: Dataflow
 * File: Input_channel.hpp
 * Author: k1008014
 * Created: July 13, 2020
 *******************************************************************/

/*Include guards*/
#ifndef INPUT_CHANNEL_HPP
#define INPUT_CHANNEL_HPP

#include <bur/plctypes.h>
#include "generaldefines.h"

/*Template class for every type in input*/
class Input_channel {
	
	void* value;
	int Type;
	
	public:
	
	Input_channel(int type)
	{
		this->Type = type;
		/*Alloc internal memory for the value*/
		CastDynamicType();
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
		return &this->value;
	}
	
	void setPointer(void* ptr)
	{
		this->value = (void*)ptr;
	}
	
	
	//Type must be defined at alloc time
	//Cast the input void* to type*
	//TODO -> erase this, has no sense
	void CastDynamicType()
	{		
		switch (this->Type)
		{
			case dataflow::_INT:
				static_cast<int*>(value);
				break;
			case dataflow::_FLOAT:
				static_cast<float*>(value);
				break;
			case dataflow::_CHAR:
				static_cast<char*>(value);
				break;
			case dataflow::_DOUBLE:
				static_cast<double*>(value);
				break;	
			case dataflow::_BOOL:
				static_cast<plcbit*>(value);
				break;
			default:
				break;
		}
	}
};

#endif