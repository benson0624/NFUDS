#include <iostream>
#include <stack>

using namespace std;

//recursive solution for ackermann function
int ackermann_r(int m, int n)
{
	if (m == 0) return n + 1;
	if (n == 0) return ackermann_r(m - 1, 1);
	return ackermann_r(m - 1, ackermann_r(m, n - 1));
}

//non-recursive solution for ackermann function
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

int main()
{
	int m, n;
	cin >> m >> n;
	
	cout << "Recursive:    " << ackermann_r (m, n) << endl;
	cout << "Non-Recursive:" << ackermann_nr(m, n) << endl;
}
