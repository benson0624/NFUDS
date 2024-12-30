# Polynomial With Circular List

## 1. 解題說明

Implement polynomial class in a circular list form as shown in its ADT,

including overloading operator `cout(<<)`, `cin(>>)`, `add(+)`, `subtract(-)`, `multiply(*)`, `assign(=)` and `evaluate`,

also should have a constructor, copy constrcutor and destructor.

For example:

$`p(x)=2x^5+3x^4+4x^3+8x^2+7x+9`$

$`q(x)=3x^4+7x^2+8x+19`$

Refer to implementation in `Source.cpp`, the copy constructor:

```cpp
Polynomial(const Polynomial& x) 
{
	Node<Term>* cur = x.poly.headerNode->link;
	while (cur != x.poly.headerNode)
	{
		poly.headerNode->data.exp = -1;
		this->NewTerm(cur->data.coef, cur->data.exp);
		cur = cur->link;
	}
}

```

Refer to implementation in `Source.cpp`, the destructor:

```cpp
~Polynomial()
{
	Node<Term>* cur = poly.headerNode->link;
	Node<Term>* deleteNode;
	while (cur != poly.headerNode)
	{
		deleteNode = cur;
		cur = cur->link;
		poly.RetNode(deleteNode);	
	}
	poly.RetNode(cur); //return the header node
}

```

Refer to implementation in `Source.cpp`, the assign operator:

```cpp
Polynomial operator=(const Polynomial& other)
{
	Polynomial out;
	Node<Term>* cur = other.poly.headerNode->link;
	while (cur != other.poly.headerNode)
	{
		poly.headerNode->data.exp = -1;
		this->NewTerm(cur->data.coef, cur->data.exp);
		cur = cur->link;
	}
	return out;
}

```

The result of $`p(x)+q(x)`$ should be:

$`2x^5+6x^4+4x^3+15x^2+15x+28`$

Refer to implementation in `Source.cpp`, the add implementation:

```cpp
Polynomial operator+(const Polynomial& other)
{
	Node<Term>* curA = this->poly.headerNode->link;
	Node<Term>* curB = other.poly.headerNode->link;
	Polynomial out;
	int biggest;
	if (curA->data.exp > curB->data.exp)
		biggest = curA->data.exp;
	else
		biggest = curB->data.exp;

	while (biggest >= 0)
	{
		int c = 0;

		if (curA->data.exp == biggest)
		{
			c += curA->data.coef;
			curA = curA->link;
		}
		if (curB->data.exp == biggest)
		{
			c += curB->data.coef;
			curB = curB->link;
		}		
		if (c != 0)
		{
			out.NewTerm(c, biggest);
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
Polynomial operator*(const Polynomial& other)
{
	Polynomial out;
	Node<Term>* curA = this->poly.headerNode->link;
	Node<Term>* curB = other.poly.headerNode->link;
	float cTemp = 0;
	int eTemp = 0;
	bool flag = true;
	while(curA != this->poly.headerNode)
	{
		Polynomial temp;
		while (curB != other.poly.headerNode)
		{
			cTemp = curA->data.coef * curB->data.coef;
			eTemp = curA->data.exp + curB->data.exp;
			temp.NewTerm(cTemp, eTemp);
			curB = curB->link;
		}
		if (flag)
		{
			out = temp;
			flag = false;
		}
		else
		{
			out = out + temp;
		}			
		curB = other.poly.headerNode->link;
		curA = curA->link;
	}
	return out;
}
```

The result of $`p(2.5)`$ should be:

$`451.5`$

Refer to implementation in `Source.cpp`, the eval implementation:

```cpp
float Evaluate(const float f)
{
	Node<Term>* cur = poly.headerNode->link;
	float out = 0;
	while (cur != poly.headerNode)
	{
		out += cur->data.coef * pow(f, cur->data.exp);
		cur = cur->link;
	}
	return out;
}
```

When inputting data to class,should use overloaded cin(>>),

Refer to implementation in `Source.cpp`, the cin overloading implementation:

```cpp
istream& operator>>(istream& is, Polynomial& x) {
	int cTemp;
	int eTemp;
	is >> cTemp >> eTemp;
	x.NewTerm(cTemp, eTemp);
	return is;
}
```

When representing the result should use overloaded cout(<<),

Refer to implementation in `Source.cpp`, the cout overloading implementation:

```cpp
ostream& operator<<(ostream& os, Polynomial& x) {

	Node<Term>* cur = x.poly.headerNode->link;

	while (cur != x.poly.headerNode )
	{
		if (cur->data.exp == 0)
		{
			os << cur->data.coef;
		}
		else if (cur->data.exp == 1)
		{
			if (cur->data.coef == 1)
				os << "x";
			else
				os << cur->data.coef << "x";
		}
		else
		{
			if (cur->data.coef == 1)
				os << "x^" << cur->data.exp;
			else
				os << cur->data.coef << "x^" << cur->data.exp;
		}
		if (cur != x.poly.last) os << " + ";
		cur = cur->link;
	}
	return os;
}
```

## 2. 演算法設計與實作

```cpp
int main()
{
	Polynomial p;

	int n;
	cin >> n;
	
	while (n--)
	{
		cin >> p;
	}
	Polynomial q(p); //copy the same data to save my time
	cout << p << endl;
	cout << q << endl;
	Polynomial r = p + q;
	Polynomial s = p * q;
	cout << r << endl;
	cout << s << endl;
	cout << s.Evaluate(2.5f);

	system("Pause");
}
```

## 3. 效能分析

### Add

- $`f(m+n) = O(n)`$, suppose $`n > m`$
- $`S(P) = 3+n`$, n is the amount of total array length

### Mult

- $`f(m*n) = O(n^2)`$, suppose $`n > m`$
- $`S(P) = 3+n^2`$, suppose $`n > m`$

### Eval

- $`f(n) = O(n)`$
- $`S(P) = 2`$

## 4. 測試與過程

### Input

```plain
3
4 4
3 3
2 2
```

### Output

```plain
p(x)= 4x^4 + 3x^3 + 2x^2
q(x)= 4x^4 + 3x^3 + 2x^2
p(x)+q(x)=r(x)= 8x^4 + 6x^3 + 4x^2
p(x)+q(x)=s(x)= 16x^8 + 12x^7 + 8x^6 + 16x^8 + 24x^7 + 17x^6 + 6x^5 + 16x^8 + 12x^7 + 16x^6 + 6x^5 + 4x^4
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

Adding took `0.0035ms`

Mutiplying took `0.01ms`

Evaluating $`p(x)`$ took `0.005ms`


## 6. 心得討論

Using a circular list to implement things is kind of harder then normal implementation,

during programming phase there's always some weird nullptr problem,

but besides that it's quite simple,

also we can tell that this is actually quite efficient than we did on HW2,

knowing that some data structure technique is definetely better.







