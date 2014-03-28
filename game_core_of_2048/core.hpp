/*
Copyright : ��Ԫ� 2014
email : sismvg@hotmail.com
��һ����������������������������������������GNUͨ�ù������֤�������޸ĺ����·�����һ���򡣻��������֤�ĵڶ��棬���ߣ��������ѡ�����κθ��µİ汾��
������һ�����Ŀ����ϣ�������ã���û���κε���������û���ʺ��ض�Ŀ�ĵ������ĵ���������ϸ����������GNUͨ�ù������֤��
*/
#ifndef CORE_OF_2048_HPP
#define CORE_OF_2048_HPP

#include  <boost/function.hpp>
#include <boost/multi_array.hpp>

template<class T, std::size_t dimension>
using multi_array = boost::multi_array<T, dimension>;

namespace isu
{
	enum operation_axis{ longitudinal=0,lateral};

	class multi_index
	{
	public:
		typedef int length_type;
		multi_index(const length_type, const length_type);

		const bool operator==(const multi_index&);
		const bool operator!=(const multi_index&);
		const length_type& axis(const operation_axis) const;
		length_type& axis(const operation_axis);

	private:
		length_type _lateral, _longitudinal;
	};

	class operation_detail
	{
	public:
		typedef int setp_type;
		typedef multi_index::length_type length_type;

		operation_detail(const multi_index, const operation_axis, const length_type, const setp_type);

		multi_index start;
		operation_axis axis;
		length_type boundary;
		setp_type main_axis_setp;
	};

	class board_setting
	{
	public:
		typedef std::size_t length_type;
		typedef std::size_t data_type;
		board_setting(const length_type longitudinal, const length_type lateral, const data_type=2048);

		length_type lateral, longitudinal;
		data_type maxinum_count;
	};


	class staus_callback
	{
	public:
		boost::function<void(multi_index,multi_index)> move;
		boost::function<void(multi_index, board_setting::data_type)> change, random_piece, merge;
		boost::function<void(void)> dead_board, win;
	};

	class board
	{
	public:
		//λ������mains��vices��Ӧ��
		enum operation{up=0,down=1,left=2,right=3};

		typedef std::size_t data_type;
		typedef operation_detail::setp_type setp_type;
		typedef multi_index::length_type length_type;
		typedef std::pair<multi_index, data_type> piece_info;

		board(const board_setting&, const staus_callback&);
		
		bool dead_board();
		void change(operation);
		void start(std::size_t intial_piece);
		length_type shape(std::size_t) const;	
		const data_type& data_of(const multi_index&) const;
		
	private:

		typedef std::function<bool(const multi_index&)> multi_fn;
		typedef std::pair<length_type, length_type> boundary_info;

		std::size_t _bits_count;
		staus_callback	_callback;
		data_type	_maxinum_count;
		multi_array<data_type, 2>	_board;

		data_type& _data_of(const multi_index&);

		void _random_piece();
		piece_info _next_piece(const operation_detail&);
		void _mapping_multi_index(multi_index& index);
		void _mapping_operation_detail(operation_detail& detail);

		void _each_axis(const operation_detail&, multi_fn);
		void _axis_next(multi_index&, operation_axis, length_type);
		void _axis_next(operation_detail&);
		bool _full_board() const;
		bool _check_dead_board() const;
		void _set_board(const multi_index&, const data_type&);
		void _change_board(const operation_detail&, const operation_detail&);
		
		void _merge(const multi_index&, const multi_index&);
		void _move(const multi_index&, const multi_index&);
		//����������
		static const operation_detail _mains_axis[4];
		//��������ᣬ�������෴��axis
		static const operation_detail _vice_axis[4];
		static const length_type none_pos = -1;
		//windows���̳߳ػ���boost���̳߳ء������Ǹ�����
	};
}
#endif