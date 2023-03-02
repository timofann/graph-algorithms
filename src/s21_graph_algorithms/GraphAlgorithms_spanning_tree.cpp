#include "GraphAlgorithms.h"
#include <vector>
#include <stack>
#include <iostream>

using namespace s21;

std::vector<std::vector<int>> GraphAlgorithms::
getLeastSpanningTree(Graph &graph) {
	std::vector<std::vector<int>> tree = std::vector<std::vector<int>>(
			graph.vertices_cnt_, std::vector<int>(graph.vertices_cnt_, 0));
	std::vector<bool> is_traversed = std::vector<bool>(graph.vertices_cnt_, false);
	int from;
	int to;

	int min_distance = 1;
	int current_vertex = 0;
	is_traversed[current_vertex] = true;
	while (min_distance > 0) {
		min_distance = 0;
		for (int i = 0; i < graph.vertices_cnt_; ++i)
			if (is_traversed[i]) {
				for (int j = 0; j < graph.vertices_cnt_; ++j)
					if (!is_traversed[j] && (min_distance == 0 || min_distance > graph.matrix_[i][j])) {
						min_distance = graph.matrix_[i][j];
						from = i;
						to = j; }}
		if (min_distance) {
			is_traversed[to] = true;
			tree[from][to] = min_distance;
			tree[to][from] = min_distance;
		}
	}
	return tree;
}