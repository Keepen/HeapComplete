#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//二叉堆：用顺序表来存储完全二叉树
//大堆：根结点>左孩子 && 根节点>右孩子
typedef struct Heap {
	int* arr;
	int size;	//用来记录有效元素的个数
	int capacity;//容量
}Heap;

//1.堆的初始化
Heap* heapInit(Heap* heap) {
	int capacity;
	printf("请输入要建的堆的元素个数：");
	scanf("%d", &capacity);
	heap->arr = (int*)malloc(sizeof(int)*capacity);
	heap->capacity = capacity;
	heap->size = capacity;
	printf("请输入堆的元素：");
	for (int i = 0; i < heap->size; ++i) {
		scanf("%d", &heap->arr[i]);
		//heap->arr[i] = getchar();
	}
	return heap;
}

//2.堆的向下调整：小堆
//条件：只有一个位置不满足堆的性质，其余位置均满足堆的性质
Heap* adjustDown(Heap* heap, int index) {
	Heap* ph = heap;
	while (1) {
		//记录有问题的元素的左右孩子下标
		//以及左右孩子中较小元素的下标
		int left = index * 2 + 1;
		int right = index * 2 + 2;
		int min = left;
		//判断是否是叶子结点，如果是，则不必判断，直接退出
		//由于是完全二叉树，没有左孩子，一定没有右孩子，即为叶子结点
		if (left >= ph->size) {
			break;
		}
		//不是叶子结点,判断有无右孩子
		//如果有右孩子，并且右孩子比左孩子还小，就让最小值的下标更改为右孩子
		if (right < ph->size &&heap->arr[right] < ph->arr[left]) {
			min = right;
		}
		//如果满足堆的性质了，就退出
		if (ph->arr[index] <= ph->arr[min]) {
			break;
		}

		//开始进行交换
		int temp = ph->arr[index];
		ph->arr[index] = ph->arr[min];
		ph->arr[min] = temp;

		//更新index的值
		index = min;
	}
	return ph;
}

//3.向上调整
Heap* adjustUp(Heap* heap, int index) {
	Heap* ph = heap;
	while (1) {
		//找双亲结点，如果没有双亲结点就退出
		int parent = (index - 1) / 2;
		if (index == 0) {
			break;
		}
		//如果双亲结点已经满足堆的性质了，就退出
		if (ph->arr[parent] <= ph->arr[index]) {
			break;
		}
		//不满足条件，进行交换
		int temp = ph->arr[index];
		ph->arr[index] = ph->arr[parent];
		ph->arr[parent] = temp;

		//更新index的值
		index = parent;
	}
	return ph;
}

//4.建堆
//保证左右孩子都是堆了，向下调整即可
Heap* heapCreate(Heap* heap) {
	Heap* ph = heap;
	for (int i = 0; i < ph->size; ++i) {
		ph = adjustDown(ph, i);
	}
	return ph;
}

//5.从堆中弹出元素：每次弹出最小的,并保证弹出后仍旧保持堆的性质
Heap* heapPop(Heap* heap) {
	Heap* ph = heap;
	ph->arr[0] = ph->arr[ph->size - 1];
	ph->size--;
	ph = adjustDown(ph, 0);
	return ph;
}

//6.向堆中插入元素，并保证插入后，仍是堆
Heap* heapPush(Heap* heap) {
	Heap* ph = heap;
	printf("\n请输入要插入的元素：");
	int val;
	scanf("%d", &val);
	ph->size++;
	ph->arr[ph->size-1] = val;
	//向上调整
	ph = adjustUp(ph, ph->size - 1);
	return ph;
}

//7.打印堆中的元素
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