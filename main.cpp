// Genetic Algorithm - 유전자 알고리즘

#include <stdio.h>
#include <random>
#include <algorithm>
#include <vector>
using namespace std;


int targetFunction(int x){
	// 목표값을 알게 해주는 함수
	return -x* x + 38 * x + 80;
}

vector<int> candidate_x(int candi = 4){
	// 후보해

	// 시드값을 얻기 위한 random_device 생성.
	random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	mt19937 gen(rd());

	// 0 부터 31까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	uniform_int_distribution<int> dis(0, 31);


	vector<int> result;

	while (result.size() < candi){

		int random = dis(gen);

		/*
		Vector vaule find - 벡터 값 찾는 방법
		if (any_of(data_types.begin(), data_types.end(), [&](const string& elem) { return elem == element_to_check; })) {
			printf("%s is present in the vector\n", element_to_check.c_str());
		}
		*/
		// 중복제거
		if (!any_of(result.begin(), result.end(), [&](const int& elem) { return elem == random; })){
			/// printf("값이 없다 %d \n", random);
			result.push_back(random);
		}
		//else{
		//	printf("값이 존재 %d \n", random);
		//}
	}

	return result;
}


int main(){

	const int size = 4;

	// Step1. 선택 연산

	// 후보해의 x
	vector<int> result = candidate_x(size);

	vector<int> 적합도;
	int sum = 0;
	float avg = 0.0f;

	for (int i = 0; i < size; i++){
		적합도.push_back(targetFunction(result.at(i)));
		sum += targetFunction(result.at(i));
	}
	avg = (float)sum / (float)size;

	vector<int> 룰렛; // 원반 면적
	for (int i = 0; i < size; i++){
		float test = (float)적합도.at(i) / (float)sum;
		룰렛.push_back( test * 100.0);
	}

	//  TODO : 100퍼가 아니어도 문제가 없나? , 만약 문제가 있다면, 100퍼로 만드는 방법
	for (int i = 0; i < size; i++){
		printf("적합도 = %d  룰렛 = %d \n", 적합도.at(i), 룰렛.at(i));
	}
	return 0;
}