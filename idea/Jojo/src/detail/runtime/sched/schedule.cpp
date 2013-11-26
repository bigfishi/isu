
#include <go/runtime_mgr.h>
#include <go/detail/goroutine.h>
//#include <boost/thread/mutex.hpp>
#include <go/detail/tools/mgrgeter.h>
#include <go/detail/schedule/schedule.h>
#include <go/detail/runtime/thread/thread.h>
#include <go/detail/handle/mhand_for_sched.h>
#include <go/detail/runtime/machine/machine.h>
//#include <boost/date_time/posix_time/posix_time.hpp>


//File:schedule.cpp
// (C) Copyright 2013 ��Ԫ�
// Use, modification and distribution is subject to the Isu source code
// License, Version 0.1. (See local file LICENSE_0_1.txt)
// See http://blog.csdn.net/fq_hayate for updates, documentation, and revision history.
//Q&A:a313865974@sina.com

namespace isu
{
	namespace go
	{
		namespace detail
		{
			scheduler::scheduler()
				:
				_mmgrhand( global_machine_manager() ),
				_mpmhand( global_processor_manager() )
			{

			}

			void scheduler::interrupt()
			{
			//	_mschedr->interrupt();
			}

			void scheduler::idle( const shared_ptr<machine>& m )
			{
				_mmgrhand.idle( m->id() );
				mhand_for_sched(m).pause();
			}

			void scheduler::gogo(functional f)
			{
				processor_ptr p = _mpmhand.allocp();
				if (!p)
				{
					global_goroutine_manager()->task(f);
					return;
				}
				//����gogo��ʱ��ᵼ���ź����ļ���
				shared_ptr<goroutine> g = global_goroutine_manager()->gogo(f);
				shared_ptr<machine> m = _mmgrhand.allocm(g,p);
				assert(m);
				phand_for_sched(p).current_machine(m);
				mhand_for_sched(m).run();
			}
			void scheduler::send_task()
			{
				_send_task();
			}

			void scheduler::_send_task()
			{
				//��ʱû��ʵ��
			}

		/*	shared_ptr<boost::mutex> _init_mtx()
			{
				shared_ptr<boost::mutex> ret(new boost::mutex);
				ret->lock();
				return ret;
			}

			void scheduler::timer_wait(time_type t)
			{
			}

			typeconfig::processor_iterator scheduler::begin()
			{
				return global_processor_manager()->begin();
			}

			typeconfig::processor_iterator scheduler::end()
			{
				return global_processor_manager()->end();
			}

			void scheduler::_nextg(processor_ptr& proc)
			{
				phand_for_sched ph(proc);
				if (ph.asking())//���proc������Դȱ�����ȴ�����ô����Ҫ����
					return;//���������˲��������ԴҲû�й�ϵ��ʱ��Ƭ���ɿ�������
				auto m = ph.current_machine();
				assert(m);
				mhand_for_sched mh(m);
				mh.pause();
				auto curg = m->curg();
				gstate st = curg->state();
				if (st != gswitching&&st != gdead)
				{
					//�л��ڼ����еĲ������û����룬�����л�
					mh.gotog(ph.alloc_g());
					ph.pushg(curg);
				}
				mh.resume();
			}

			void scheduler::_start()
			{//��ʱû��ʵ��
			/ *	while (true)
				{
					timer_wait(100);
					std::for_each(scheduler::begin(), scheduler::end(), [](processor_ptr& proc)
					{
						_nextg(proc);
					});
				}* /
			}*/
		}
	}
}