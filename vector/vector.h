#include<iostream>
#include<string.h>
#include<assert.h>

namespace vectorstl
{
  template<class T>
  class vector{
  public:
    typedef T value_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    vector():_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){}
  

    //要提前将_start,_finish,_end_of_storage设为空，因为reserve中有关于size()的计算，如果不置空，随机值可能会导致程序错误
    vector(const vector<value_type>& v):_start(nullptr),_finish(nullptr),_end_of_storage(nullptr)
    {
      reserve(v.capacity());
      for(auto e: v)
      {
        push_back(e);
      }
      _finish = _start + v.size();
      _end_of_storage = _start + v.capacity();
      
    }

    vector<value_type>& operator=(vector<value_type> v)
    {
      swap(v);
      return *this;
    }

    ~vector()
    {
      delete[] _start;
      _start = _finish = _end_of_storage = nullptr;
    }

    void swap(vector<value_type> v)
    {
      std::swap(_start,v._start);
      std::swap(_finish,v._finish);
      std::swap(_end_of_storage,v._end_of_storage);
    }

    size_t size() const{
      return _finish - _start;
    }

    size_t capacity() const{
      return _end_of_storage - _start;
    }

    
    void reserve(size_t n)
    {
      if(n>capacity())
      {
        size_t sz = size();
        iterator temp = new value_type[n];
        //只有_start不为空时，才需要将_start指向的空间复制到新空间
        if(_start)
        {
          //下面这种复制方法是将_start中的值全部复制，是浅拷贝。
          //如vector中存放string类时，delete []_start时会将新空间的每个对象指向的字符串空间删除
         //memcpy(temp,_start,sz*sizeof(value_type));
         for(size_t i = 0; i < sz; ++i)
         {
           //该方法会自动调用vector内的类型的operator=(),为深拷贝
           temp[i] = _start[i];
         }
         delete[] _start;
        }
        _start = temp;
        _finish = _start + sz;
        _end_of_storage = _start + n;
      }
    }

    iterator insert(const iterator pos, const value_type& val)
    {
      assert(pos<=_finish);
      if(_finish == _end_of_storage)
      {
        size_t len = pos - _start;
        size_t newcapacity = capacity() == 0? 4: 2*capacity();
        reserve(newcapacity);
        pos = _start + len;
      }
      iterator end = _finish;
      while(end>pos)
      {
        *end = *(end-1);
        end--;
      }
      *pos = val;
      _finish++;
      return pos;
    }


    iterator insert(const iterator pos,size_t count , const value_type& val)
    {
      assert(pos <=_finish);
      size_t sz = size();
      if(_finish + count > _end_of_storage)
      {
        size_t len = pos - _start;
        reserve(sz + count);
        pos = _start + len;
      }
      iterator end = _finish - 1;
      while(end >= pos)
      {
       *(end + count) = *(end);
        end--;
      }
      iterator it = pos;
      while(it < pos + count)
      {
        *it = val;
        it++;
      }
      _finish += count;
      return pos;
    }

    //删除pos位置的对象
    iterator erase(iterator pos)
    {
      iterator it = pos + 1;
      while(it!=_finish)
      {
        *(it - 1) = *it;
        ++it;
      }
     -- _finish;
     return pos;
    }
    


    void push_back(const value_type& val)
    {
      if(_finish ==  _end_of_storage)
      {
        size_t newcapacity = capacity() == 0? 4 : capacity()*2;        
        reserve(newcapacity);
      }
      *_finish = val;
      ++_finish;
    }

    vector<value_type>& operator[](size_t i)
    {
      return _start[i];
    }

    const vector<value_type>& operator[](size_t i) const
    {
      return _start[i];
    }

    iterator begin()
    {
      return _start;
    }

    iterator end()
    {
      return _finish;
    }

  private:
    iterator _start;
    iterator _finish;
    iterator _end_of_storage;


  };
}
