#include <vector>

template <typename T>
class BinaryHeap {
private:
	std::vector<T> a;
	void siftDown(size_t ind);
	void siftUp(size_t ind);
public:
	T extractMin();
	void insert(T key);
	size_t size();
};

template<typename T>
inline void BinaryHeap<T>::siftDown(size_t ind)
{
	size_t i = ind;
	while (2 * i + 1 < a.size())
	{
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t j = left;
		if ((right < a.size()) && (a[right] < a[left]))
		{
			j = right;
		}
		if (a[i] <= a[j])
		{
			break;
		}
		std::swap(a[i], a[j]);
		i = j;
	}
}

template<typename T>
inline void BinaryHeap<T>::siftUp(size_t ind)
{
	size_t i = ind;
	while (i > 0 && a[i] < a[(i - 1) / 2]) {
		std::swap(a[i], a[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

template<typename T>
inline T BinaryHeap<T>::extractMin()
{
	T min = a[0];
	a[0] = a[a.size() - 1];
	a.pop_back();
	siftDown(0);
	return min;
}

template<typename T>
inline void BinaryHeap<T>::insert(T key)
{
	a.push_back(key);
	siftUp(a.size() - 1);
}

template<typename T>
inline size_t BinaryHeap<T>::size()
{
	return a.size();
}
