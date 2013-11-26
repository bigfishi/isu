#ifndef ISU_BASE_CHANNEL_H
#define ISU_BASE_CHANNEL_H

//File:base_channel.h
// (C) Copyright 2013 ��Ԫ�
// Use, modification and distribution is subject to the Isu source code
// License, Version 0.1. (See local file LICENSE_0_1.txt)
// See http://blog.csdn.net/fq_hayate for updates, documentation, and revision history.
//Q&A:a313865974@sina.com

#include <cstddef>
#include <forward_list>
#include <boost/smart_ptr/detail/spinlock.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <utility>

namespace isu
{
	namespace go
	{
		namespace detail
		{
			class goroutine;
		}
	}
}

namespace isu
{
	//2��channel,��buff�ģ�����buff��
	template<class T,class Alloc=std::allocator<T> >
	using container = std::forward_list<T, Alloc>;



	class base_channel
	{
	public:
		typedef std::size_t size_type;
		typedef void* HANDLE;
		typedef HANDLE thread_type;
		typedef thread_type thread_type_pointer;
		typedef boost::detail::spinlock lock_type;
		typedef boost::detail::spinlock::scoped_lock scoped_lock;
		typedef go::detail::goroutine* goroutine_ptr;
		base_channel();
		void post();//�������,����һ�������Ķ���
		//�������push�Ķ�����һ��G����G���в�Ϊ�գ��򼤻�G,���򼤻�thread
		//��֮��Ȼ
		void wait();//��ȡ���ݣ�������
	private:
		//wait list for thread
		void _block();
		void _unblock();
		void _post_to_goroutine();
		void _wait_goroutine();

		boost::interprocess::interprocess_semaphore _msem;
	//	lock_type _mlock;
		container<std::pair<thread_type_pointer,goroutine_ptr> > _mwaiting_g;
	};
}
#endif