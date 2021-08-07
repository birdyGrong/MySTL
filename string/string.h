#pragma once
#include<algorithm>
#include<assert.h>
#include<string.h>


namespace stringstl
{
	class string
	{
	public:
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		typedef const char* const_iterator;
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}


		//string(const string& s) :_str(new char[strlen(s._str) + 1])
		//{
		//	//深拷贝，让_str指向一片与s._str相同大小的空间
		//	strcpy(_str, s._str);
		//}

		/*string(const char* str = "") : _size(strlen(str)), _capacity(_size), _str(new char[_capacity + 1])
		{
			strcpy(_str, str);
		}*/
		
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];

			strcpy(_str, str);
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}

		const char* c_str() const
		{
			return _str;
		}

		//string& operator=(const string& s)
		//{
		//	if (this != &s)
		//	{
		//		delete[] _str;
		//		_str = new char[strlen(s._str) + 1];
		//		strcpy(_str, s._str);
		//	}
		//	//*this 此时还没有析构，因此返回引用可以提高效率
		//	//*this 此时还没有析构，因此返回引用可以提高效率
		//	return *this;
		//}

		void swap(string& s)
		{
			std::swap(_str,s._str);
			std::swap(_size,s._size);
			std::swap(_capacity,s._capacity);
		}

		string(const string& s):_str(nullptr),_size(0),_capacity(0)
		{
			//如果不将_str置空，将会是随机值，tmp(_str)析构时会报错
			//先调用普通构造函数构造一个临时变量tmp，tmp内的_str指向一片与s._str大小和数据都相同的空间
			string tmp(s._str);
			//交换后，_str指向一片与s._str大小和数据都相同的空间，即实现了string类拷贝构造时的深拷贝
			swap(tmp);
		}

		string& operator=(string s)
		{
			//传参过程中s先调用拷贝构造复制了实参，再将s._str和_str交换
			//此时不能传引用，因为要改变s的值
			swap(s);
			return *this;
		}
		//_str[i]能改变，因此用的char&
		char& operator[](size_t i)
		{
			assert(i < _size);
			return _str[i];
		}
		//_str[i]不能改变，因此用的const char&
		const char& operator[](size_t i) const
		{
			assert(i < _size);
			return _str[i];
		}

		size_t size() const //使得const对象可以调用
		{
			return _size;
		}

		size_t capacity() const //使得const对象可以调用
		{
			return _capacity;
		}

		//增删
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0? 4:_capacity * 2);
			}
			_str[_size++] = ch;
		}
		void append(const char* str)
		{
			if (_size + strlen(str) > _capacity)
			{
				reserve(_size + strlen(str));
			}
			strcpy(_str + _size, str);
			_size += strlen(str);
		}

		//开空间，扩展_capcity,此处设计的为只扩容不缩容
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp,_str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		//改变_size，同时初始化
		void resize(size_t n, char val = '\0')
		{
			if (n < _size)
			{
				_size = n;
				_str[n] = '\0';
			}
			else 
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = val;
				}
				_str[n] = '\0';
				_size = n;
			}
		}
		//+=运算
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size && pos >= 0);
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			size_t end = _size;
			//从\0往后挪，否则最后要补上"\0"
			while (end >= pos)
			{
				_str[end + 1] = _str[end];
				if (end == 0)
				{
					break;
				}
				--end;
			}
			_str[pos] = ch;
			_size++;
			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos >= 0 && pos < _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			size_t end = _size;
			//pos位置及其后面的都要进行移动
			while (end >= pos)
			{
				_str[end + len] = _str[end];
				if (end == 0)
				{
					break;
				}
				end--;
			}
			strncpy(_str + pos, str, len); //strncpy可以控制复制的字符数
			_size += len;
			return *this;
		}

		string& erease(size_t pos, size_t len = npos)
		{
			//pos位置到len位置之前的字符个数（包含pos位置的字符）
			size_t leftLen = len - pos;
			if (leftLen > _size - pos)
			{
				_size = pos;
				_str[_size] = '\0';
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			return *this;
		}

		bool operator>(const char* str);
		bool operator<(const char* str);
		bool operator==(const char* str);
		bool operator>=(const char* str);
		bool operator<=(const char* str);
		bool operator!=(const char* str);

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos;
	};

	 const size_t string::npos = -1;
}
