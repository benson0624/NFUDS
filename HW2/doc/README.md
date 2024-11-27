# Polynomial

## 1. 解題說明

Implement polynomial class as shown in its ADT,

including add, mult and eval,

also overload both cin(>>) and cout(<<).

For example:

$`p(x)=2x^5+3x^4+4x^3+8x^2+7x+9`$

$`q(x)=3x^4+7x^2+8x+19`$

The result of $`p(x)+q(x)`$ should be:

$`2x^5+6x^4+4x^3+15x^2+15x+28`$

Refer to implementation in `Source.cpp`, the add implementation:

```cpp
Polynomial Add(const Polynomial& other)
{
	Polynomial out;
	int aPos = 0;
	int bPos = 0;
	int biggest = -1;
	//Decide which polynomial contains greater degree
	if (this->termArray[0].exp > other.termArray[0].exp)
		biggest = this->termArray[0].exp;
	else
		biggest = other.termArray[0].exp;

	//Loop from max degree to 0
	//When finding the same as current degree add it's coefficient to output
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

```


The result of $`p(x)*q(x)`$ should be:

$`6x^9+9x^8+26x^7+61x^6+111x^5+172x^4+189x^3+271x^2+205x +171`$

Refer to implementation in `Source.cpp`, the mult implementation:

```cpp
Polynomial Mult(const Polynomial& other)
{
	Polynomial out;
	float cTemp = 0;
	int eTemp = 0;
	//Nested loop to multply each term of a function to the other
	for (int i = 0; i < this->terms; i++)
	{
		//Temporary variavle to store current result
		Polynomial temp;
		for (int j = 0; j < other.terms; j++)
		{
			//Multply the coefficient of both polynomial
			cTemp = this->termArray[i].coef * other.termArray[j].coef;
			//Add the exponent of both polynomial
			eTemp = this->termArray[i].exp + other.termArray[j].exp;
			//Store current result to temp
			temp.newTerm(cTemp, eTemp);
		}
		//Add current result to output
		out = out.Add(temp);
	}
	return out;
}
```

The result of $`p(2.5)`$ should be:

$`451.5`$

Refer to implementation in `Source.cpp`, the eval implementation:

```cpp
float Eval(float f)
{
	float out = 0;
	//Loop through all terms and adds the result to output
	//Following the rule c*f^e
	for (int i = 0; i < terms; i++)
	{
		out += termArray[i].coef * pow(f, termArray[i].exp);
	}
	return out;
}
```

When inputting data to class,should use overloaded cin(>>),

Refer to implementation in `Source.cpp`, the cin overloading implementation:

```cpp
istream& operator>>(istream& is, Polynomial& polynomial)
{
	float c;
	int e;
	//We suppose user doesn't do unallowed input
	//pipe from input stream to two temporary variable
	is >> c >> e;
	//Terminate condition
	//Implementing like this needs to clear failbit after
	if (c == 0 && e == 0.0f)
	{
		is.setstate(std::ios::failbit);
		return is;
	}
	//Adding new term by using newTerm member function
	polynomial.newTerm(c, e);
	return is;
}
```

When representing the result should use overloaded cout(<<),

Refer to implementation in `Source.cpp`, the cout overloading implementation:

```cpp
ostream& operator<<(ostream& os, const Polynomial& polynomial)
{
	int i = 0;//Index to loop through all terms
	//Loop through all terms and pipe into output stream
	//Then return the result 
	while (1)
	{
		//Handle constant case
		if (polynomial.termArray[i].exp == 0)
		{
			os << polynomial.termArray[i].coef;
		}
		//Handle exponent=1 case
		if (polynomial.termArray[i].exp == 1)
		{
			if (polynomial.termArray[i].coef == 1)
				os << "x";
			else
				os << polynomial.termArray[i].coef << "x";
		}
		//Handle any other case
		if (polynomial.termArray[i].exp > 1)
		{
			if (polynomial.termArray[i].coef == 1)
				os << "x^" << polynomial.termArray[i].exp;
			else
				os << polynomial.termArray[i].coef << "x^" << polynomial.termArray[i].exp;
		}
		i++;
		if (i == polynomial.terms)break;
		os << " + ";
	}
	return os;
}
```

## 2. 演算法設計與實作

```cpp
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
```

## 3. 效能分析

### Add

-$`f(m+n) = O(n)`$, suppose $`n > m`$
-$`S(P) = 3+n`$, n is the amount of total array length

### Mult

- $`f(m*n) = O(n^2)`$, suppose $`n > m`$
- $`S(P) = 3+n^2`$, suppose $`n > m`$

### Eval

- $`f(n) = O(n)`$
- $`S(P) = 2`$

## 4. 測試與過程

### Input

```plain
2 5
3 4
4 3
8 2
7 1
9 0
0 0
3 4
7 2
8 1
19 0
0 0
```

### Output

```plain
p(x) = 2x^5 + 3x^4 + 4x^3 + 8x^2 + 7x + 9
q(x) = 3x^4 + 7x^2 + 8x + 19
p(x) + q(x) = 2x^5 + 6x^4 + 4x^3 + 15x^2 + 15x + 28
p(x) * q(x) = 6x^9 + 9x^8 + 26x^7 + 61x^6 + 111x^5 + 172x^4 + 189x^3 + 271x^2 + 205x + 171
p(2.5) = 451.5
```

### 驗證

Using $`p(x)=2x^2+x`$ and $`q(x)=3x+1`$ as example

$`p(x)+q(x)`$:

First we determine which has a greater degree,

which would be $`p(x)`$ having $`2x^2`$, thus set biggest to $`2`$

starting from `biggest=2` we first add $`2x^2`$ to out,

at `biggest=1` we add $`x`$ and  $`3x`$ to out,

lastly at `biggest=0` we add $`1`$ to out.

In the end returns $`p(x)+q(x)=2x^2+4x+1`$

$`p(x)*q(x)`$:

First we multiply $`2x^2`$ by $`3x`$ and add to out,

then we multiply $`2x^2`$ by $`1`$ and add to out,

then we multiply $`x`$ by $`3x`$ and add to out,

then we multiply $`x`$ by $`1`$ and add to out.

In the end returns $`6x^3+5x^2+x`$

$`p(2)`$:

$`2x^2`$ at $`x=2`$ we get $`8`$ and add to out,

$`x`$ at $`x=2`$ we get $`2`$ and add to out.

In the end returns $`10`$

## 5. 效能量測

Both $`p(x)`$ and $`q(x)`$ having 100 terms.

Adding took `0.0066ms`

Mutiplying took `3.4031ms`

Evaluating $`p(x)`$ took `0.011ms`


## 6. 心得討論

Not really sure if the implementation is optimized,

Also the implementation on overlaoding cin(>>) haves some inconvenience,

which I'm referring to the needing to clear cin bit state after finishing input each polynomial,

I just really don't want to store data in some temporary variable and pipe into the class,

which I can definitely do, but I think it kind of defeat the purpose of overloading cin.





