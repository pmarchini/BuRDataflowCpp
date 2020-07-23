/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: Dataflow
 * File: INode.hpp
 * Author: k1008014
 * Created: July 13, 2020
 *******************************************************************/

#ifndef NODE_HPP
#define NODE_HPP

#include <bur/plctypes.h>
#include <vector>

#include "Input_channel.hpp"
#include "Output_channel.hpp"

namespace dataflow
{
	class NodeException: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Node exception happened";
		}
	} NodeEx;
		
	class INode
	{
		public:
			

		plcbit error;
			
		/// <summary>Add an input to the node</summary>
		/// <param name="type">Specifies the type of the input</param>  
		/// <returns>void</returns>  
		void AddInput(int type)
		{
			try
			{	
				this->inputs.push_back(new Input_channel(type));
			}
			catch(std::bad_alloc& e)
			{
				this->error = 1;
			}
		}
			
		/// <summary>Set pointer to an input linking the node to an ouput or val</summary>
		/// <param name="ptr">void* to another node or value, user must check types</param>  
		/// <param name="inputNr">Input number to set, if out of bound throw NodeEx</param>  
		/// <returns>void</returns>  
		void SetInput(void* ptr, int inputNr)
		{
			if(((this->inputs.size() + 1) < inputNr) || inputNr < 0)
			{
				throw NodeEx;	
			}
			this->inputs[inputNr]->setPointer(ptr);
		}
			
		/// <summary>Set pointer to an output linking the node to an input or val</summary>
		/// <param name="ptr">void* to another node or value, user must check types</param>  
		/// <param name="inputNr">Output number to set, if out of bound throw NodeEx</param>  
		/// <returns>void</returns>  
		void SetOutput(void* ptr, int outPutNr)
		{
			if(((this->outputs.size() + 1) < outPutNr) || outPutNr < 0)
			{
				this->error = 1;
				throw NodeEx;	
			}
			this->outputs[outPutNr]->setPointer((void*)ptr);
		}
			
		/// <summary>Add an output to the node</summary>
		/// <param name="type">Specifies the type of the output</param>  
		/// <returns>void</returns>  
		void AddOutput(int type)
		{
			try
			{
				this->outputs.push_back(new Output_channel(type));
			}
			catch(std::bad_alloc& e)
			{
				this->error = 1;
			}
		}
	
		/// <summary>Get ouput pointer</summary>
		/// <param name="type">Specifies the output number</param>  
		/// <returns>void*</returns>  
		void* GetOutputPtr(int outPutNr)
		{
			if(((this->outputs.size() + 1) < outPutNr) || outPutNr < 0)
			{
				this->error = 1;
				throw NodeEx;	
			}
			else
			{
				return this->outputs[outPutNr]->getPointer();
			}
		}
			
		/// <summary>Virtual method, Init node</summary>
		/// <returns>void</returns>  
		virtual void Init() = 0;
		/// <summary>Virtual method, Cyclic executon of the node[main logic]</summary>
		/// <returns>void</returns>  
		virtual void Cyclic() = 0;
		/// <summary>Virtual method, Exit function on decostruction</summary>
		/// <returns>void</returns>  
		virtual void Exit() = 0;
			
		protected:
		/*Vectors of I/O*/
		std::vector<Input_channel*> inputs;
		std::vector<Output_channel*> outputs;
		
	};
}




#endif