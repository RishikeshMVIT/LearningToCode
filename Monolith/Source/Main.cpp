
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



int main()
{
	return 0;
}

