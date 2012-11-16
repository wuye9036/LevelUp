#ifndef PTRLIST_H_INCLUDED
#define PTRLIST_H_INCLUDED

#include <stdlib.h>

class DeleteContent{
public:
	bool _is;
	explicit DeleteContent(bool is):_is(is){}
	bool operator == (DeleteContent dc){return _is == dc._is;}
	bool IsDeleteContent()
	{
		return _is;
	}

	static const DeleteContent Yes;
	static const DeleteContent No;
};

template <class T> struct PtrList;

template <class T>
struct PtrListNode
{
	PtrList<T>*		owner;
	PtrListNode<T>*	prev;
	PtrListNode<T>*	next;
	T*				content;
};

template <class T>
struct PtrList
{
	PtrListNode<T>* header;
	PtrListNode<T>* tail;
	PtrListNode<T>* null;

	static PtrList* NewList()
	{
		PtrList* retList = new PtrList<T>;
		retList->header = NULL;
		retList->tail = NULL;
		retList->null = new PtrListNode<T>;
		retList->null->owner = retList;
		return retList;
	}

	static void AddToHead(PtrList<T>* lst, T* item)
	{
		PtrListNode<T>* oldHeader = lst->header;
		lst->header = new PtrListNode<T>;
		lst->header->owner = lst;
		lst->header->prev = NULL;
		lst->header->next = oldHeader;
		lst->header->content = item;

		if (lst->tail == NULL){
			lst->tail = lst->header;
		}
	}

	static void AddToTail(PtrList<T>* lst, T* item)
	{
		PtrListNode<T>* oldTail = lst->tail;
		lst->tail = new PtrListNode<T>;
		lst->header->owner = lst;
		lst->tail->prev = oldTail;
		lst->tail->next = NULL;
		lst->tail->content = item;

		if (lst->header == NULL){
			lst->header = lst->tail;
		}
	}

	static void DeleteHeader(PtrList<T>* lst, DeleteContent dc)
	{
		if (lst->header == NULL) return;
		PtrListNode<T>* newHeader = lst->header->next;
		if(dc.IsDeleteContent)	{
			delete lst->header->content;
		}
		delete lst->header;
		if(newHeader == NULL){
			lst->tail = NULL;
		}
		lst->header = newHeader;
	}

	static void DeleteTail(PtrList<T>* lst, DeleteContent dc)
	{
		if (lst->tail == NULL) return;
		PtrListNode<T>* newTail = lst->tail->next;
		if(dc.IsDeleteContent)	{
			delete lst->tail->content;
		}
		delete lst->tail;
		if(newTail == NULL){
			lst->header = NULL;
		}
		lst->tail = newTail;
	}

	// delete node and return next node.
	static PtrListNode<T>* DeleteNode(PtrListNode<T>* lstNode, DeleteContent dc)
	{
		if(lstNode == NULL || lstNode == lstNode->owner->null)
		{
			return NULL;
		}
		if(lstNode == lstNode->owner->header)
		{
			DeleteHeader(lstNode->owner, dc);
			return lstNode->header;
		}
		if(lstNode == lstNode->owner->tail)
		{
			DeleteTail(lstNode->owner, dc);
			return NULL;
		}
		PtrListNode<T>* prevNode = lstNode->prev;
		PtrListNode<T>* nextNode = lstNode->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		if(dc.IsDeleteContent)
		{
			delete lstNode->content;
		}
		delete lstNode;
	}

	//insert after current node.
	//if pos is lst->null it means addtoheader.
	static void Insert(PtrListNode<T>* lstNode, T* item)
	{
		if (lstNode == lstNode->owner->null)
		{
			AddToHead(lstNode->owner, item);
			return;
		}
		if (lstNode == lstNode->owner->tail)
		{
			AddToTail(lstNode->owner, item);
			return;
		}

		PtrListNode<T>* newNode = new PtrListNode<T>;
		newNode->owner = lstNode->owner;
		newNode->prev = lstNode;
		newNode->next = lstNode->next;
		lstNode->next = newNode;
	}

	static void Clear(PtrList<T>* lst, DeleteContent dc)
	{
		PtrListNode<T>* ptr = lst->header;
		while(ptr != NULL)
		{
			PtrListNode<T>* newptr = ptr->next;
			delete ptr;
			if (dc.IsDeleteContent) delete ptr->content;
			ptr = newptr;
		}
	}

	static void Delete(PtrList<T>* lst, DeleteContent dc)
	{
		PtrList<T>::Clear(lst, dc);
		delete lst->null;
		delete lst;
	}
};



#endif // PTRLIST_H_INCLUDED
