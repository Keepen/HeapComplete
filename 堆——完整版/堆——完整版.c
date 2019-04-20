#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//����ѣ���˳������洢��ȫ������
//��ѣ������>���� && ���ڵ�>�Һ���
typedef struct Heap {
	int* arr;
	int size;	//������¼��ЧԪ�صĸ���
	int capacity;//����
}Heap;

//1.�ѵĳ�ʼ��
Heap* heapInit(Heap* heap) {
	int capacity;
	printf("������Ҫ���Ķѵ�Ԫ�ظ�����");
	scanf("%d", &capacity);
	heap->arr = (int*)malloc(sizeof(int)*capacity);
	heap->capacity = capacity;
	heap->size = capacity;
	printf("������ѵ�Ԫ�أ�");
	for (int i = 0; i < heap->size; ++i) {
		scanf("%d", &heap->arr[i]);
		//heap->arr[i] = getchar();
	}
	return heap;
}

//2.�ѵ����µ�����С��
//������ֻ��һ��λ�ò�����ѵ����ʣ�����λ�þ�����ѵ�����
Heap* adjustDown(Heap* heap, int index) {
	Heap* ph = heap;
	while (1) {
		//��¼�������Ԫ�ص����Һ����±�
		//�Լ����Һ����н�СԪ�ص��±�
		int left = index * 2 + 1;
		int right = index * 2 + 2;
		int min = left;
		//�ж��Ƿ���Ҷ�ӽ�㣬����ǣ��򲻱��жϣ�ֱ���˳�
		//��������ȫ��������û�����ӣ�һ��û���Һ��ӣ���ΪҶ�ӽ��
		if (left >= ph->size) {
			break;
		}
		//����Ҷ�ӽ��,�ж������Һ���
		//������Һ��ӣ������Һ��ӱ����ӻ�С��������Сֵ���±����Ϊ�Һ���
		if (right < ph->size &&heap->arr[right] < ph->arr[left]) {
			min = right;
		}
		//�������ѵ������ˣ����˳�
		if (ph->arr[index] <= ph->arr[min]) {
			break;
		}

		//��ʼ���н���
		int temp = ph->arr[index];
		ph->arr[index] = ph->arr[min];
		ph->arr[min] = temp;

		//����index��ֵ
		index = min;
	}
	return ph;
}

//3.���ϵ���
Heap* adjustUp(Heap* heap, int index) {
	Heap* ph = heap;
	while (1) {
		//��˫�׽�㣬���û��˫�׽����˳�
		int parent = (index - 1) / 2;
		if (index == 0) {
			break;
		}
		//���˫�׽���Ѿ�����ѵ������ˣ����˳�
		if (ph->arr[parent] <= ph->arr[index]) {
			break;
		}
		//���������������н���
		int temp = ph->arr[index];
		ph->arr[index] = ph->arr[parent];
		ph->arr[parent] = temp;

		//����index��ֵ
		index = parent;
	}
	return ph;
}

//4.����
//��֤���Һ��Ӷ��Ƕ��ˣ����µ�������
Heap* heapCreate(Heap* heap) {
	Heap* ph = heap;
	for (int i = 0; i < ph->size; ++i) {
		ph = adjustDown(ph, i);
	}
	return ph;
}

//5.�Ӷ��е���Ԫ�أ�ÿ�ε�����С��,����֤�������Ծɱ��ֶѵ�����
Heap* heapPop(Heap* heap) {
	Heap* ph = heap;
	ph->arr[0] = ph->arr[ph->size - 1];
	ph->size--;
	ph = adjustDown(ph, 0);
	return ph;
}

//6.����в���Ԫ�أ�����֤��������Ƕ�
Heap* heapPush(Heap* heap) {
	Heap* ph = heap;
	printf("\n������Ҫ�����Ԫ�أ�");
	int val;
	scanf("%d", &val);
	ph->size++;
	ph->arr[ph->size-1] = val;
	//���ϵ���
	ph = adjustUp(ph, ph->size - 1);
	return ph;
}

//7.��ӡ���е�Ԫ��
void heapPrint(Heap* heap) {
	printf("\n\n");
	for (int i = 0; i < heap->size; ++i) {
		printf("%d  ", heap->arr[i]);
	}
}

void test() {
	Heap heap;
	Heap* pH;
	pH = heapInit(&heap);
	heapPrint(pH);
	//pH = adjustDown(&heap,0);
	//heapPrint(pH);
	//pH = adjustUp(pH, 7);
	//heapPrint(pH);
	pH = heapCreate(pH);
	heapPrint(pH);
	pH = heapPop(pH);
	heapPrint(pH);
	pH = heapPush(pH);
	heapPrint(pH);
}

int main() {
	test();
	system("pause");
	return 0;
}