#pragma once
#include "MemoryManager.h"

template <class E>
struct Node {
	Node(E element, Node *next) {
		this->element = element;
		this->next = next;
	}
	E element;
	Node *next;
};

template <class E>
struct LinkedIterator {
	Node<E>* actual_node;
	bool hasNext() {
		return actual_node != nullptr;
	}
	E next() {
		Node<E>* actual_node_aux = actual_node;
		actual_node = actual_node->next;
		return actual_node_aux->element;
	}
};

template <class E>
class LinkedList
{
private:
	Node<E> *_first_node = nullptr, *_last_node = nullptr;
	MemoryManager<Node<E>> memory;
public:
	LinkedList() {}

	LinkedIterator<E> linked_iterator() {
		LinkedIterator<E> lit;
		lit.actual_node = _first_node;
		return lit;
	}

	void add(E element) {
		Node<E> *node = new(memory.requestMemory()) Node<E>(element, nullptr);
		if (isEmpty()) {
			_last_node = node;
		}
		node->next = _first_node;
		_first_node = node;
	}

	void remove(E element) {
		Node<E>* aux = _first_node, *paux = nullptr;
		while (aux != nullptr) {
			if (aux->element == element) {
				if (aux == _first_node && aux == _last_node) {
					_first_node = nullptr;
					_last_node = nullptr;
				}
				else {
					if (aux == _first_node)
						_first_node = aux->next;
					if (aux == _last_node)
						_last_node = paux;
				}
				memory->freeMemory(aux);
				return;
			}
			else {
				paux = aux;
				aux = aux->next;
			}
		}
	}

	void empty() {
		Node<E>* aux = _first_node, *aux2;
		while (aux != nullptr) {
			aux2 = aux->next;
			memory.freeMemory(aux);
			aux = aux2;
		}
		_first_node = nullptr;
		_last_node = nullptr;
	}

	bool isEmpty() { return _first_node == nullptr; }
	~LinkedList() {
		Node<E> *aux = _first_node, *aux2;
		while (aux != nullptr) {
			aux2 = aux->next;
			delete aux->element;
			aux = aux2;
		}
	}
};

