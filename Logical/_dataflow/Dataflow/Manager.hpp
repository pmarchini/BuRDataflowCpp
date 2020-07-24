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


#ifdef _SG4 /*B&R system*/

#define _NODES_LIMITER 
#define _MAX_NODES_NR 100

#endif

namespace dataflow
{

	class ManagerException: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Manager exception";
		}
	} ManagerEx;

#ifdef _NODES_LIMITER

	class ManagerNodesNumberOutOfBounds: public std::exception
	{
		virtual const char* what() const throw()
		{
		return "Manager exception : too many nodes";
	}
		} ManagerOutOfBoundEx;

#endif

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
	
		bool ErrorState;
		
		/// <summary>Get Node pointer</summary>
		/// <param name="nodeNr">Specifies the node number</param>  
		/// <returns>INode*</returns>  
		INode* GetNodePtr(int nodeNr)
		{
			if(((this->nodes.size() + 1) < nodeNr) || nodeNr < 0)
			{
				this->ErrorState = true;
				throw ManagerEx;	
			}
			else
			{
				return this->nodes[nodeNr];
			}
		}
		
		/// <summary>Remove Node from manager returning a pointer of the element</summary>
		/// <param name="nodeNr">Specifies the node number</param>  
		/// <returns>INode*</returns>  
		INode*  RemoveNode(int nodeNr)
		{
			if(((this->nodes.size() + 1) < nodeNr) || nodeNr < 0)
			{
				this->ErrorState = true;
				throw ManagerEx;	
			}
			else
			{
				auto tmp = this->nodes[nodeNr];
				this->nodes.erase(this->nodes.begin() + nodeNr);
			}
		}

		/// <summary>Exec Cyclic of every node contained into manager</summary>
		/// <returns>void</returns>  
		void CyclicExecution()
		{
			std::for_each(nodes.begin(), nodes.end(), NodeExecution);
		}
		
		/// <summary>Exec Init of every node contained into manager</summary>
		/// <returns>void</returns>  
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
	
		/// <summary>Get Node pointer</summary>
		/// <param name="nodeNr">Specifies the node number</param>  
		/// <returns>INode*</returns>  
		INode **AddNode(INode *node)
		{
/*Max amount of nodes, prevent memory errors*/
#ifdef _NODES_LIMITER
			if(this->nodes.size() > _MAX_NODES_NR)
			{
				this->ErrorState = true;
				throw ManagerOutOfBoundEx;
			}
#endif
			try
			{
				this->nodes.push_back(node);
				return &node;
			}
			catch (std::exception ex)
			{
				this->ErrorState = true;
#ifdef _DATAFLOW_LOGGER
				/*TODO -> add logger*/
#endif
			}
		}
		
		/// <summary>Returns last node added to the manager</summary>
		/// <returns>INode*</returns>  
		INode* GetLastNode()
		{
			return this->nodes.back();
		}
	
		/// <summary>Clear Manager memory</summary>
		/// <returns>void</returns>  
		void ClearManager()
		{
			try
			{
				this->nodes.clear();
			}
			catch (std::exception ex)
			{
				this->ErrorState = true;
#ifdef _DATAFLOW_LOGGER
				/*TODO -> add logger*/
#endif
			}	
		}
	};
	
}

#endif