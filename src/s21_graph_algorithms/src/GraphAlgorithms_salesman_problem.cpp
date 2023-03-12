#include "../include/GraphAlgorithms.h"

using namespace s21;

#define Q_VAL 10000.0
#define ANTS_NUM 100
#define ALPHA 0.7
#define BETA 0.7
#define RHO 0.3

struct Ant {
  std::vector<bool> is_traversed;
  std::vector<int> traversed;
  int current_city;
  double length;
};

static void restartAnts(std::vector<Ant> &ants) {

  for (int i = 0; i < (int)ants.size(); ++i) {
    ants[i].current_city = i % ANTS_NUM;
    ants[i].traversed.clear();
    ants[i].traversed.push_back(i % ANTS_NUM);
    ants[i].is_traversed = std::vector<bool>(ants.size(), false);
    ants[i].is_traversed[i % ANTS_NUM] = true;
    ants[i].length = 0.0;
  }
}

static void
initPheromoneLvl(const Graph &graph,
                   std::vector<std::vector<double>> &pheromone_lvl) {

  for (int i = 0; i < (int)graph.size(); ++i)
    for (int j = 0; j < (int)graph.size(); ++j)
      if (graph[i][j])
        pheromone_lvl[i][j] = 1;
}

static std::vector<int> getAvailablePaths(const Graph &graph,
                                            const Ant &ant) {

  std::vector<int> available_paths;
  for (int i = 0; i < (int)graph.size(); ++i)
    if (graph[ant.current_city][i] && ant.is_traversed[i] == false)
      available_paths.push_back(i);
  return available_paths;
}

static int choosePath(const Graph &graph,
                       const std::vector<std::vector<double>> &pheromone_lvl,
                       const std::vector<int> &available_paths,
                       const Ant &ant) {

  std::vector<double> probabilities = std::vector(available_paths.size(), 0.0);
  double sum = 0;
  for (auto city = available_paths.begin(); city != available_paths.end();
       city++)
    sum += pow(1.0 / graph[ant.current_city][*city], BETA) *
           pow(pheromone_lvl[ant.current_city][*city], ALPHA);
  for (int i = 0; i < (int)available_paths.size(); i++)
    probabilities[i] =
        100 * pow(1.0 / graph[ant.current_city][available_paths[i]], BETA) *
        pow(pheromone_lvl[ant.current_city][available_paths[i]], ALPHA) / sum;
  double random_choice = std::rand() % 100;

  double probability_integral = 0;
  int path = ant.current_city;
  for (int i = 0; i < (int)available_paths.size(); i++) {
    probability_integral += probabilities[i];
    if (probability_integral >= random_choice && path == ant.current_city)
      path = available_paths[i];
  }
  if (path == ant.current_city)
    path = available_paths.back();
  return path;
}

static int
chooseElitePath(const Graph &graph,
                  const std::vector<std::vector<double>> &pheromone_lvl,
                  const std::vector<int> &available_paths, const Ant &ant) {

  std::vector<double> probabilities = std::vector(available_paths.size(), 0.0);

  int max_index = 0;
  for (int i = 0; i < (int)available_paths.size(); i++) {
    probabilities[i] =
        pow(1.0 / graph[ant.current_city][available_paths[i]], BETA) *
        pow(pheromone_lvl[ant.current_city][available_paths[i]], ALPHA);
    if (probabilities[i] > probabilities[max_index])
      max_index = i;
  }
  return available_paths[max_index];
}

static void updateAnt(const Graph &graph, Ant &ant, int path) {

  ant.length += (double)graph[ant.current_city][path];
  ant.traversed.push_back(path);
  ant.is_traversed[path] = true;
  ant.current_city = path;
}

static void
updatePheromoneLvlRho(const Graph &graph,
                         std::vector<std::vector<double>> &pheromone_lvl) {

  for (int i = 0; i < (int)graph.size(); ++i)
    for (int j = 0; j < (int)graph.size(); ++j)
      pheromone_lvl[i][j] *= (1.0 - RHO);
}

static void finishPath(const Graph &graph, Ant &ant) {

  if (graph[ant.traversed.back()][ant.traversed.front()]) {
    ant.length += (double)graph[ant.traversed.back()][ant.traversed.front()];
    ant.traversed.push_back(ant.traversed.front());
  }
}

static void
updatePheromoneLvlAnt(const Graph &graph, const Ant &ant,
                         std::vector<std::vector<double>> &pheromone_lvl) {

  double delta;
  if (ant.traversed.size() == graph.size() + 1) {
    delta = Q_VAL * (double)graph.size() / (double)ant.length;
    for (int j = 0; j < (int)graph.size(); ++j) {
      pheromone_lvl[ant.traversed[j]][ant.traversed[j + 1]] += delta;
      pheromone_lvl[ant.traversed[j + 1]][ant.traversed[j]] += delta;
    }
  }
}

static void runAnts(const Graph &graph, std::vector<Ant> &ants,
                     std::vector<std::vector<double>> &pheromone_lvl) {

  std::vector<int> available_paths;
  int path;

  restartAnts(ants);
  for (auto ant = ants.begin(); ant != ants.end(); ant++) {
    available_paths = getAvailablePaths(graph, *ant);
    while (available_paths.size() > 0) {
      path = choosePath(graph, pheromone_lvl, available_paths, *ant);
      updateAnt(graph, *ant, path);
      available_paths = getAvailablePaths(graph, *ant);
    }
    finishPath(graph, *ant);
    updatePheromoneLvlAnt(graph, *ant, pheromone_lvl);
  }
}

static void runEliteAnts(const Graph &graph, std::vector<Ant> &ants,
                           std::vector<std::vector<double>> &pheromone_lvl) {

  std::vector<int> available_paths;
  int path;

  restartAnts(ants);
  for (auto ant = ants.begin(); ant != ants.end(); ant++) {
    available_paths = getAvailablePaths(graph, *ant);
    while (available_paths.size() > 0) {
      path = chooseElitePath(graph, pheromone_lvl, available_paths, *ant);
      updateAnt(graph, *ant, path);
      available_paths = getAvailablePaths(graph, *ant);
    }
    finishPath(graph, *ant);
    updatePheromoneLvlAnt(graph, *ant, pheromone_lvl);
  }
}

void findBestAnt(const Graph &graph, std::vector<Ant> &ants, Ant **best_ant) {

  for (auto ant = ants.begin(); ant != ants.end(); ++ant) {
    if (ant->traversed.size() == graph.size() + 1 &&
        ((*best_ant) == NULL || ant->length < (*best_ant)->length)) {
      if (*best_ant == NULL)
        *best_ant = new Ant(*ant);
      else
        **best_ant = *ant;
    }
  }
}

static GraphAlgorithms::TsmResult collectPath(Ant *best_ant) {

  if (best_ant == NULL)
    throw GraphAlgorithms::NoSolution("Ants couldn't find the shortest path");
  for (auto city = best_ant->traversed.begin();
       city != best_ant->traversed.end(); city++)
    *city = *city + 1;
  return GraphAlgorithms::TsmResult{best_ant->traversed, best_ant->length};
}

GraphAlgorithms::TsmResult
GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {

  std::vector<Ant> ants =
      std::vector<Ant>(graph.size(), Ant{std::vector<bool>(graph.size(), false),
                                         std::vector<int>(), 0, 0});
  std::vector<std::vector<double>> pheromone_lvl =
      std::vector<std::vector<double>>(graph.size(),
                                       std::vector<double>(graph.size(), 0.0));

  Ant *best_ant = NULL;
  initPheromoneLvl(graph, pheromone_lvl);
  for (int iter = 0; iter < ANTS_NUM / 2; ++iter) {
    updatePheromoneLvlRho(graph, pheromone_lvl);
    runAnts(graph, ants, pheromone_lvl);
    findBestAnt(graph, ants, &best_ant);
    runEliteAnts(graph, ants, pheromone_lvl);
    findBestAnt(graph, ants, &best_ant);
  }
  return collectPath(best_ant);
}