#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// auto_ptr：权限转移，不安全
// unique_ptr：禁止拷贝和赋值
// shared_ptr：可以拷贝和赋值，用一个引用计数去计算有多少个对象
// weak_ptr：解决shared_ptr的循环引用问题
template <class T>
class smartPtr
{
public:
	smartPtr(T* ptr)
		: _ptr(ptr)
	{
		// 构造的时候创建

	}
	~smartPtr()
	{
		// 析构的时候销毁
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
	smartPtr(smartPtr<T>& sp)
		: _ptr(sp._ptr)
	{
		sp._ptr = nullptr;
	}
	smartPtr<T>& operator=(smartPtr<T>& sp)
	{
		if (this != &sp)
		{
			delete _ptr;
			_ptr = sp._ptr;
			sp._ptr = nullptr;
		}
		return *this;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};
class Date
{
public:
	int _year = 1;
};
void Test1()
{
	smartPtr<int> sp(new int(1));
	smartPtr<int> sp1(new int(2));

	// 拷贝构造
	smartPtr<int> sp2(sp);
	// 赋值重载
	sp1 = sp2;

	// 智能指针类似指针的操作
	smartPtr<Date> sp3(new Date);
	cout << (*sp3)._year << endl;
	cout << sp3->_year << endl;
}
void Test2()
{
	auto_ptr<Date> ap(new Date);
	cout << ap->_year << endl;
	// 拷贝时发生权限转移
	auto_ptr<Date> ap1(ap);
	cout << ap1->_year << endl;

	// 转移之后，智能指针不再拥有资源
	cout << ap->_year << endl;	// 这里发生错误，指针为空
}
void Test3()
{
	unique_ptr<Date> up(new Date);
	// unique_ptr<Date> up1(up);	// 这里被禁止了,拷贝构造是删除函数
	unique_ptr<Date> up2(new Date);
	// up2 = up;	// 这里也被禁止了，赋值重载是删除函数
}
// 模拟实现 unique_ptr
template <class T>
class Unique_ptr
{
public:
	Unique_ptr(T* ptr)
		: _ptr(ptr)
	{}
	~Unique_ptr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	// 防止拷贝
	Unique_ptr(const Unique_ptr<T>& up) = delete;
	Unique_ptr<T>& operator=(const Unique_ptr<T>& up) = delete;
private:
	T* _ptr;
};
void Test4()
{
	shared_ptr<Date> sp(new Date);
	cout << sp.use_count() << endl;
	shared_ptr<Date> sp1(sp);
	cout << sp.use_count() << endl;
	shared_ptr<Date> sp2(new Date);
	sp2 = sp;
	cout << sp.use_count() << endl;
}

#include <mutex>
// 模拟实现 shared_ptr
template <class T>
class Shared_ptr
{
public:
	Shared_ptr(T* ptr)	// 这里不能用const的原因：因为要用ptr给_ptr赋值，而_ptr是T*类型。
		: _ptr(ptr)
		, use_count(new int(1))
		, _mtx(new mutex)
	{}
	~Shared_ptr()
	{
		if (subRef() == 0)
		{
			delete _ptr;
			delete use_count;
			delete _mtx;
			use_count = nullptr;
			_ptr = nullptr;
		}
	}
	Shared_ptr(const Shared_ptr<T>& sp)
		: _ptr(sp._ptr)
		, use_count(sp.use_count)
		, _mtx(sp._mtx)
	{
		addRef();
	}
	Shared_ptr<T>& operator=(const Shared_ptr<T>& sp)
	{
		// if (this != &sp) 这里应该判断双方管理的资源是否相同
		if (_ptr != sp._ptr)
		{
			if (subRef() == 0)	// 线程安全版本
			{
				delete _ptr;
				delete use_count;
				delete _mtx;
			}
			_ptr = sp._ptr;
			use_count = sp.use_count;
			_mtx = sp._mtx;
			addRef();
		}
		return *this;
	}
	int getUseCount()
	{
		return *use_count;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	int addRef()
	{
		_mtx->lock();
		++(*use_count);
		_mtx->unlock();
		return *use_count;
	}
	int subRef()
	{
		_mtx->lock();
		--(*use_count);
		_mtx->unlock();
		return *use_count;
	}
private:
	T* _ptr;
	int* use_count;
	mutex* _mtx;
};

void Test5()
{
	Shared_ptr<Date> sp1(new Date);
	Shared_ptr<Date> sp2(new Date);
	cout << sp1.getUseCount() << endl;
	Shared_ptr<Date> sp3(sp1);
	cout << sp1.getUseCount() << endl;
	sp2 = sp1;
	cout << sp1.getUseCount() << endl;
}
#include <thread>
void func(Shared_ptr<Date> sp, int n)
{
	for (int i = 0; i < n; i++)
	{
		Shared_ptr<Date> copy(sp);
	}
}
void TestThread()	// 其实这份代码有个问题：环形引用
{
	Shared_ptr<Date> sp(new Date);
	cout << sp.getUseCount() << endl;
	int n;
	cin >> n;
	thread t1(func, sp, n);
	thread t2(func, sp, n);

	t1.join();
	t2.join();
	cout << sp.getUseCount() << endl;
}
template <class T>
struct ListNode
{
	~ListNode()
	{
		cout << "析构" << endl;
	}
	shared_ptr<ListNode<T>> prev;
	shared_ptr<ListNode<T>> next;
};
void Test6()
{
	// 环形引用：我等着你释放，你等着我释放，结果都释放不了资源
	shared_ptr<ListNode<int>> sp(new ListNode<int>);
	shared_ptr<ListNode<int>> sp1(new ListNode<int>);
	cout << sp.use_count() << endl;
	cout << sp1.use_count() << endl;

	sp->prev = sp1;
	sp1->next = sp;

	cout << sp.use_count() << endl;
	cout << sp1.use_count() << endl;
}

template <class T>
struct ListNode2
{
	~ListNode2()
	{
		cout << "析构" << endl;
	}
	weak_ptr<ListNode2<T>> prev;
	weak_ptr<ListNode2<T>> next;
};
void Test7()
{
	// 使用weak_ptr解决循环引用问题
	shared_ptr<ListNode2<int>> sp(new ListNode2<int>);
	shared_ptr<ListNode2<int>> sp1(new ListNode2<int>);
	cout << sp.use_count() << endl;
	cout << sp1.use_count() << endl;

	sp->prev = sp1;
	sp1->next = sp;

	cout << sp.use_count() << endl;
	cout << sp1.use_count() << endl;
}

template <class T>
struct freeM
{
	void operator()(T* ptr)
	{
		free(ptr);
		cout << "free" << endl;
	}
};
void Test8()
{
	// 定制删除器：shared_ptr 只能使用delete删除对象，如果是malloc或者new[]的需要定制删除器
	freeM<int> fm;
	shared_ptr<int> sp((int*)malloc(sizeof(int)));
}