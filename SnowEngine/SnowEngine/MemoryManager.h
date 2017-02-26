#pragma once

#include <new>
#include <stack>

#define POOL_MAX_BYTES 268435456 // 256 MB

using namespace std;

template <class E>
class MemoryManager
{
private:

	template <class E>
	class MemoryPool
	{
		friend class MemoryManager<E>;
		size_t _actual_ptr = 0, obj_count;
		E* _pool_contents;
		MemoryPool() {
			obj_count = POOL_MAX_BYTES / sizeof(E);
			_pool_contents = (E*) malloc(obj_count * sizeof(E));
		}

		E* requestMemory() {
			if (_actual_ptr < obj_count) return &_pool_contents[_actual_ptr++];
			else return nullptr;
		}
	};

	stack<E*> _free_memory;
	MemoryPool<E>** _memory_pools;

	size_t _actual_pool = 0;
	size_t _max_pools;
public:
	MemoryManager(size_t pool_count = 20) :
		_max_pools(pool_count),
		_memory_pools(new MemoryPool<E>*[pool_count])
	{
		_memory_pools[_actual_pool] = new MemoryPool<E>();
	}
	E* requestMemory() {
		// If there's free memory in the stack (stack is not empty) we'll just give the top pointer
		E* ptr;
		if (!_free_memory.empty()) {
			ptr = _free_memory.top();
			_free_memory.pop();
			return ptr;
		}
		// Otherwise we'll have to give memory from the pools
	askForMemory:
		ptr = _memory_pools[_actual_pool]->requestMemory();
		if (ptr == nullptr) {
			if (_actual_pool < _max_pools) _actual_pool++;
			else return nullptr;
			_memory_pools[_actual_pool] = new MemoryPool<E>();
			goto askForMemory;
		}
		return ptr;
	}
	void freeMemory(E* ptr) {
		_free_memory.push(ptr);
	}
};