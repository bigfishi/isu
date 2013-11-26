#ifndef ISU_GO_MACHINE_MGR_H
#define ISU_GO_MACHINE_MGR_H

//File:machine_mgr.h
// (C) Copyright 2013 ��Ԫ�
// Use, modification and distribution is subject to the Isu source code
// License, Version 0.1. (See local file LICENSE_0_1.txt)
// See http://blog.csdn.net/fq_hayate for updates, documentation, and revision history.
//Q&A:a313865974@sina.com

#include "mstate.h"
#include <go/detail/config.h>
#include <hash_map>

namespace isu
{
	namespace go
	{
		namespace detail
		{
			class machine;
			class m_mgrhand_for_sched;//�������ſ��Խ���M�ĵ���
			class m_mgrhand_for_sched;

			class machine_mgr
				:private typeconfig
			{
			public:

				const std::size_t runing() const;
				const std::size_t idleing() const;
				const std::size_t syscall() const;

			private:
				lock_type _mlock;
				typedef unsigned long id_type;
				//ͨ��id��������
				std::hash_map<id_type,shared_ptr<machine>> 
					_mrunning, _msyscall, _midle;
				//~~~~~~~~~~~~~
				friend class m_mgrhand_for_sched;
				friend class m_mgrhand_for_sched;
			};
		}
	}
}
#endif