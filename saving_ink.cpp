#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct cost {
	int m;
	int n;
	float d;
};
/*
* Description: Bubble sort algorithm - To sort them in the order of less cost.
* Input: Struct array to sort, The length of struct 'distance'
* Output: void
*/
void bubble_sort(struct cost* distance, int k) {
	struct cost temp;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k - 1; j++) {
			if (distance[j].d > distance[j + 1].d) {
				temp = distance[j];
				distance[j] = distance[j + 1];
				distance[j + 1] = temp;
			}
		}
	}
}
/*
* Description: Kruscal algorithm
* Input: The number of coordinates, array of x-coodinate and y-coordinate in unconnected graph
* Output: Minimum weight
*/
float kruskal(int n, float** arr) {
	int distance_n, k = 0; //index of the distance
	distance_n = n * (n - 1) / 2; //Store the expected number of distances
	struct cost* distance = (struct cost*)malloc(sizeof(struct cost) * distance_n); //Array to store the distance

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			distance[k].m = i;
			distance[k].n = j;
			distance[k].d = sqrt(pow(arr[i][0] - arr[j][0], 2) + pow(arr[i][1] - arr[j][1], 2));
			k++;
		}
	}

	bubble_sort(distance, k);

	int* set = (int*)malloc(sizeof(int) * n); //To store the set
	for (int i = 0; i < n; i++) {
		set[i] = n;
	}

	float cost = 0.0;
	int set_num = 0; //index of the set
	for (int i = 0; i < k; i++) {
		int n1 = distance[i].m;
		int n2 = distance[i].n;
		if (set[n1] == n && set[n2] == n) { //When both node are not connected 
			set[n1] = set_num;
			set[n2] = set_num;
			set_num++;
		}
		else if (set[n1] == n || set[n2] == n) { //When only one node is connected
			if (set[n1] == n) { //n1 node is not connected
				set[n1] = set[n2];
			}
			else { //n2 node is not connected
				set[n2] = set[n1];
			}
		}
		else if (set[n1] != set[n2]) { //Both nodes are connected, but when the set is different
			int n2_temp;
			for (int j = 0; j < k; j++) {
				if (set[j] == n2_temp) {
					set[j] = set[n1];
				}
			}
		}
		else {
			continue;
		}
		cost += distance[i].d;
	}
	return cost;
}
int main() {
	int n; //Number of edges
	float result; //Final result (Minimum cost)
	float** arr; //To store the edge coordinates
	scanf("%d", &n);
	arr = (float**)malloc(sizeof(float*) * n);

	for (int i = 0; i < n; i++) {
		arr[i] = (float*)malloc(sizeof(float) * 2);
	}
	for (int i = 0; i < n; i++) {
		scanf("%f", &arr[i][0]);
		scanf("%f", &arr[i][1]);
	}

	result = kruskal(n, arr);
	printf("%.2f", result);
}