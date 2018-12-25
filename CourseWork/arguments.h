#pragma once
#include "configs.h"

//����� ��� ������ � ����������� ��������� ������
namespace cmd {
	class arguments {
		size_t count;
		char ** argument;
	protected:
		//�������� �� ������ ������ ������
		bool isKey(size_t index) const;
		//����� ��������� �� �����
		std::string find(const std::string & name, std::string & def) const;
	public:
		arguments(size_t count, char ** arguments);
		//��������� ������������ �� ������ ���������� ����������
		void apply(config & cfg) const;
	};
}