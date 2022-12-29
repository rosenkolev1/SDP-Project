#pragma once

#include <iostream>
#include <vector>
#include <map>

template <typename T>
struct Node
{
	T key;

	Node<T>* next;
	Node<T>* prev;

	Node<T>* spec;

	Node(T key) 
	{
		this->key = key;
		this->next = nullptr;
		this->prev = nullptr;
		this->spec = nullptr;
	}
};

template <typename T>
class SkipList 
{
private:
	Node<T>* head;

	void copy(const SkipList& other)
	{
		if (other.head == nullptr)
		{
			this->head = nullptr;
			return;
		}

		Node<T>* curOtherNode = other.head;

		Node<T>* curNode = nullptr;

		std::map<Node<T>*, std::vector<Node<T>*>> awaitingSpecs;
		//<copied node, new copy node>
		std::map<Node<T>*, Node<T>*> correspondingNodes;

		int curOtherNodeIndex = 0;
		while (curOtherNode)
		{
			Node<T>* newNode = new Node<T>(curOtherNode->key);
			if (this->head == nullptr)
			{
				this->head = newNode;
				curNode = this->head;
				curNode->next = curNode;
			}
			else
			{
				curNode->next = newNode;
				newNode->prev = curNode;
			}

			correspondingNodes[curOtherNode] = newNode;

			//Set the new node's spec
			if (curOtherNode->spec)
			{
				if (correspondingNodes.find(curOtherNode->spec) != correspondingNodes.end())
				{
					newNode->spec = correspondingNodes[curOtherNode->spec];
				}
				else
				{
					if (awaitingSpecs.find(curOtherNode->spec) != awaitingSpecs.end())
					{
						awaitingSpecs[curOtherNode->spec].push_back(newNode);
					}
					else
					{
						awaitingSpecs[curOtherNode->spec] = { newNode };
					}
				}			
			}

			//Set old nodes' specs
			if (awaitingSpecs.find(curOtherNode) != awaitingSpecs.end())
			{
				std::vector<Node<T>*> oldNodes = awaitingSpecs[curOtherNode];

				for (Node<T>* oldNode : oldNodes)
				{
					oldNode->spec = newNode;
				}
			}

			curNode = curNode->next;
			curOtherNode = curOtherNode->next;
			curOtherNodeIndex++;
		}
	}

	void deallocate()
	{
		Node<T>* curNode = this->head;

		while (curNode)
		{
			Node<T>* temp = curNode;
			curNode = curNode->next;

			delete temp;
		}
	}

public:

	SkipList(Node<T>* head)
	{
		this->head = head;
	}

	SkipList()
	{
		this->head = nullptr;
	}

	SkipList(const SkipList& other)
	{
		this->copy(other);
	}

	SkipList& operator=(const SkipList& other)
	{
		this->deallocate();
		this->copy(other);
	}

	~SkipList()
	{
		this->deallocate();
	}

	const Node<T>* getHead() const
	{
		return this->head;
	}

	const int getSize() const
	{
		int size = 0;
		Node<T>* curNode = this->head;
		while (curNode)
		{
			size++;
			curNode = curNode->next;
		}

		return size;
	}

	std::string toString() const
	{
		std::string NEWLINE = "\n";

		std::string result = "";
		result += "--------------------------------------------------------------------------------------------------------" + NEWLINE;
		result += "This SkipList: ";

		Node<T>* curNode = this->head;

		while (curNode)
		{
			result += curNode->key + (curNode->next != nullptr ? " --> " : "");
			curNode = curNode->next;
		}
		result += NEWLINE;

		curNode = this->head;
		result += "Special connections:" + NEWLINE;
		while (curNode)
		{
			if (curNode->spec)
			{
				result += curNode->key + " --> " + curNode->spec->key + NEWLINE;
			}
			curNode = curNode->next;
		}
		result += "--------------------------------------------------------------------------------------------------------" + NEWLINE;

		return result;
	}
};

