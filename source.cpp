#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>

using namespace std;

struct subject
{
	double x;
	double y;
	double fit;
	double P;
};

double function(const double& x, const double& y)
{
	return 1 / (1 + x * x + y * y);
}

bool mutation()
{
	double b;
	b = (double)rand() * 100 / RAND_MAX;
	return(b < 25);
}

double newpopulation(const double& gen)
{
	return gen * 0.8;
}

double P(const double& f1, const double& f2, const double& f3, const double& f4)
{
	return(f1 / f1 + f2 + f3 + f4);
}

int num(const double& p1, const double& p2, const double& p3, const double& p4)
{
	double erase;
	erase = (double)rand() * (4 - p1 - p2 - p3 - p4) / RAND_MAX;
	if (erase < p1) return 0;
	if (erase > p1&& erase < (p1 + p2)) return 1;
	if (erase > (p1 + p2) && erase < (p1 + p2 + p3)) return 2;
	if (erase > (p1 + p2 + p3) && erase < (p1 + p2 + p3 + p4)) return 3;
}

int main()
{
	double x1 = -2, x2 = 2, y1 = -2, y2 = 2, sum = 0  ;
	int n = 1;
	vector<subject> sub(4);
	for (auto i = 0; i < 4; i++)
	{
		sub[i].x = (double)rand() * (abs(x1) + abs(x2)) / RAND_MAX + x1;
		sub[i].y = (double)rand() * (abs(y1) + abs(y2)) / RAND_MAX + y1;
		sub[i].fit = function(sub[i].x, sub[i].y);
		sum += (double)sub[i].fit;
	}
	sort(sub.begin(), sub.end(), [](auto a, auto b) { return a.fit < b.fit; });
	cout << "Start population" << endl;
	cout << "    x       y    f(x,y)" << endl;
	for (auto i : sub)
	{
		cout << fixed << setprecision(4) << setw(7) << i.x << " " << setw(7) << i.y << " " << setw(7) << i.fit << " " << endl;
	}
	sum /= 4;
	cout << "max: " << sub[3].fit << " average: " << sum << endl << endl;

	while (n <= 40)

	{

		sub[0].P = P(sub[0].fit, sub[1].fit, sub[2].fit, sub[3].fit);
		sub[1].P = P(sub[1].fit, sub[0].fit, sub[2].fit, sub[3].fit);
		sub[2].P = P(sub[2].fit, sub[1].fit, sub[0].fit, sub[3].fit);
		sub[3].P = P(sub[3].fit, sub[1].fit, sub[2].fit, sub[0].fit);

		int i = num(sub[0].P, sub[1].P, sub[2].P, sub[3].P);

		sub.erase(sub.begin() + i);
		sub.push_back({});

		vector <subject> sub_copy = sub;
		sub[0].x = sub_copy[2].x;
		sub[1].x = sub_copy[2].x;
		sub[2].x = sub_copy[0].x;
		sub[3].x = sub_copy[1].x;
		sub[0].y = sub_copy[1].y;
		sub[1].y = sub_copy[0].y;
		sub[2].y = sub_copy[2].y;
		sub[3].y = sub_copy[2].y;

		for (auto i = 0; i < 4; i++)

		{
			if (mutation) sub[i].x = newpopulation(sub[i].x);
			if (mutation) sub[i].y = newpopulation(sub[i].x);
		}
		for (auto i = 0; i < 4; i++) sub[i].fit = function(sub[i].x, sub[i].y);

		sum = 0;
		cout << n++ << " population: " << endl;
		cout << "    x       y    f(x,y)" << endl;
		sort(sub.begin(), sub.end(), [](auto a, auto b) { return a.fit < b.fit; });

		for (auto i : sub)
		{
			cout << fixed << setprecision(4) << setw(7) << i.x << " " << setw(7) << i.y << " " << setw(7) << i.fit << " " << endl;
			sum += i.fit;
		}
		sum /= 4;
		cout << "max: " << sub[3].fit << " middlepoint: " << sum << endl << endl;
	}
	system("pause");
	return 0;
}
