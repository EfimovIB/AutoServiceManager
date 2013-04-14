#include "goods.h"

namespace asmt
{
	Goods::Goods(const QString& _barcode, const QString& _name, int _count)
		: m_barcode(_barcode),
		m_name(_name),
		m_count(_count)
	{}

	Goods::Goods(const QString& _barcode, int _count)
		: m_barcode(_barcode),
		m_count(_count)
	{}

	const QString& Goods::barcode() const
	{
		return m_barcode;
	}

	const QString& Goods::name() const
	{
		return m_name;
	}

	int Goods::count() const
	{
		return m_count;
	}

}