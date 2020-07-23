/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: Dataflow
 * File: NodeFunctions.hpp
 * Author: k1008014
 * Created: July 13, 2020
 *******************************************************************/
#ifndef NODE_GENERAL_FUNCTIONS_HPP
#define NODE_GENERAL_FUNCTIONS_HPP

#include <bur/plctypes.h>
#include "INode.hpp"

namespace dataflow
{

	/*Less then*/
	class LT: public INode
	{
		private:
	
		bool outVal;
	
		public:
	
		/// <summary>Init node, set standard structure</summary>
		/// <returns>void</returns> 
		void Init()
		{
			//Input 1
			this->AddInput(dataflow::_DOUBLE);
			//Input 2
			this->AddInput(dataflow::_DOUBLE);
			//Output 1
			this->AddOutput(dataflow::_BOOL);
		}
		/// <summary>Cyclic executon of the node[main logic]</summary>
		/// <returns>void</returns>  
		void Cyclic()
		{
			this->outVal = (double*)this->inputs[0]->getVal() < (double*)this->inputs[1]->getVal();
			this->SetOutput((void*)outVal,0);
		}
		/// <summary>Exit function on decostruction</summary>
		/// <returns>void</returns>  
		void Exit()
		{
			return;
		}

	};
	/*Greater then*/
	class GT : public INode
	{
		private:
	
		bool outVal;
	
		public:
	
		/// <summary>Init node, set standard structure</summary>
		/// <returns>void</returns> 
		void Init()
		{
			//Input 1
			this->AddInput(dataflow::_DOUBLE);
			//Input 2
			this->AddInput(dataflow::_DOUBLE);
			//Output 1
			this->AddOutput(dataflow::_BOOL);
		}
		/// <summary>Cyclic executon of the node[main logic]</summary>
		/// <returns>void</returns>  
		void Cyclic()
		{
			this->outVal = (double*)this->inputs[0]->getVal() > (double*)this->inputs[1]->getVal();
			this->SetOutput((void*)outVal,0);
		}
		/// <summary>Exit function on decostruction</summary>
		/// <returns>void</returns>  
		void Exit()
		{
			return;
		}

	};


	class VAR : public INode
	{
		public:
		/// <summary>Init node, set standard structure</summary>
		/// <returns>void</returns> 
		void Init()
		{
			/*Input 1*/
			this->AddInput(dataflow::_DOUBLE);
			/*Output 1*/
			this->AddOutput(dataflow::_DOUBLE);
			/*Set bridge input-output*/
			this->SetOutput((double*)this->inputs[0]->getVal(),0);
		
		}
	
		void Cyclic()
		{
			return;
		}
		
		void Exit()
		{
			return;
		}
	};
	
	#define _A_INPUT 0
	#define _B_INPUT 1
	
	#define _A_OUTPUT 0
	#define _B_OUTPUT 1
	
	//This class in only a test and has empty void methods
	class NOT : public INode
	{
		
		private:
		
		plcbit outVal;
		
		public:
		
		/// <summary>Init node, set standard structure</summary>
		/// <returns>void</returns> 		
		void Init()
		{
			/*Input 1*/
			this->AddInput(dataflow::_BOOL);
			/*Output 1*/
			this->AddOutput(dataflow::_BOOL);
		}
	
		void Cyclic()
		{
			if(!this->error)
			{
				/*Static cast of input void pointer*/
				auto tmp_in = static_cast<plcbit*>(this->inputs[_A_INPUT]->getVal());
				/*Static cast of output void pointer*/
				auto tmp_out = static_cast<plcbit*>(this->GetOutputPtr(_A_OUTPUT));
				if(*tmp_in)
				{
					*tmp_out = false;
				}
				else
				{
					*tmp_out = true;
				}
			}	
		}
		
		void Exit()
		{
			return;
		}
	};
}

#endif
