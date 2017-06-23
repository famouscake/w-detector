// Copyright 2017 Peter Hristov
#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

int bfs(vector<vector<int>> tree, int root)
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
                if ((u - v) * (u - parent[u]) > 0 && u != root)
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

    cout << endl;
    for (int i = 0 ; i < distance.size() ; i++)
    {
        //printf("d(%d, %d) = %d, w(%d, %d) = %d, p(%d) = %d\n", root, i, distance[i], root, i, wdistance[i], i, parent[i]);
        printf("d(%d, %d) = %d  |  w(%d, %d) = %d  |  p(%d) = %d\n", root, i, distance[i], root, i, wdistance[i], i, parent[i]);
    }

    //cout << "Critical W Path : ";
    //int i = last;

    //while(parent[i] != i)
    //{
        //cout << i << " ";
        //i = parent[i];
    //}

    //cout << i;

    //cout << endl;

    return wlast;
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


int main(int argc, char *argv[])
{

    auto tree = readTree();

    //printTree(tree);

    int a = bfs(tree, 0);
    int b = bfs(tree, a);

    printf("\nW Diameter is %d -> %d", a, b);

    return 0;
}
