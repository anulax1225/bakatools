#pragma once

#include <bakatoolspch.h>

namespace Bk {
	class DataStream 
	{
	public:
		DataStream() = default;
		DataStream(std::vector<char> data)
		: payload(data) {}

		int size() { return payload.size(); }

		template <typename T>
		void push(const T& data)
		{
			static_assert(std::is_standard_layout<T>::value, "Data is too complex to be pushed into vector");
			size_t i = payload.size();
			payload.resize(i + sizeof(T));
			std::memcpy(payload.data() + i, &data, sizeof(T));
		}

		template <typename T>
		void push(const T* data, int size)
		{
			for(int i = 0; i < size; i++) push<T>(data[i]);	
		}

		template <typename T>
		T pull()
		{
			static_assert(std::is_standard_layout<T>::value, "Data is too complex to be pulled from vector");
			T data;
			size_t i = payload.size() - sizeof(T);
			std::memcpy(&data, payload.data() + i, sizeof(T));
			payload.resize(i);
			return data;
		}

		template <typename T>
		std::unique_ptr<T[]> pull(int size)
		{
			std::unique_ptr<T[]> data(new T[size]);
			for(int i = size - 1; i >= 0; i--) data[i] = pull<T>();
			return data;
		}

		bool append_data(std::vector<char> data)
		{
			if (!data.size()) return false;
			size_t i = payload.size();
			payload.resize(i + data.size());
			std::memcpy(payload.data() + i, data.data(), sizeof(char) * data.size());
			return true;
		}
	
		std::vector<char> payload;
	};
}