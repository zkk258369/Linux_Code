#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include <algorithm>
#include<map>
#include<time.h>
#include<limits.h>
using namespace std;

typedef struct Node
{
	int x;
	int y;
	Node(int a, int b) :x(a), y(b) {}
	friend bool operator<(const Node& a, const Node& b);
}Node;

inline bool operator<(const Node &a, const Node &b)
{
	return a.y > b.y;
}


class Topk
{
public:
	Topk(int _k) :k(_k) {}

	void insert(const Node& value)
	{
		if (pque.size() < k)
		{
			pque.push(value);
		}
		else if(value.y > pque.top().y)
		{
			pque.pop();
			pque.push(value);
		}
	}

	void print(vector<Node>& vec)
	{
		while (!pque.empty())
		{
			vec[pque.size() - 1] = pque.top();
			pque.pop();
		}
	}
private:
	int k;
	// 最小堆
	priority_queue<Node> pque; 
};

void Create1000w(int number_count)
{
	clock_t start_time = clock();
	srand(unsigned(time(0)));
	int max = 1047483648;
	int min = -1047483648;
	FILE* file = freopen("data1000w.txt", "w", stdout);
	if (nullptr == file)
	{
		fprintf(stdout, "open file error");
	}
	else
	{
		for (int i = 0; i < number_count; i++)
		{
			int tmp = rand() + min;
			cout << tmp << " ";
		}
	}
	fclose(file);
	freopen("/dev/tty", "w", stdout);

	cout << "elapsed time:" << double(clock() - start_time) / CLOCKS_PER_SEC << 's' << endl;
}

void Divide()
{
	char pathi[20] = "data1000w.txt";
	fstream ifile(pathi, ios::in);
	while (!ifile.eof())
	{
		int num;
		ifile >> num;
		int index = abs(num % 100);
		char patho[200] = { 0 };
		sprintf(patho, "/home/zkk/myCode/20200607bigdata/disdata/%d.txt", index);
		fstream ofile(patho, ios_base::out | ios_base::app);
		ofile << num << " ";
		ofile.close();
	}
	ifile.close();
}

int main()
{
	int number_count = 10000000;
	int k = 1000;
	vector<Node> result;
	

	clock_t start_time = clock();
	// 创建1000w数据
	//Create1000w(number_count);

	// 将1000w数据划分在100个文件中
	//Divide();

	// 利用hashmap对小文件中的数据进行统计,并将数据放入topk中
	// 数据-个数
	//map<int, int> hashmap;

	Topk topk(k);
	int i = 0;
	int tmp;
	while (i < 1)
	{
		map<int, int> hashmap;
		char path[200] = { 0 };
		sprintf(path, "/home/zkk/myCode/20200607bigdata/disdata/%d.txt", i);
		fstream ifile(path, ios_base::in);
		while (!ifile.eof())
		{
			ifile >> tmp;
			if (hashmap.count(tmp) > 0)
			{
				hashmap[tmp] += 1;
			}
			else
			{
				hashmap[tmp] = 1;
			}
		}
        ifile.close();
		map<int, int>::iterator it = hashmap.begin();
		for (; it != hashmap.end(); it++)
		{
			topk.insert(Node(it->first, it->second));
		}
        i++;
	}

	topk.print(result);
	char resultpath[200] = "/home/zkk/myCode/20200607bigdata/result.txt";
	fstream ofile(resultpath, ios_base::out);
	i = 0;
	ofile << "Rank \t number \t count" << endl;
	while (i < k)
	{
		ofile << i << "\t" << result[i].x << "\t" << result[i].y << endl;
		i++;
    }
    ofile.close();

	cout << "elapsed time:" << double(clock() - start_time) / CLOCKS_PER_SEC << 's' << endl;

	return 0;
}
