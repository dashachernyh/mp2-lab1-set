// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp),MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField),MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf),MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	TSet rez;
	rez.MaxPower = s.MaxPower;
	rez.BitField = s.BitField;
	return rez;

}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField == s.BitField) return true;
	else return false;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField != s.BitField) return true;
	else return false;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField b;
	b = BitField | s.BitField;
	TSet rez(b);
	return rez;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet rez(BitField);
	rez.InsElem(Elem);
	return rez;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet rez(BitField);
	rez.DelElem(Elem);
	return rez;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField b;
	b = BitField & s.BitField;
	TSet rez(b);
	return rez;
}

TSet TSet::operator~(void) // дополнение
{
	TSet rez(~BitField);
	return rez;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int a;
	istr >> a;
	while (a >= 0)
		s.InsElem(a);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i) != 0) ostr << i << ' ';
		return ostr;
	}
}
