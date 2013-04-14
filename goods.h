#ifndef ASM_GOODS_H
#define ASM_GOODS_H

#include <QString>

namespace asmt
{
	class  Goods
	{
	public:
		Goods(const QString& _barcode, const QString& _name = QString(), int _count = 1);
		Goods(const QString& _barcode, int _count = 1);

		const QString& barcode() const;
		const QString& name() const;
		int count() const;

	private:
		QString m_barcode;
		QString m_name;
		int m_count;
	};
}

#endif //ASM_GOODS_H