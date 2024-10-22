# Problem-1 Ackermann Function

## 1. 解題說明

Find solution for recursive and non-recursive ackermann function.

The rules for ackermann function is as follows:

$`A(m,n) = \begin{cases}n+1 & \mbox{if } m = 0 \\A(m-1, 1) & \mbox{if } n = 0 \\A(m-1, A(m, n-1)) & otherwise.\end{cases}`$


Refer to implementation in `problem1.cpp`, the recursive function:

```cpp
int ackermann_r(int m, int n)
{
	if (m == 0) return n + 1;
	if (n == 0) return ackermann_r(m - 1, 1);
	return ackermann_r(m - 1, ackermann_r(m, n - 1));
}
```

and non-recursive counterpart：

```cpp
int ackermann_nr(int m, int n)
{
	stack<int> tracker;
	tracker.push(m);

	while (!tracker.empty())
	{
		m = tracker.top();
		tracker.pop();

		if (m == 0)
		{
			n += 1;
		}
		else if (n == 0)
		{
			tracker.push(m - 1);
			n = 1;
		}
		else
		{
			tracker.push(m - 1);
			tracker.push(m);
			n -= 1;
		}
	}
	return n;
}
```
## 2. 演算法設計與實作

```cpp
int main()
{
	int m, n;
	cin >> m >> n; //Input m and n	
	cout << "Recursive:    " << ackermann_r (m, n) << endl; //Output for recusive solution
	cout << "Non-Recursive:" << ackermann_nr(m, n) << endl; //Output for non-recusive solution
}
```

## 2. 效能分析

- Due to the complexity and non primitive recursive nature of ackermann function, I can't find a definitive answer for it.

## 3. 測試與過程

### Input

```plain
3 3

```

### Output

```plain

Recursive:    61
Non-Recursive:61

```

### 驗證

This function terminate and returns output when $`m=0`$ recursively.

In the recursive one we can just write an easy recursive function by following the rule set,

On the other hand the non-recursive one, we need to keep track of m,

by pushing m onto a stack manually we can get the same answer as the recursive way.

I tried to write the structure as similar as the recursive one.

Which for example: 

$`A(1,1)`$

By the rule when $`m \not= 0`$ and $`n \not= 0`$ we can get $`A(0,A(1,0))`$,

when $`n=0`$ we can get $`A(0,A(0,1))`$,

when $`m=0`$ we can get $`A(0,2)`$,

and we can get our final result of $`3`$.



# Problem-2 Recursive Powerset

## 1. 解題說明

Find a recursive function to generate powerset.

A powerset is to find all possible subset of given set $`S`$

For example $`S={a,b,c}`$

The powerset of $`S`$ should be

$`{(),(a),(b),(c),(ab),(ac),(bc),(abc)}`$

Refer to implementation in `problem2.cpp`, the recursive function:

```cpp
void powerset(int n, string current, int index)
{
    // Output and return when n is equal to n
    if (index == n) {
        std::cout << "{" << current << "}" << std::endl;
        return;
    }
    // Using type cast to turn integer into char

    // Branch into a set containing current element
    powerset(n, current + char('a' + index), index + 1);
    // Branch into a set not containing current element
    powerset(n, current, index + 1);
}
```


## 2. 演算法設計與實作

```cpp
int main() 
{
    int n;
    cin >> n;
    // n represent the set from a to a+n-1
    powerset(n, "", 0);
}
```

## 2. 效能分析

- $`f(n)=O(2^{n})`$, this recursion split half every time.
- $`S(P)=n*2^{n}`$, the average size for subset is $`n/2`$, and we call the recursion $`2^{n}`$ times.
- $`T(n)=c*2^n `$, every time we call the function $`c`$, and we call the recursion $`2^{n}`$ times.

## 3. 測試與過程

### Input

```plain

3

```

### Output

```plain

{abc}
{ab}
{ac}
{a}
{bc}
{b}
{c}
{}

```

### 驗證

The function split into two parts,

One including the current subset, and one not including the current subset.

This recursion is very expensive on both time and space.

Which for example: 

Suppose $`n=2`$

We can see the function first start as p(2,"",0)`,

and we split into p(2,"a",1) and p(2,"",1),

then split into p(2,"ab",2), p(2,"a",2), p(2,"b",2) and p\left(2,"",2)

in the end we can get {(ab),(a),(b),()}

even when n is small like two we can already see the nature of this function being $`2^{n}`$
