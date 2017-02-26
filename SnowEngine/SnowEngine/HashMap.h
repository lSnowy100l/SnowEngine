#pragma once

template <class K>
using HashFunction = size_t (*)(K);

template <class K, class E>
class HashMap
{
private:
	HashFunction<K> _hash;
	vector<pair<K, E>>* _contents;
public:
	HashMap(HashFunction<K> hashFun, size_t size) :
		_hash(hashFun),
		_contents(new vector<pair<K, E>>[size])
	{
	}
	void put(K key, E element)
	{
		_contents[_hash(key)].push_back({key, element});
	}
	E get(K key)
	{
		vector<pair<K, E>> list = _contents[_hash(key)];
		for (pair<K, E> pair : list) {
			if (pair.first == key)
				return pair.second;
		}
		return nullptr;
	}
	~HashMap()
	{
		delete[] _contents;
	}
};
