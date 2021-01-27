#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

//TODO it's kek priority queue

template<typename T>
class PriorityQueue
{
public:
	void Push(T value);
	T Pop();
	size_t GetSize() { return data_.size(); };

private:
	std::vector<T> data_;
};

template<typename T>
void PriorityQueue<T>::Push(T value)
{
	data_.push_back(value);
}

template<typename T>
T PriorityQueue<T>::Pop()
{
	size_t curIndex = 0;
	
	for (size_t i = 1; i < data_.size(); i++)
	{
		if (data_[i] < data_[curIndex])
			curIndex = i;
	}
	
	T value = data_[curIndex];
	data_.erase(data_.begin() + curIndex);
	
	return value;
}

#endif
