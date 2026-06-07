#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>

class MatrixGraph {
private:
    int vertex_count_;
    std::vector<std::vector<int> > matrix_;

    void dfsRoutes(int current, int finish, std::vector<int>& path,
                   std::vector<bool>& used,
                   std::vector<std::vector<int> >& routes) const;

public:
    MatrixGraph();
    MatrixGraph(const MatrixGraph& other);
    MatrixGraph& operator=(const MatrixGraph& other);
    ~MatrixGraph();

    void clear();
    bool isEmpty() const;
    int size() const;

    bool inputFromKeyboard(int max_n, bool directed);
    bool inputFromFile(const std::string& file_name, int max_n, bool directed);
    bool inputRandom(int max_n, bool directed);

    void print() const;
    std::vector<int> getDegrees() const;
    std::vector<int> getCitiesByTransfers(int start, int transfers) const;
    std::vector<std::vector<int> > findAllRoutes(int start, int finish) const;
};

class RouteList {
private:
    std::vector<std::vector<int> > routes_;

public:
    RouteList();
    RouteList(const RouteList& other);
    RouteList& operator=(const RouteList& other);
    ~RouteList();

    void setRoutes(const std::vector<std::vector<int> >& routes);
    void sortRoutes();
    bool saveToFile(const std::string& file_name) const;
    void print() const;
};

bool readInt(int& value);

void runGraf1();
void runGraf6();
void runGraf10();

#endif
