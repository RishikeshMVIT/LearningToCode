
#define NULL = 0;

typedef UINT8;
typedef UINT16;
typedef UINT32;
typedef UINT64;
typedef INT8;
typedef INT16;
typedef INT32;
typedef INT64;
typedef F8;
typedef F16;
typedef F32;
typedef F64;

template <typename T>
class LinearData
{
public:
	LinearData() : array(nullptr), capacity(0), size(0) {}
	~LinearData()
	{
		delete[] array;
	}

	virtual void Push(const T& value) = 0;
	virtual T Pop() = 0;

private:
	void Resize(size_t newCapacity)
	{
		T* newArray = new T[newCapacity];
		for (size_t i = 0; i < size; ++i)
		{
			newArray[i] = array[i];
		}

		delete[] array;
		array = newArray;
		capacity = newCapacity;
	}

private:
	T* array;
	size_t size;
	size_t capacity;
};

template<typename T>
class DynamicArray
{
public:
	DynamicArray() : array(nullptr), capacity(0), size(0) {}
	~DynamicArray()
	{
		delete[] array;
	}

	void Push(const T& value)
	{
		if (size >= capacity)
		{
			size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
			Resize(newCapacity);
		}
		array[size++] = value;
	}

	void Pop(int index = 0)
	{
		if (index <= size)
		{

		}

		return;
	}

	T& operator[](size_t index)
	{
		if (index >= size)
		{
			
		}

		return array[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= size)
		{

		}

		return array[index];
	}

private:
	void Resize(size_t newCapacity)
	{
		T* newArray = new T[newCapacity];
		for (size_t i = 0; i < size; ++i)
		{
			newArray[i] = array[i];
		}

		delete[] array;
		array = newArray;
		capacity = newCapacity;
	}

private:
	//Header
	T* array;
	size_t capacity;
	size_t size;
};

template <typename T>
class LinkedList
{

};

template <typename T, int n>
class Stack
{
public:
	Stack() : array(nullptr), capacity(0), size(0) {}
	~Stack()
	{
		delete[] array;
	}

	void Push()
	{
	}

	T Pop()
	{

	}

	T Peek()
	{

	}

	bool IsEmpty()
	{
		return (size == 0) ? true : false;
	}

	bool IsFull()
	{
		return (size >= capacity) ? true : false;
	}

private:
	T* array;
	size_t capacity;
	size_t size;
};

template<typename T>
class Queue
{
public:

private:

};

template <typename T>
class Tree
{

};

template <typename T>
class Trie
{

};

template <typename T>
class Graph
{

};

int main()
{
	return 0;
}

