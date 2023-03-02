#include "GraphAlgorithms.h"
#include <math.h>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace s21;
#define Q_VAL 10000.0 // количество фермента, которое муравей может распределить по пути
#define ANTS_NUM 20 // количество муравьев в каждом городе
#define ALPHA 1.0 // степень влияния количества ферромона на выбор пути (0 - остальные муравьи безразличны, обычный жадный алгоритм: хватай, что поближе)
#define BETA 1.0 // степень влияния обратного расстояния на выбор пути (0 - игнорирование близости и дальности городов, реагируем только на ферромон)
#define RHO 0.3 // коэффициент забывчивости [0, 1] (1 - не обращаем внимания на других муравьёв, 0 - помним всё)


struct Ant {
	std::vector<bool> is_traversed;
	std::vector<int> traversed;
	int current_city;
	std::size_t length;
};

static std::vector<int>
euler_graph_check(Graph &graph) {
	std::vector<int> cities_to_start_from;
	return cities_to_start_from;
}

static void
restart_ants(const Graph &graph, std::vector<Ant>& ants) {
	for (int i = 0; i < ants.size(); ++i) {
		ants[i].current_city = i % ANTS_NUM;
		ants[i].traversed.push_back(i % ANTS_NUM);
		ants[i].is_traversed[i % ANTS_NUM] = true;
        ants[i].length = 0;
	}
}

static void
init_pheromone_lvl(const Graph &graph, std::vector<std::vector<double>>& pheromone_lvl) {
	for (int i = 0; i < graph.vertices_cnt_; ++i)
		for (int j = 0; j < graph.vertices_cnt_; ++j)
			if (graph.matrix_[i][j])
				pheromone_lvl[i][j] = 1;
}

static std::vector<int>
get_available_paths(const Graph &graph, const Ant& ant) {
	std::vector<int> available_paths;
	for (int i = 0; i < graph.vertices_cnt_; ++i)
		if (graph.matrix_[ant.current_city][i] && ant.is_traversed[i] == false)
			available_paths.push_back(i);
	return available_paths;
}

static int
choose_path(const Graph &graph, const std::vector<std::vector<double>>& pheromone_lvl,
			const std::vector<int>& available_paths, const Ant& ant) {
	std::vector<double> probabilities = std::vector(available_paths.size(), 0.0);
	double sum = 0;
	for (auto city = available_paths.begin(); city != available_paths.end(); city++)
		sum += pow(1.0 / graph.matrix_[ant.current_city][*city], BETA) * pow(pheromone_lvl[ant.current_city][*city], ALPHA);
	for (int i = 0; i < available_paths.size(); i++)
		probabilities[i] = 100 * pow(1.0 / graph.matrix_[ant.current_city][available_paths[i]], BETA) *
				pow(pheromone_lvl[ant.current_city][available_paths[i]], ALPHA) / sum;
	double random_choice = std::rand() % 100;

//    for (auto p = probabilities.begin(); p != probabilities.end(); ++p)
//        printf("%6.2f ", *p);
//    printf("random %f ", random_choice); //debug

	double probability_integral = 0;
	int path = ant.current_city;
	for (int i = 0; i < available_paths.size(); i++) {
		probability_integral += probabilities[i];
		if (probability_integral >= random_choice && path == ant.current_city)
			path = available_paths[i];
	}
	if (path == ant.current_city) // на случай погрешностей double
		path = available_paths.back();
//    printf("path %d\n", path); //debug
	return path;
}


static int
choose_elite_path(const Graph &graph, const std::vector<std::vector<double>>& pheromone_lvl,
                  const std::vector<int>& available_paths, const Ant& ant) {

    std::vector<double> probabilities = std::vector(available_paths.size(), 0.0);

    int max_index = 0;
    for (int i = 0; i < available_paths.size(); i++) {
        probabilities[i] = pow(1.0 / graph.matrix_[ant.current_city][available_paths[i]], BETA) *
                           pow(pheromone_lvl[ant.current_city][available_paths[i]], ALPHA);
        if (probabilities[i] > probabilities[max_index])
            max_index = i;
    }
    return available_paths[max_index];
}


static void
update_ant(const Graph &graph, Ant& ant, int path) {
	ant.length += graph.matrix_[ant.current_city][path];
	ant.traversed.push_back(path);
	ant.is_traversed[path] = true;
	ant.current_city = path;
}


static void
update_pheromone_lvl_rho(const Graph& graph, const std::vector<Ant>& ants, std::vector<std::vector<double>>& pheromone_lvl) {
    for (int i = 0; i < graph.vertices_cnt_; ++i)
        for (int j = 0; j < graph.vertices_cnt_; ++j)
            pheromone_lvl[i][j] *= (1.0 - RHO);
}


static void
finish_path(const Graph& graph, Ant& ant) {
    if (graph.matrix_[ant.traversed.back()][ant.traversed.front()]) {
        ant.traversed.push_back(ant.traversed.front());
        ant.length += graph.matrix_[ant.traversed.back()][ant.traversed.front()];
    }
}

static void
update_pheromone_lvl_ant(const Graph& graph, const Ant& ant, std::vector<std::vector<double>>& pheromone_lvl) {
    double delta;
    if (ant.traversed.size() == graph.vertices_cnt_ + 1) {
        delta = Q_VAL * (double)graph.vertices_cnt_ / (double)ant.length;
        for (int j = 0; j < graph.vertices_cnt_; ++j) {
            pheromone_lvl[ant.traversed[j]][ant.traversed[j + 1]] += delta;
            pheromone_lvl[ant.traversed[j + 1]][ant.traversed[j]] += delta;
        }
    }
}

static void
run_ants(const Graph& graph, std::vector<Ant>& ants, std::vector<std::vector<double>>& pheromone_lvl) {
    std::vector<int> available_paths;
    int path;

    for (int iter = 0; iter < ANTS_NUM; ++iter) {
        update_pheromone_lvl_rho(graph, ants, pheromone_lvl);
        restart_ants(graph, ants);
        for (auto ant = ants.begin(); ant != ants.end(); ant++) {
            available_paths = get_available_paths(graph, *ant);
            while (available_paths.size() > 0) {
                path = choose_path(graph, pheromone_lvl, available_paths, *ant);
                update_ant(graph, *ant, path);
                available_paths = get_available_paths(graph, *ant);
            }
//        for (auto city = ant->traversed.begin(); city != ant->traversed.end(); ++city)
//            printf("%3d ", *city);
//        printf("\n"); //debug
            finish_path(graph, *ant);
            update_pheromone_lvl_ant(graph, *ant, pheromone_lvl);
        }

        for (int i = 0; i < graph.vertices_cnt_; ++i) {
            for (int j = 0; j < graph.vertices_cnt_; ++j)
                printf("%5.2f ", pheromone_lvl[i][j]);
            std::cout << std::endl;
        } //debug
        printf("\n");

    }
}


static void
run_elite_ants(const Graph& graph, std::vector<Ant>& ants, std::vector<std::vector<double>>& pheromone_lvl) {
    std::vector<int> available_paths;
    int path;

    update_pheromone_lvl_rho(graph, ants, pheromone_lvl);
    restart_ants(graph, ants);
    for (auto ant = ants.begin(); ant != ants.end(); ant++) {
        available_paths = get_available_paths(graph, *ant);
        while (available_paths.size() > 0) {
            path = choose_elite_path(graph, pheromone_lvl, available_paths, *ant);
            update_ant(graph, *ant, path);
            available_paths = get_available_paths(graph, *ant);
        }
//       for (auto city = ant->traversed.begin(); city != ant->traversed.end(); ++city)
//           printf("%3d ", *city);
//       printf("\n"); //debug
        finish_path(graph, *ant);
    }
}


static GraphAlgorithms::TsmResult
collect_path(const Graph& graph, std::vector<Ant>& elite_ants) {
    Ant* best_ant = NULL;
    for (auto ant = elite_ants.begin(); ant != elite_ants.end(); ++ant) {
        if (ant->traversed.size() == graph.vertices_cnt_
        && graph.matrix_[ant->traversed.back()][ant->traversed.front()]
        && (best_ant == NULL || ant->length < best_ant->length)) {
            best_ant = &(*ant);
            printf("FOUND\n");
        }
    }
    if (best_ant == NULL)
        throw GraphAlgorithms::GraphAlgorithmsError("Ants couldn't find the shortest path.");
    return GraphAlgorithms::TsmResult{best_ant->traversed, (double)best_ant->length};
}


GraphAlgorithms::TsmResult GraphAlgorithms::
solveTravelingSalesmanProblem(Graph &graph) {
//	std::vector<int> cities_to_start_from = euler_graph_check(graph);
	std::vector<Ant> ants = std::vector<Ant>(graph.vertices_cnt_,
											 Ant{std::vector<bool>(graph.vertices_cnt_, false),
												 std::vector<int>(), 0, 0});
	std::vector<std::vector<double>> pheromone_lvl = std::vector<std::vector<double>>(
			graph.vertices_cnt_, std::vector<double>(graph.vertices_cnt_, 0.0));
	int path;

	init_pheromone_lvl(graph, pheromone_lvl);
    run_ants(graph, ants, pheromone_lvl);
    run_elite_ants(graph, ants, pheromone_lvl);

    return collect_path(graph, ants);
}