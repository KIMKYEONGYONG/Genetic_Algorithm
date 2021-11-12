// Genetic Algorithm - ������ �˰���

#include "main.h"

// ��ǥ���� �˰� ���ִ� �Լ�
int targetFunction(int x){
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

		// �ߺ�����
		if (!any_of(result.begin(), result.end(), [&](const int& elem) { return elem == random; })){
			result.push_back(random);
		}
	}

	return result;
}

// �귿 �����ϴ� �Լ�
vector<int> select_Roulette(const vector<int>& x, int sum , int size = 4){

	// ���Ϳ� �־ �ϴ� ��� TODO. �� ���� ��� �����غ���
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
		// �ĺ��ذ� 1���� ���õǵ��� �ߺ�üũ
		if (!any_of(result.begin(), result.end(), [&](const int& elem) { return elem == input.at(random); })){
		//if (count(result.begin(), result.end(), input.at(random)) < size / 2){
			result.push_back(input.at(random));
		}
	}

	return result;
}

// ���� ����
vector<int> cross(const vector<int>& �ĺ���_input, const vector<int>& roulette, int size = 4){

	// step1. �����ϱ�
	vector<int> cross_result;
	int front, end, cross_value = 0;
	front = (�ĺ���_input.at(roulette.at(0)) & 0x18);
	end = (�ĺ���_input.at(roulette.at(1)) & 0x7);
	cross_value = front | end;

	// ù��° �ĺ��� ��������
	if ((cross_value & (1 << 3)) == 0){
		cross_value = cross_value | (1 << 3);
	}
	else{
		cross_value = cross_value & ~(1 << 3);
	}
	cross_result.push_back(cross_value);

	front = (�ĺ���_input.at(roulette.at(1)) & 0x18);
	end = (�ĺ���_input.at(roulette.at(0)) & 0x7);
	cross_value = front | end;
	cross_result.push_back(cross_value);

	front = (�ĺ���_input.at(roulette.at(2)) & 0x18);
	end = (�ĺ���_input.at(roulette.at(3)) & 0x7);
	cross_value = front | end;
	cross_result.push_back(cross_value);

	front = (�ĺ���_input.at(roulette.at(3)) & 0x18);
	end = (�ĺ���_input.at(roulette.at(2)) & 0x7);
	cross_value = front | end;
	cross_result.push_back(cross_value);
	

	return cross_result;
}

int main(){

	const int size = 4;


	// Step1. ���� ����

	// �ĺ����� x
	vector<int> �����ĺ� = candidate_x(size);

	printf("�����ĺ� Ȯ�� \n");

	for (int i = 0; i < size; i++){
		printf("%d ", �����ĺ�.at(i));
	}
	printf("\n----------------------------------------------\n");

	int �������յ� = 0;
	int �������յ� = 0;
	float �������յ���� = 0.0f;
	vector<int> ���յ�;
	for (int j = 0; j < size; j++){
		int result = targetFunction(�����ĺ�.at(j));
		���յ�.push_back(result);
		�������յ� += result;
	}

	vector<int> roulette_result = select_Roulette(���յ�, �������յ�);
	vector<int> �����ĺ� = �����ĺ�;
	int �������յ� = �������յ�;

	printf("�귿 ��� Ȯ�� \n");

	for (int i = 0; i < size; i++){
		printf("%d ", roulette_result.at(i));
	}
	printf("\n----------------------------------------------\n");

	int count = 0;
	const int traning_count = 50000;
	for (int i = 2; i <= traning_count; i++){

		�������յ� = �������յ�;

		printf("�����ĺ� %d %d %d %d \n", �����ĺ�.at(0), �����ĺ�.at(1), �����ĺ�.at(2), �����ĺ�.at(3));
		�����ĺ� = cross(�����ĺ�, roulette_result);

		int result_sum = 0;
		���յ�.clear();
		for (int j = 0; j < size; j++){
			���յ�.push_back(targetFunction(�����ĺ�.at(j)));
			result_sum += targetFunction(�����ĺ�.at(j));
		}

		�������յ� = result_sum;
		roulette_result = select_Roulette(���յ�, �������յ�);

		printf("�����ĺ� %d %d %d %d \n", �����ĺ�.at(0), �����ĺ�.at(1), �����ĺ�.at(2), �����ĺ�.at(3));
		printf("�����ĺ� %d %d %d %d \n", �����ĺ�.at(0), �����ĺ�.at(1), �����ĺ�.at(2), �����ĺ�.at(3));
		printf("���� �ĺ� ���յ����� %d :", �������յ�);
		printf("���� �ĺ� ���յ����� %d :", �������յ�);
		printf("���� �ĺ� ���յ����� %d \n", �������յ�);
		printf("----------------------------------------------\n");

		if (�������յ� > �������յ�){
			�����ĺ� = �����ĺ�;
			�������յ� = �������յ�;
			count = 0;
		}

		if (�������յ� == �������յ�){
			count += 1;
		}



		if (count > sqrt(traning_count)){
			break;
		}
	


	}

	���յ�.clear();

	printf("���� �ĺ��� Ȯ�� \n");

	for (int j = 0; j < size; j++){
		int result = targetFunction(�����ĺ�.at(j));
		���յ�.push_back(result);
		printf("%d ", ���յ�.at(j));
		printf("%d ", �����ĺ�.at(j));
	}

	int max = ���յ�.at(0);
	int index = 0;
	for (int j = 0; j < size; j++){
		if (max < ���յ�.at(j)) {
			max = ���յ�.at(j);
			index = j;
		}
	}

	printf("\n");

	printf("�ִ밪 �ĺ��� Ȯ�� %d \n", �����ĺ�.at(index));

	return 0;
}