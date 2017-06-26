// Copyright 2017 Peter Hristov
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#include <cassert>

using namespace std;

pair<vector<int>, int> bfs(vector<vector<int>> tree, int root)
{
    int last = -1;
    int wlast = -1;
    queue<int> q;
    vector<int> distance(tree.size(), -1);
    vector<int> wdistance(tree.size(), -1);
    vector<int> parent(tree.size(), -1);

    q.push(root);
    distance[root] = 0;
    parent[root] = root;
    wdistance[root] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        last = u;

        if (wdistance[u] >= wdistance[wlast])
        {
            wlast = u;
        }

        for (int v : tree[u])
        {
            if (distance[v] == -1)
            {
                distance[v] = distance[u] + 1;
                parent[v] = u;

                // If both v and parent[u] are bigger or smaller than u
                // if ((u - v) * (u - parent[u]) > 0 && u != root)
                if (((u > v && u > parent[u]) || (u < v && u < parent[u])) && u != root)
                {
                    wdistance[v] = wdistance[u] + 1;
                }
                else
                {
                    wdistance[v] = wdistance[u];
                }

                q.push(v);
            }
        }
    }

    //cout << endl;
    //for (int i = 0; i < distance.size(); i++)
    //{
        // printf("d(%d, %d) = %d, w(%d, %d) = %d, p(%d) = %d\n", root, i, distance[i], root, i, wdistance[i], i, parent[i]);
        // printf("d(%d, %d) = %d  |  w(%d, %d) = %d  |  p(%d) = %d\n", root, i, distance[i], root, i, wdistance[i], i, parent[i]);
    //}

    int i = wlast;
    vector<int> path;

    while (parent[i] != i)
    {
        path.push_back(i);
        i = parent[i];
    }

    path.push_back(i);

    //printf("Path %d ~> %d is %ld edges and %d kink.\n", *(path.end() - 1), *path.begin(), path.size(), wdistance[*path.begin()]);

    // return wlast;
    return {path, wdistance[*path.begin()]};
}

vector<vector<int>> readTree()
{
    int vertices = 0;

    cin >> vertices;

    vector<vector<int>> tree(vertices);

    int u, v;

    while (cin >> u >> v)
    {
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    return tree;
}

/**
 * Write tree grid to STDIN
 */
void printTree(const std::vector<std::vector<int>> &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        std::cout << std::endl << std::setw(4) << i << " - ";
        for (const auto element : data[i])
        {
            std::cout << std::setw(4) << element;
        }
    }

    std::cout << std::endl;
}

int checkWDiameter(vector<int> path)
{
    int wd = 0;

    for(int i = 1; i < path.size() - 1 ; i++)
    {
        if ((path[i] > path[i-1] && path[i] > path[i+1]) || (path[i] < path[i-1] && path[i] < path[i+1]))
        {
            wd++;
        }
    }

    return wd;
}

bool isPath(vector<vector<int>> tree, vector<int> path)
{
    for(int u = 0; u < path.size() - 1 ; u++)
    {
        bool foundEdge = false;

        for (auto v: tree[path[u]])
        {
            if (v == path[u + 1])
            {
                foundEdge = true;
                break;
            }
        }

        if (false == foundEdge)
        {
            return false;
        }
    }

    return true;
}

int findRoot(vector<vector<int>> tree)
{
    for (int i = 0 ; i < tree.size() ; i++)
    {
        if (tree[i].size() != 0)
        {
            return i;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    auto tree = readTree();
    //printTree(tree);

    int root = findRoot(tree);
    //root = 5;

    // Critical W Path from 0 - 619513 -> 666360
    auto a = bfs(tree, root);
    auto b = bfs(tree, *(a.first.begin()));

    vector<int> path = b.first;
    int wdiameter = b.second;

    assert(isPath(tree, path));
    assert(wdiameter == checkWDiameter(path));

    printf("Root : %d\n", root);
    printf("Kink : %d\n", wdiameter);
    printf("Edges: %ld\n", path.size());
    printf("Path : %d ~> %d\n", *(path.end() - 1), *path.begin());

    //for(auto v: path)
    //{
        //cout << v << endl;
    //}

    return 0;
}
