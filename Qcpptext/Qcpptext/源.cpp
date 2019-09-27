#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	bool Find(int target, vector<vector<int> > array) {
		// array�Ƕ�ά���飬����û���пղ���
		int rows = array.size();
		int cols = array[0].size();
		int i = rows - 1, j = 0;//���½�Ԫ������
		while (i >= 0 && j < cols) {//ʹ�䲻�������鷶Χ
			if (target < array[i][j])
				i--;//���ҵ�Ԫ�ؽ��٣�������
			else if (target > array[i][j])
				j++;//����Ԫ�ؽϴ�������
			else
				return true;//�ҵ�
		}
		return false;
	}
};


int main()
{

	vector<vector<int> > array;
	int mNum = 0;
	vector<int> array2;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			array2.push_back(mNum++);
			//cout << array2[j] << endl;
		}
		array.push_back(array2);
		array2.erase(array2.begin(), array2.end());
	}

	for (vector<vector<int> >::iterator it = array.begin(); it != array.end(); it++)
	{

		for (vector<int>::iterator it2 = (*it).begin(); it2 < (*it).end(); it2++)
			cout << *it2 << "";
	}
	cout << "" << endl;
	Solution sol;
	bool bu = sol.Find(2, array);
	cout << bu << endl;
	return 0;
}