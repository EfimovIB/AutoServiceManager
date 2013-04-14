#ifndef ASM_CUSTOMER_H
#define ASM_CUSTOMER_H

#include <QUuid>

namespace asmt
{
	class Customer
	{
	public:
		Customer();

	private:
		QUuid m_id;
	};
}

#endif //ASM_CUSTOMER_H