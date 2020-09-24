# 实现快排并改进
## 随机快排
	算法Random quicksort(S)
	输入 :无序数组S
	输出 :有序数组S
	1:   QuickSort(A, p, r)
	2:      If p<r   then
	3:         q = Rand_Partition(A, p, r)
	4:         QuickSort(A, p, q-1)
	5:         QuickSort(A, q+1, r)
	6:   Rand_Partition(A, p, r)
	7:      i=Random(p, r)
	8:      swap(A[r], A[i])
	9:      x=A[r]
	10:    i=p-1
	11:    for j=p to r-1
	12:       If   A[j]<=x   then
	13:          i=i+1, swap(A[i], A[j])
	14:    swap(A[i+1], A[r])
	15:    return i+1
##### 对应源码
	void swap_int(int *a, int *b) {
		if (*a != *b) {
			int temp;
			temp = *a;
			*a = *b;
			*b = temp;
		}	
	}
	
	int rand_partition(int *A, int p, int r) {
		srand((unsigned)time(0));
		int i = my_generate_node(p, r+1);
		swap_int(&A[r], &A[i]);
		int x = A[r];
		i = p - 1;
		for (int j = p; j < r; j++) {
			if (A[j] <= x) {
				i++;
				swap_int(&A[i], &A[j]);
			}
		}
		swap_int(&A[i + 1], &A[r]);
		return i + 1;		
	}
## 三路快排
	算法Trple sort(S)
	输入 :无序数组S
	输出 :有序数组S
	1:  设p为S的最小下标，r为S的最大下标
	2:   从[p, r]中随机选一个元素作为划分标准v
	3:   If 当前i指向的元素==v   then   i←i+1
	4:   If 当前i指向的元素<v   then   swap(S[lt+1], S[i]), lt←lt+1, i←i+1
	5:   If 当前i指向的元素>v   then   swap(S[gt-1], S[i]), gt←gt-1, i←i+1
	6:   If   gt==i   then swap(S[lt], S[p]), lt←lt-1
	7:   不断递归，重复第1-6步
![](https://github.com/HuiyanWen/quicksort/blob/master/pic/%E4%B8%89%E8%B7%AF%E5%BF%AB%E6%8E%92.png)
## 实验结果
##### 1.随机快排运行结果(横轴为数据集的元素重复率，纵轴为排序时间)
![双路快排](https://github.com/HuiyanWen/quicksort/blob/master/pic/%E9%9A%8F%E6%9C%BA%E5%BF%AB%E6%8E%92%E7%BB%93%E6%9E%9C.png)

##### 2.三路快排和系统库函数运行结果对比(对比的库函数为qsort)
![](https://github.com/HuiyanWen/quicksort/blob/master/pic/%E4%B8%89%E8%B7%AF%E5%BF%AB%E6%8E%92%E6%80%A7%E8%83%BD%E5%AF%B9%E6%AF%94.png)

## 总结
在数据集中元素重复较少时，三路快排和随机快排的区别不明显，当重复元素较多时，运行时间和空间有显著差异。造成这种现象的原因主要是随机快排中无法处理大量的重复元素，会造成递归树不平衡，导致递归层次多，速度慢，占据空间大。再加入了=v后，进化成三路快排，可有效解决此问题。对比qsort函数，本实验改进的三路快排具有与之几乎一样的运行时间，优化结果理想，同时可以猜测该函数可能采用了类似的处理方式。
