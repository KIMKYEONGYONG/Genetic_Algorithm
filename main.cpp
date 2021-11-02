// Genetic Algorithm - ������ �˰���

#include <stdio.h>
#include <random>
#include <algorithm>
#include <vector>
using namespace std;


int targetFunction(int x){
	// ��ǥ���� �˰� ���ִ� �Լ�
	return -x* x + 38 * x + 80;
}

vector<int> candidate_x(int candi = 4){
	// �ĺ���

	// �õ尪�� ��� ���� random_device ����.
	random_device rd;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	mt19937 gen(rd());

	// 0 ���� 31���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
	uniform_int_distribution<int> dis(0, 31);


	vector<int> result;

	while (result.size() < candi){

		int random = dis(gen);

		/*
		Vector vaule find - ���� �� ã�� ���
		if (any_of(data_types.begin(), data_types.end(), [&](const string& elem) { return elem == element_to_check; })) {
			printf("%s is present in the vector\n", element_to_check.c_str());
		}
		*/
		// �ߺ�����
		if (!any_of(result.begin(), result.end(), [&](const int& elem) { return elem == random; })){
			/// printf("���� ���� %d \n", random);
			result.push_back(random);
		}
		//else{
		//	printf("���� ���� %d \n", random);
		//}
	}

	return result;
}


int main(){

	const int size = 4;

	// Step1. ���� ����

	// �ĺ����� x
	vector<int> result = candidate_x(size);

	vector<int> ���յ�;
	int sum = 0;
	float avg = 0.0f;

	for (int i = 0; i < size; i++){
		���յ�.push_back(targetFunction(result.at(i)));
		sum += targetFunction(result.at(i));
	}
	avg = (float)sum / (float)size;

	vector<int> �귿; // ���� ����
	for (int i = 0; i < size; i++){
		float test = (float)���յ�.at(i) / (float)sum;
		�귿.push_back( test * 100.0);
	}

	//  TODO : 100�۰� �ƴϾ ������ ����? , ���� ������ �ִٸ�, 100�۷� ����� ���
	for (int i = 0; i < size; i++){
		printf("���յ� = %d  �귿 = %d \n", ���յ�.at(i), �귿.at(i));
	}
	return 0;
}