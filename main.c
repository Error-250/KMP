#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
	KMP算法
	思路: 匹配失败时, 返回next所值位置重新尝试
	例子:
	abacab
	对于next:
	000100
	原因:
	假设在第二个a匹配失败, 此时不应回到1而是0,已经匹配的是ab, 没有可以重叠的部分
	假设在c处匹配失败, 应回到1, 此时匹配到的为aba,
	aba?
	  aba 这样重叠是可以的, 因为?处不等于c, 但不一定不等于b
	假设在最后一个b处匹配失败, 很多算法会让next为1, 事实上应该为0
	因为:
		abaca?
		    abacab 虽然看上去可以这样重叠, 事实上?不等于b, 这样匹配的结果注定是失败的
	理应回到0
	过程:
	    a b a c a b
初始化  0 0 0 0 0 0
	state = 0
	| |
	v v
	a b a c a b
	0 0 0 0 0 0
	
	state = 0 (此时比较两指针对应值相同, 将要修改state)
	|   |
	v   v
	a b a c a b
	0 0 0 0 0 0
	
	state = 1 (此时state为1, 两指针对应值不同, next填充第一个指针位置)
	  |   |
	  v   v
	a b a c a b
	0 0 0 1 0 0
	
	state = 0
	|       |
	v       v
	a b a c a b
	0 0 0 1 0 0
	
	state = 1
	  |       |
	  v       v
	a b a c a b
	0 0 0 1 0 0
*/

int* getNext(const char *target) {
	int *next;
	int head, current, len, state;
	len = strlen(target);
	next = (int *)malloc(sizeof(int) * len);
	head = 0;
	current = 1;
	next[0] = 0;
	memset(next, 0, len * sizeof(int));
	state = 0; // 未匹配状态
	// 遍历target产生next数组
	// 原理, 尽可能利用已经匹配的结果进行错位
	while(current < len) {
		if(target[head] == target[current]) {
			state = 1;
			head++;
			current++;
		}else {
			if(state == 1) {
				next[current] = head;
			}
			else {
				// next[current] = next[head];
				current++;
			}
			head = 0;
			state = 0;
		}
	}
	return next;
}
/*
	测试Next数组
*/
void testNext(const char *target ){
	int *next, i;
	int len = strlen(target);
	next = getNext(target);
	for(i = 0;i < len;i++) {
		printf("%d ", next[i]);
	}
	printf("\n");
}

int KMP(const char *source, const char *target) {
	int *next;
	// 获得next数组
	next = getNext(target);
	int source_index = 0;
	int source_len = strlen(source);
	int target_index = 0;
	int target_len = strlen(target);
	while(source_index < source_len && target_index < target_len) {
		if(source[source_index] == target[target_index]) {
			source_index++;
			target_index++;
		}else {
			//跳过
			if(target_index == 0)
				source_index++;
			else {
				printf("Skip %d to %d for %c where %d\n", target_index, next[target_index - 1], source[source_index], source_index);
				target_index = next[target_index];
			}
		}
	}
	if(source_index == source_len)
		return -1;
	return source_index - target_len;
}

int main(void) {
	testNext("abcacabcab");
	// printf("%d\n", KMP("abcdabcabdabcabcabcabcdabc","abcabcabcd"));
	return 0;
}