#pragma once

#include <bakatoolspch.h>
#include <initializer_list>
#include <string>

namespace Bk::Type {
	class DataStream 
	{
	public:
		DataStream() = default;
		DataStream(std::initializer_list<char> list)
		: payload(list) {}
		DataStream(std::vector<char> data)
		: payload(data) {}

		operator std::string() { return std::string(payload.data(), payload.size()); }

		int size() { return payload.size(); }

		void reverse() { std::reverse(payload.begin(), payload.end()); }

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