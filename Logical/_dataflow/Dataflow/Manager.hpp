/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: Dataflow
 * File: Manager.hpp
 * Author: k1008014
 * Created: July 13, 2020
 *******************************************************************/

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <bur/plctypes.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "NodeFunctions.hpp"
#include "generaldefines.h"

#define _MAX_NODES_NR 100

namespace dataflow
{


	//support for foreach
	void NodeExecution(INode *node)
	{
		node->Cyclic();
	}
	
	//support for foreach
	void NodeInit(INode *node)
	{
		node->Init();
	}

	class Manager
	{
		private:
		std::vector<INode *> nodes;

		public:

		/*Node by node _CYCLYC execution*/
		void CyclicExecution()
		{
			std::for_each(nodes.begin(), nodes.end(), NodeExecution);
		}
		
		/*Node by node _INIT execution */
		void InitExecution()
		{
			std::for_each(nodes.begin(), nodes.end(), NodeInit);
		}

		/*Selection of type of node*/
		static INode *SelectINode(int INodeNr)
		{
			switch (INodeNr)
			{
				case dataflow::_LT :
					return new LT();
					break;
				case dataflow::_GT :
					return new GT();
					break;
				default:
					break;
			}
		}
	
		/*Add a new node to the manager*/
		INode **AddNode(INode *node)
		{
			try
			{
				this->nodes.push_back(node);
				return &node;
			}
			catch (std::exception ex)
			{
#ifdef _DATAFLOW_LOGGER
				/*TODO -> add logger*/
#endif
			}
		}
		
		INode* GetLastNode()
		{
			return this->nodes.back();
		}
	
		/*Clear nodes vector*/
		void ClearManager()
		{
			try
			{
				this->nodes.clear();
			}
			catch (std::exception ex)
			{
				/*TODO -> add logger*/
			}	
		}
	};
	
}

#endif