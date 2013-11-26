#include <go/detail/tools/semapore.h>
#include <stdexcept>
#include <iostream>

//File:semapore.cpp
// (C) Copyright 2013 ��Ԫ�
// Use, modification and distribution is subject to the Isu source code
// License, Version 0.1. (See local file LICENSE_0_1.txt)
// See http://blog.csdn.net/fq_hayate for updates, documentation, and revision history.
//Q&A:a313865974@sina.com

namespace isu
{
	semapore::semapore(const count_type init, const count_type max)
		:_mnc(init), _mmc(max), _mlock()
	{
		_mlock.lock();//��������
	}

	void semapore::wait()
	{
		if (_mnc == 0)
		{
			std::cout << "�������" << std::endl;
			_mlock.lock();
		}
		--_mnc;
	}

	void semapore::desemapore( count_type de)
	{
		if (_mnc < de)
			throw std::runtime_error("desemapore arg is too big");
		_mnc -=de;
		//���ﲻ�õȴ�
	}

	void semapore::post()
	{
		addsemapore(1);
	}

	void semapore::addsemapore(count_type ad)
	{
		if (_mnc + ad > _mmc)
			throw std::overflow_error("semapore arg is to big with add");
		if (_mnc == 0)
		{
			_mnc += ad;
			_mlock.unlock();
			return;
		}
		_mnc += ad;
	}

	const bool semapore::try_wait()
	{
		if (_mnc==0)
		return _mlock.try_lock();
		return true;
	}

	const bool semapore::timed_wait()
	{
		//û��ʵ��
		return false;
	}
}