// Genetic Algorithm - 유전자 알고리즘

#include "main.h"

// 목표값을 알게 해주는 함수
int targetFunction(int x){
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

		// 중복제거
		if (!any_of(result.begin(), result.end(), [&](const int& elem) { return elem == random; })){
			result.push_back(random);
		}
	}

	return result;
}

// 룰렛 선택하는 함수
vector<int> select_Roulette(const vector<int>& x, int sum , int size = 4){

	// 벡터에 넣어서 하는 방법 TODO. 더 좋은 방법 생각해보기
	vector<int> input;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < x.at(i); j++){
			input.push_back(i);
		}
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, sum-1);

	vector<int> result;

	while (result.size() < size){
		int random = dis(gen);
		// 후보해가 1개만 선택되도록 중복체크
		if (!any_of(result.begin(), result.end(), [&](const int& elem) { return elem == input.at(random); })){
		//if (count(result.begin(), result.end(), input.at(random)) < size / 2){
			result.push_back(input.at(random));
		}
	}

	return result;
}

// 교차 연산
vector<int> cross(const vector<int>& 후보해_input, const vector<int>& roulette, int size = 4){

	// step1. 교차하기
	vector<int> cross_result;
	int front, end, cross_value = 0;
	front = (후보해_input.at(roulette.at(0)) & 0x18);
	end = (후보해_input.at(roulette.at(1)) & 0x7);
	cross_value = front | end;

	// 첫번째 후보해 돌연변이
	if ((cross_value & (1 << 3)) == 0){
		cross_value = cross_value | (1 << 3);
	}
	else{
		cross_value = cross_value & ~(1 << 3);
	}
	cross_result.push_back(cross_value);

	front = (후보해_input.at(roulette.at(1)) & 0x18);
	end = (후보해_input.at(roulette.at(0)) & 0x7);
	cross_value = front | end;
	cross_result.push_back(cross_value);

	front = (후보해_input.at(roulette.at(2)) & 0x18);
	end = (후보해_input.at(roulette.at(3)) & 0x7);
	cross_value = front | end;
	cross_result.push_back(cross_value);

	front = (후보해_input.at(roulette.at(3)) & 0x18);
	end = (후보해_input.at(roulette.at(2)) & 0x7);
	cross_value = front | end;
	cross_result.push_back(cross_value);
	

	return cross_result;
}

int main(){

	const int size = 4;


	// Step1. 선택 연산

	// 후보해의 x
	vector<int> 현재후보 = candidate_x(size);

	printf("현재후보 확인 \n");

	for (int i = 0; i < size; i++){
		printf("%d ", 현재후보.at(i));
	}
	printf("\n----------------------------------------------\n");

	int 현재적합도 = 0;
	int 이전적합도 = 0;
	float 현재적합도평균 = 0.0f;
	vector<int> 적합도;
	for (int j = 0; j < size; j++){
		int result = targetFunction(현재후보.at(j));
		적합도.push_back(result);
		현재적합도 += result;
	}

	vector<int> roulette_result = select_Roulette(적합도, 현재적합도);
	vector<int> 최적후보 = 현재후보;
	int 최적적합도 = 현재적합도;

	printf("룰렛 결과 확인 \n");

	for (int i = 0; i < size; i++){
		printf("%d ", roulette_result.at(i));
	}
	printf("\n----------------------------------------------\n");

	int count = 0;
	const int traning_count = 50000;
	for (int i = 2; i <= traning_count; i++){

		이전적합도 = 현재적합도;

		printf("이전후보 %d %d %d %d \n", 현재후보.at(0), 현재후보.at(1), 현재후보.at(2), 현재후보.at(3));
		현재후보 = cross(현재후보, roulette_result);

		int result_sum = 0;
		적합도.clear();
		for (int j = 0; j < size; j++){
			적합도.push_back(targetFunction(현재후보.at(j)));
			result_sum += targetFunction(현재후보.at(j));
		}

		현재적합도 = result_sum;
		roulette_result = select_Roulette(적합도, 현재적합도);

		printf("최적후보 %d %d %d %d \n", 최적후보.at(0), 최적후보.at(1), 최적후보.at(2), 최적후보.at(3));
		printf("현재후보 %d %d %d %d \n", 현재후보.at(0), 현재후보.at(1), 현재후보.at(2), 현재후보.at(3));
		printf("이전 후보 적합도의합 %d :", 이전적합도);
		printf("현재 후보 적합도의합 %d :", 현재적합도);
		printf("최적 후보 적합도의합 %d \n", 최적적합도);
		printf("----------------------------------------------\n");

		if (현재적합도 > 최적적합도){
			최적후보 = 현재후보;
			최적적합도 = 현재적합도;
			count = 0;
		}

		if (현재적합도 == 이전적합도){
			count += 1;
		}



		if (count > sqrt(traning_count)){
			break;
		}
	


	}

	적합도.clear();

	printf("최종 후보해 확인 \n");

	for (int j = 0; j < size; j++){
		int result = targetFunction(최적후보.at(j));
		적합도.push_back(result);
		printf("%d ", 적합도.at(j));
		printf("%d ", 최적후보.at(j));
	}

	int max = 적합도.at(0);
	int index = 0;
	for (int j = 0; j < size; j++){
		if (max < 적합도.at(j)) {
			max = 적합도.at(j);
			index = j;
		}
	}

	printf("\n");

	printf("최대값 후보해 확인 %d \n", 최적후보.at(index));

	return 0;
}