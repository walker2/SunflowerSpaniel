#ifndef SUNFLOWERSPANIEL_SEARCHALGHORITHMS_H
#define SUNFLOWERSPANIEL_SEARCHALGHORITHMS_H
/*
 Sample code from http://www.redblobgames.com/pathfinding/
 Copyright 2014 Red Blob Games <redblobgames@gmail.com>
s
 Feel free to use this code in your own projects, including commercial projects
 License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>
*/

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>

using std::unordered_map;
using std::unordered_set;
using std::array;
using std::vector;
using std::queue;
using std::priority_queue;
using std::pair;
using std::tuple;
using std::tie;
using std::string;

template<typename L>
struct SimpleGraph
{
    typedef L Location;
    typedef typename vector<Location>::iterator iterator;
    unordered_map<Location, vector<Location> > edges;

    inline const vector<Location> neighbors(Location id)
    {
        return edges[id];
    }
};

/*SimpleGraph<char> example_graph {{
                                         {'A', {'B'}},
                                         {'B', {'A', 'C', 'D'}},
                                         {'C', {'A'}},
                                         {'D', {'E', 'A'}},
                                         {'E', {'B'}}
                                 }};*/

// Helpers for SquareGrid::Location

// When using std::unordered_map<T>, we need to have std::hash<T> or
// provide a custom hash function in the constructor to unordered_map.
// Since I'm using std::unordered_map<tuple<int,int>> I'm defining the
// hash function here. It would be nice if C++ automatically provided
// the hash function for tuple and pair, like Python does. It would
// also be nice if C++ provided something like boost::hash_combine. In
// any case, here's a simple hash function that combines x and y:
namespace std
{
    template<>
    struct hash<tuple<int, int> >
    {
        inline size_t operator()(const tuple<int, int> &location) const
        {
            int x, y;
            tie(x, y) = location;
            return x * 1812433253 + y;
        }
    };
}

// For debugging it's useful to have an ostream::operator << so that we can write cout << foo
inline std::basic_iostream<char>::basic_ostream &
operator<<(std::basic_iostream<char>::basic_ostream &out, tuple<int, int> loc)
{
    int x, y;
    tie(x, y) = loc;
    out << '(' << x << ',' << y << ')';
    return out;
}

// This outputs a grid. Pass in a distances map if you want to print
// the distances, or pass in a point_to map if you want to print
// arrows that point to the parent location, or pass in a path vector
// if you want to draw the path.
template<class Graph>
void draw_grid(const Graph &graph, int field_width,
               unordered_map<typename Graph::Location, double> *distances = nullptr,
               unordered_map<typename Graph::Location, typename Graph::Location> *point_to = nullptr,
               vector<typename Graph::Location> *path = nullptr)
{
    for (int y = 0; y != graph.height; ++y)
    {
        for (int x = 0; x != graph.width; ++x)
        {
            typename Graph::Location id{x, y};
            std::cout << std::left << std::setw(field_width);
            if (graph.walls.count(id))
            {
                std::cout << string(field_width, '#');
            } else if (point_to != nullptr && point_to->count(id))
            {
                int x2, y2;
                tie(x2, y2) = (*point_to)[id];
                // TODO: how do I get setw to work with utf8?
                if (x2 == x + 1)
                { std::cout << "\u2192 "; }
                else if (x2 == x - 1)
                { std::cout << "\u2190 "; }
                else if (y2 == y + 1)
                { std::cout << "\u2193 "; }
                else if (y2 == y - 1)
                { std::cout << "\u2191 "; }
                else
                { std::cout << "* "; }
            } else if (distances != nullptr && distances->count(id))
            {
                std::cout << (*distances)[id];
            } else if (path != nullptr && std::find(path->begin(), path->end(), id) != path->end())
            {
                std::cout << '@';
            } else
            {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}

struct SquareGrid
{
    typedef tuple<int, int> Location;
    static array<Location, 8> DIRS;

    int width, height;
    unordered_set<Location> walls;

    SquareGrid(int width_, int height_)
            : width(width_), height(height_)
    {}

    inline bool in_bounds(Location id) const
    {
        int x, y;
        tie(x, y) = id;
        return 0 <= x && x < width && 0 <= y && y < height;
    }

    inline bool passable(Location id) const
    {
        return !walls.count(id);
    }

    vector<Location> neighbors(Location id) const
    {
        int x, y, dx, dy;
        tie(x, y) = id;
        vector<Location> results;

        for (auto dir : DIRS)
        {
            tie(dx, dy) = dir;
            Location next(x + dx, y + dy);
            if (in_bounds(next) && passable(next))
            {
                results.push_back(next);
            }
        }

        if ((x + y) % 2 == 0)
        {
            // aesthetic improvement on square grids
            std::reverse(results.begin(), results.end());
        }

        return results;
    }
};


inline void add_rect(SquareGrid &grid, int x1, int y1, int x2, int y2)
{
    for (int x = x1; x < x2; ++x)
    {
        for (int y = y1; y < y2; ++y)
        {
            grid.walls.insert(SquareGrid::Location {x, y});
        }
    }
}

inline SquareGrid make_diagram1()
{
    SquareGrid grid(200, 200);
    add_rect(grid, 3, 3, 5, 12);
    add_rect(grid, 13, 4, 15, 15);
    add_rect(grid, 21, 0, 23, 7);
    add_rect(grid, 23, 5, 26, 7);
    return grid;
}

struct GridWithWeights : SquareGrid
{
    unordered_set<Location> forests;

    GridWithWeights(int w, int h) : SquareGrid(w, h)
    {}

    double cost(Location /*from_node*/, Location to_node) const
    {
        return forests.count(to_node) ? 5 : 1;
    }
};

inline GridWithWeights make_diagram4()
{
    GridWithWeights grid(200, 200);
    add_rect(grid, 1, 7, 4, 9);
    typedef SquareGrid::Location L;
    grid.forests = unordered_set<SquareGrid::Location> {
            L{3, 4}, L{3, 5}, L{4, 1}, L{4, 2},
            L{4, 3}, L{4, 4}, L{4, 5}, L{4, 6},
            L{4, 7}, L{4, 8}, L{5, 1}, L{5, 2},
            L{5, 3}, L{5, 4}, L{5, 5}, L{5, 6},
            L{5, 7}, L{5, 8}, L{6, 2}, L{6, 3},
            L{6, 4}, L{6, 5}, L{6, 6}, L{6, 7},
            L{7, 3}, L{7, 4}, L{7, 5}
    };
    return grid;
}

template<typename T, typename priority_t>
struct PriorityQueue
{
    typedef pair<priority_t, T> PQElement;
    priority_queue<PQElement, vector<PQElement>,
            std::greater<PQElement>> elements;

    inline bool empty() const
    { return elements.empty(); }

    inline void put(T item, priority_t priority)
    {
        elements.emplace(priority, item);
    }

    inline T get()
    {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

template<typename Graph>
inline void dijkstra_search
        (const Graph &graph,
         typename Graph::Location start,
         typename Graph::Location goal,
         unordered_map<typename Graph::Location, typename Graph::Location> &came_from,
         unordered_map<typename Graph::Location, double> &cost_so_far)
{
    typedef typename Graph::Location Location;
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty())
    {
        auto current = frontier.get();

        if (current == goal)
        {
            break;
        }

        for (auto next : graph.neighbors(current))
        {
            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                came_from[next] = current;
                frontier.put(next, new_cost);
            }
        }
    }
}

template<typename Location>
vector<Location> reconstruct_path(
        Location start,
        Location goal,
        unordered_map<Location, Location> &came_from
)
{
    vector<Location> path;
    Location current = goal;
    path.push_back(current);
    while (current != start)
    {
        current = came_from[current];
        path.push_back(current);
    }
    path.push_back(start); // optional
    std::reverse(path.begin(), path.end());
    return path;
}

inline double heuristic(SquareGrid::Location a, SquareGrid::Location b)
{
    int x1, y1, x2, y2;
    tie(x1, y1) = a;
    tie(x2, y2) = b;
    return abs(x1 - x2) + abs(y1 - y2);
}

template<typename Graph>
inline void a_star_search
        (const Graph &graph,
         typename Graph::Location start,
         typename Graph::Location goal,
         unordered_map<typename Graph::Location, typename Graph::Location> &came_from,
         unordered_map<typename Graph::Location, double> &cost_so_far)
{
    typedef typename Graph::Location Location;
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty())
    {
        auto current = frontier.get();

        if (current == goal)
        {
            break;
        }

        for (auto next : graph.neighbors(current))
        {
            double new_cost = cost_so_far[current] + graph.cost(current, next);

            if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}

template<typename Graph>
inline unordered_map<typename Graph::Location, typename Graph::Location>
breadth_first_search(const Graph &graph,
                     typename Graph::Location start,
                     typename Graph::Location goal)
{
    typedef typename Graph::Location Location;
    queue<Location> frontier;
    frontier.push(start);

    unordered_map<Location, Location> came_from;
    came_from[start] = start;

    while (!frontier.empty())
    {
        auto current = frontier.front();
        frontier.pop();

        if (current == goal)
        {
            break;
        }

        for (auto next : graph.neighbors(current))
        {
            if (!came_from.count(next))
            {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }
    return came_from;
}

#endif