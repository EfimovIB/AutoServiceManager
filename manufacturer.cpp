#include "manufacturer.h"

namespace asmt
{
	Manufacturer::Manufacturer(const QString& _name)
		: QObject(),
		m_id(-1),
		m_name(_name)
	{
	}

	const QString& Manufacturer::name() const
	{
		return m_name;
	}

	QList<Manufacturer*> Manufacturer::manufacturer()
	{
		QList<Manufacturer*> l;
		return l;
	}

	void Manufacturer::setName(const QString& _name)
	{
		m_name = _name;
	}

}