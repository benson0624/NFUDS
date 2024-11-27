#include <iostream>
#include <cmath>

using namespace std;

class Polynomial;

class Term
{
	friend Polynomial;
	friend ostream& operator<<(ostream& os, const Polynomial& polynomial);
	friend istream& operator>>(istream& is, const Polynomial& polynomial);
private:
	float coef;
	int exp;
};

class Polynomial {
	friend ostream& operator<<(ostream& os, const Polynomial& polynomial);
	friend istream& operator>>(istream& is, Polynomial& polynomial);
private:
	Term* termArray;
	int capacity;
	int terms;
public:
	Polynomial()
	{
		capacity = 2;
		terms = 0;
		termArray = new Term[capacity];
	}

	void newTerm(float c, int e)
	{
		if (capacity == terms)
		{
			Term* temp = new Term[capacity];
			copy(termArray, termArray + terms, temp);
			capacity *= 2;
			delete[] termArray;
			termArray = new Term[capacity];
			copy(temp, temp + terms, termArray);
			delete[] temp;
		}
		termArray[terms].coef = c;
		termArray[terms].exp = e;
		terms++;
	}

	Polynomial Add(const Polynomial& other)
	{
		Polynomial out;
		int aPos = 0;
		int bPos = 0;
		int biggest = -1;
		if (this->termArray[0].exp > other.termArray[0].exp)
			biggest = this->termArray[0].exp;
		else
			biggest = other.termArray[0].exp;

		while (biggest >= 0)
		{
			int c = 0;
			if (this->termArray[aPos].exp == biggest)
			{
				c += this->termArray[aPos].coef;
				aPos++;
			}
			if (other.termArray[bPos].exp == biggest)
			{
				c += other.termArray[bPos].coef;
				bPos++;
			}
			if (c != 0)
			{
				out.newTerm(c, biggest);
			}
			biggest--;
		}
		return out;
	}

	Polynomial Mult(const Polynomial& other)
	{
		Polynomial out;
		float cTemp = 0;
		int eTemp = 0;
		for (int i = 0; i < this->terms; i++)
		{
			Polynomial temp;
			for (int j = 0; j < other.terms; j++)
			{
				cTemp = this->termArray[i].coef * other.termArray[j].coef;
				eTemp = this->termArray[i].exp + other.termArray[j].exp;
				temp.newTerm(cTemp, eTemp);
			}
			out = out.Add(temp);
		}
		return out;
	}

	float Eval(float f)
	{
		float out = 0;
		for (int i = 0; i < terms; i++)
		{
			out += termArray[i].coef * pow(f, termArray[i].exp);
		}
		return out;
	}

};

ostream& operator<<(ostream& os, const Polynomial& polynomial)
{
	int i = 0;
	while (1)
	{
		if (polynomial.termArray[i].exp == 0)
		{
			os << polynomial.termArray[i].coef;
		}
		if (polynomial.termArray[i].exp == 1)
		{
			if (polynomial.termArray[i].coef == 1)
				os << "x";
			else
				os << polynomial.termArray[i].coef << "x";
		}
		if (polynomial.termArray[i].exp > 1)
		{
			if (polynomial.termArray[i].coef == 1)
				os << "x^" << polynomial.termArray[i].exp;
			else
				os << polynomial.termArray[i].coef << "x^" << polynomial.termArray[i].exp;
		}
		i++;
		if (i == polynomial.terms) break;
		os << " + ";
	}
	return os;
}

istream& operator>>(istream& is, Polynomial& polynomial)
{
	float c;
	int e;
	is >> c >> e;
	if (c == 0 && e == 0.0f)
	{
		is.setstate(std::ios::failbit);
		return is;
	}
	polynomial.newTerm(c, e);
	return is;
}

int main()
{
	Polynomial p;
	Polynomial q;

	while (cin >> p);//overloaded cin
	cin.clear();//clear cin state

	while (cin >> q);
	cin.clear();

	cout << "p(x) = " << p << endl;//overloaded cout
	cout << "q(x) = " << q << endl;
	cout << "p(x) + q(x) = " << p.Add(q) << endl;//Add p and q and cout
	cout << "p(x) * q(x) = " << p.Mult(q) << endl;//Multply p and q and cout

	cout << "p(2.5) = " << p.Eval(2.5) << endl;//Evaluate p(x) at 2.5
}
