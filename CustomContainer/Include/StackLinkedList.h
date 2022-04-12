#pragma once

template <class T>
class StackLinkedList
{
public:
	struct Node
	{
		T data;
		Node* next;
		Node* prev;
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	
	StackLinkedList() = default;
	void push(Node* InNode)
	{
		InNode->next = nullptr;
		if (head == nullptr)
		{	
			head = InNode;
			head->prev = nullptr;
			tail = head;
		}
		else
		{
			tail->next = InNode;
			tail->next->prev = tail;
			tail = tail->next;
		}
	}
	Node* pop()
	{
		Node* top = head;
		head = head->next;
		return top;
	}
private:
	StackLinkedList(StackLinkedList& OtherStackLinkedList) = delete;
};