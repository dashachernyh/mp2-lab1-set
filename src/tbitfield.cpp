// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include <iostream>
using namespace std;
#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = BitLen / 32 + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int p = n % 32;
	return 1 << p;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	mask = ~mask;
	pMem[index] &= mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int rez;
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	return rez = pMem[index] & mask;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		delete[]pMem;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	else
	{
		for (int i = 0; i < MemLen - 1; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 0;
		}
		return 1;
  }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 1;
	else
	{
		for (int i = 0; i < MemLen - 1; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 1;
		}
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField max,min;
	if (BitLen >= bf.BitLen)
	{
		max= *this;
		min = bf;
	}
	else
	{
		max = bf;
		min= *this;
	}
	
		TBitField rez(max.BitLen);
		if (min.MemLen == 1)
		{
			for (int i = 0; i < min.BitLen; i++)
			{
				if (min.GetBit(i) == 1) rez.SetBit(i);
				else rez.ClrBit(i);
			}
		}
		else
		{
			for (int i = 0; i < min.MemLen - 1; i++)
			{
				rez.pMem[i] = min.pMem[i];
			}
			for (int i = (min.MemLen - 1) * 32; i < min.BitLen; i++)
			{
				if (min.GetBit(i) == 1) rez.SetBit(i);
				else rez.ClrBit(i);
			}

			for (int i = 0; i < max.MemLen - 1; i++)
			{
				rez.pMem[i] |= max.pMem[i];
			}
			if (min.BitLen == max.BitLen)
				for (int i = (max.MemLen - 1) * 32; i < max.BitLen; i++)
				{
					if (max.GetBit(i) | rez.GetBit(i) == 1) rez.SetBit(i);
					else rez.ClrBit(i);
				}
		}
			return rez;
		
}

TBitField TBitField::operator& (const TBitField &bf) // операция "и"
{
	TBitField max, min;
	if (BitLen >= bf.BitLen)
	{
		max = *this;
		min = bf;
	}
	else
	{
		max = bf;
		min = *this;
	}

	TBitField rez(max.BitLen);
	if (min.MemLen == 1)
	{
		for (int i = 0; i < min.BitLen; i++)
		{
			if (min.GetBit(i) == 1) rez.SetBit(i);
			else rez.ClrBit(i);
		}
	}
	else
	{
		for (int i = 0; i < min.MemLen - 1; i++)
		{
			rez.pMem[i] = min.pMem[i];
		}
		for (int i = (min.MemLen - 1) * 32; i < min.BitLen; i++)
		{
			if (min.GetBit(i) == 1) rez.SetBit(i);
			else rez.ClrBit(i);
		}

		for (int i = 0; i < max.MemLen - 1; i++)
		{
			rez.pMem[i] &= max.pMem[i];
		}

		if (min.BitLen == max.BitLen)
			for (int i = (max.MemLen - 1) * 32; i < max.BitLen; i++)
			{
				if (max.GetBit(i)&rez.GetBit(i) == 1) rez.SetBit(i);
				else rez.ClrBit(i);
			}
	}
		return rez;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField rez(BitLen);
	for (int i = 0; i < MemLen; i++)
		rez.pMem[i] = ~pMem[i];
	return rez;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char c;
	int i = 0;
	do {
		istr >> c;
		if (c == '0') bf.ClrBit(i);
		if (c == '1') bf.SetBit(i);
		i++;
	} while (c == '0' || c == '1');

		return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i) == 0) ostr << 0;
		else ostr << 1;
	}
	return ostr;
}
