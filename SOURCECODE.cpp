#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <climits>
#include <map>
#include <conio.h>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

// ANSI color codes for terminal UI enhancement
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Utility function to print a separator line
void printSeparator(char ch = '-', int length = 78) {
    cout << string(length, ch) << endl;
}

// Edge class for graph representation
class Edge {
public:
    int nbr;
    double wt;
    Edge(int nbr, double wt) : nbr(nbr), wt(wt) {}
};

// Driver information
class Driver {
public:
    string name, cname, phonen, pnumber;
    double rate;
    Driver(string name, string cname, string phonen, string pnumber, double rate)
        : name(name), cname(cname), phonen(phonen), pnumber(pnumber), rate(rate) {}
};

// Pair for Dijkstra's algorithm
class DijkstraPair {
public:
    int val;
    double cost;
    string path;
    DijkstraPair(int val, double cost, string path) : val(val), cost(cost), path(path) {}
    bool operator>(const DijkstraPair &other) const { return cost > other.cost; }
};

// Pair for path with stops
class StopPair {
public:
    int val;
    double cost;
    int bitmask;
    StopPair(int val, double cost, int bitmask) : val(val), cost(cost), bitmask(bitmask) {}
    bool operator>(const StopPair &other) const { return cost > other.cost; }
};

// Pair for Prim's algorithm
class PrimsPair {
public:
    int val;
    double lcost;
    PrimsPair(int val, double lcost) : val(val), lcost(lcost) {}
    bool operator>(const PrimsPair &other) const { return lcost > other.lcost; }
};

// Graphs for each city
vector<vector<Edge>> delhi(12), uttrakhand(12), bangalore(12);

// City mappings
unordered_map<string, int> dm, ukm, bangm;
unordered_map<int, string> dm1, ukm1, bangm1;
unordered_map<string, vector<vector<Edge>>> choice;
unordered_map<string, unordered_map<string, int>> cchoice;
unordered_map<string, unordered_map<int, string>> cchoice1;

// Driver mappings
unordered_map<int, vector<Driver>> m1, m2, m3;
unordered_map<string, unordered_map<int, vector<Driver>>> mapingdrivercity;

// Driver info for Delhi
void makeDriverInfoDelhi() {
    m1[0] = { Driver("rakesh", "scorpio", "9988992345", "DL2CK81699", 8.88),
              Driver("rju", "tata indica", "9988792345", "DL3C876997", 6.88),
              Driver("Birju", "Hyundai i20", "9988922345", "DL2CT81699", 5.88) };
    m1[1] = { Driver("Mahesh", "Hyundai Accent", "7988992345", "DL2TK81799", 8.88),
              Driver("srijan", "tata Sumo", "6988992345", "DL1C876097", 7.88),
              Driver("Ujjwal", "Tata Nano", "8988992345", "DL2FT81899", 4.58) };
    m1[2] = { Driver("Hardik", "Mahindra XUV 700", "9988992345", "DL5CK81699", 12.00) };
    m1[3] = { Driver("Suresh", "Hyundai i10 grand", "9966992345", "DL2TK41799", 6.00),
              Driver("sHubhanshu", "Hyundai Creta", "7988992345", "DL1C876667", 13.00) };
    m1[4] = { Driver("Ankur", "Wagnor Lxi", "6988992345", "DL1C859097", 9.00),
              Driver("ankit", "Naruti Suzuki Swift", "7988992345", "DL2FU01899", 8.97) };
    m1[5] = { Driver("Montu", "Mahindra KUV", "9955992345", "DL5CK87691", 16.00) };
    m1[6] = { Driver("Suresh", "Hyundai Santro", "9999992345", "DL2TK41999", 8.12),
              Driver("Sharat", "Celerio", "9988992388", "DL3C076667", 9.67) };
    m1[7] = { Driver("Monty", "Mahindra TUV 300", "9954992345", "DL5CH87671", 14.00) };
    m1[8] = { Driver("Suresh", "Hyundai Santro", "9990992345", "DL2TK41999", 8.12),
              Driver("Sharat", "Celerio", "7788992345", "DL3C076667", 9.67) };
    m1[9] = { Driver("rakesh", "scorpio", "8888992345", "DL2CK81699", 8.88),
              Driver("rju", "tata indica", "8088992345", "DL3C876997", 6.88),
              Driver("Birju", "Hyundai i20", "9088992345", "DL2CT81699", 5.88) };
    m1[10] = { Driver("Manu", "scorpio", "7988992345", "DL2CK81699", 8.88),
               Driver("Mandeep", "Tata Nano", "8988992345", "DL4C876907", 3.88),
               Driver("Mukesh", "XUV 500", "7688992345", "DL2CH81689", 12.88) };
    m1[11] = { Driver("Sumit", "Tata Harrier", "7766992345", "DL9CH86671", 12.00) };
    mapingdrivercity["delhi"] = m1;
}

// Driver info for Uttrakhand
void makeDriverInfoUK() {
    m2[0] = { Driver("rakesh", "scorpio", "9988992345", "UK2CK81699", 8.88),
              Driver("rju", "tata indica", "9988792345", "UK3C876997", 6.88),
              Driver("Birju", "Hyundai i20", "9988922345", "UK2CT81699", 5.88) };
    m2[1] = { Driver("Mahesh", "Hyundai Accent", "7988992345", "UK2TK81799", 8.88),
              Driver("srijan", "tata Sumo", "6988992345", "UK1C876097", 7.88),
              Driver("Ujjwal", "Tata Nano", "8988992345", "UK2FT81899", 4.58) };
    m2[2] = { Driver("Hardik", "Mahindra XUV 700", "9988992345", "UK5CK81699", 12.00) };
    m2[3] = { Driver("Suresh", "Hyundai i10 grand", "9966992345", "UK2TK41799", 6.00),
              Driver("sHubhanshu", "Hyundai Creta", "7988992345", "UK1C876667", 13.00) };
    m2[4] = { Driver("Ankur", "Wagnor Lxi", "6988992345", "UK1C859097", 9.00),
              Driver("ankit", "Naruti Suzuki Swift", "7988992345", "UK2FU01899", 8.97) };
    m2[5] = { Driver("Montu", "Mahindra KUV", "9955992345", "UK5CK87691", 16.00) };
    m2[6] = { Driver("Suresh", "Hyundai Santro", "9999992345", "UK2TK41999", 8.12),
              Driver("Sharat", "Celerio", "9988992388", "UK3C076667", 9.67) };
    m2[7] = { Driver("Monty", "Mahindra TUV 300", "9954992345", "UK5CH87671", 14.00) };
    m2[8] = { Driver("Suresh", "Hyundai Santro", "9990992345", "UK2TK41999", 8.12),
              Driver("Sharat", "Celerio", "7788992345", "UK3C076667", 9.67) };
    m2[9] = { Driver("rakesh", "scorpio", "8888992345", "UK2CK81699", 8.88),
              Driver("rju", "tata indica", "8088992345", "UK3C876997", 6.88),
              Driver("Birju", "Hyundai i20", "9088992345", "UK2CT81699", 5.88) };
    m2[10] = { Driver("Manu", "scorpio", "7988992345", "UK2CK81699", 8.88),
               Driver("Mandeep", "Tata Nano", "8988992345", "UK4C876907", 3.88),
               Driver("Mukesh", "XUV 500", "7688992345", "UK2CH81689", 12.88) };
    m2[11] = { Driver("Sumit", "Tata Harrier", "7766992345", "UK9CH86671", 12.00) };
    mapingdrivercity["uttrakhand"] = m2;
}

// Driver info for Bangalore
void makeDriverInfoBG() {
    m3[0] = { Driver("rakesh", "scorpio", "9988992345", "KA2CK81699", 8.88),
              Driver("rju", "tata indica", "9988792345", "KA3C876997", 6.88),
              Driver("Birju", "Hyundai i20", "9988922345", "KA2CT81699", 5.88) };
    m3[1] = { Driver("Mahesh", "Hyundai Accent", "7988992345", "KA2TK81799", 8.88),
              Driver("srijan", "tata Sumo", "6988992345", "KA1C876097", 7.88),
              Driver("Ujjwal", "Tata Nano", "8988992345", "KA2FT81899", 4.58) };
    m3[2] = { Driver("Hardik", "Mahindra XUV 700", "9988992345", "KA5CK81699", 12.00) };
    m3[3] = { Driver("Suresh", "Hyundai i10 grand", "9966992345", "KA2TK41799", 6.00),
              Driver("sHubhanshu", "Hyundai Creta", "7988992345", "KA1C876667", 13.00) };
    m3[4] = { Driver("Ankur", "Wagnor Lxi", "6988992345", "KA1C859097", 9.00),
              Driver("ankit", "Naruti SuzKAi Swift", "7988992345", "KA2FU01899", 8.97) };
    m3[5] = { Driver("Montu", "Mahindra KUV", "9955992345", "KA5CK87691", 16.00) };
    m3[6] = { Driver("Suresh", "Hyundai Santro", "9999992345", "KA2TK41999", 8.12),
              Driver("Sharat", "Celerio", "9988992388", "KA3C076667", 9.67) };
    m3[7] = { Driver("Monty", "Mahindra TUV 300", "9954992345", "KA5CH87671", 14.00) };
    m3[8] = { Driver("Suresh", "Hyundai Santro", "9990992345", "KA2TK41999", 8.12),
              Driver("Sharat", "Celerio", "7788992345", "KA3C076667", 9.67) };
    m3[9] = { Driver("rakesh", "scorpio", "8888992345", "KA2CK81699", 8.88),
              Driver("rju", "tata indica", "8088992345", "KA3C876997", 6.88),
              Driver("Birju", "Hyundai i20", "9088992345", "KA2CT81699", 5.88) };
    m3[10] = { Driver("Manu", "scorpio", "7988992345", "KA2CK81699", 8.88),
               Driver("Mandeep", "Tata Nano", "8988992345", "KA4C876907", 3.88),
               Driver("Mahesh", "XUV 500", "7688992345", "KA2CH81689", 12.88) };
    m3[11] = { Driver("Sumit", "Tata Harrier", "7766992345", "KA9CH86671", 12.00) };
    mapingdrivercity["bangalore"] = m3;
}

// Add edge to graph
void addEdge(int v1, int v2, double weight, vector<vector<Edge>> &graph) {
    graph[v1].emplace_back(v2, weight);
    graph[v2].emplace_back(v1, weight);
}

// Build graphs for all cities
void makeGraphs() {
    // Delhi
    addEdge(0, 1, 2.4, delhi); addEdge(0, 10, 12, delhi); addEdge(0, 7, 4.7, delhi);
    addEdge(0, 6, 7.5, delhi); addEdge(1, 10, 14, delhi); addEdge(1, 7, 13, delhi);
    addEdge(7, 8, 14, delhi); addEdge(7, 6, 3.1, delhi); addEdge(6, 8, 12, delhi);
    addEdge(6, 4, 29, delhi); addEdge(2, 5, 21, delhi); addEdge(2, 8, 6.4, delhi);
    addEdge(2, 10, 8.8, delhi); addEdge(2, 3, 3.1, delhi); addEdge(5, 3, 15, delhi);
    addEdge(5, 4, 30, delhi); addEdge(10, 3, 7.7, delhi); addEdge(3, 9, 2.2, delhi);
    addEdge(3, 4, 17, delhi); addEdge(4, 9, 17, delhi); addEdge(4, 11, 20, delhi);
    addEdge(9, 11, 4.2, delhi);

    // Bangalore
    addEdge(0, 1, 7.7, bangalore); addEdge(0, 2, 8.5, bangalore); addEdge(1, 2, 9.9, bangalore);
    addEdge(1, 4, 11, bangalore); addEdge(1, 7, 36, bangalore); addEdge(2, 11, 30, bangalore);
    addEdge(2, 8, 6.9, bangalore); addEdge(2, 5, 17, bangalore); addEdge(2, 4, 3.8, bangalore);
    addEdge(2, 3, 9.2, bangalore); addEdge(3, 9, 61, bangalore); addEdge(3, 10, 45, bangalore);
    addEdge(5, 4, 14, bangalore); addEdge(4, 6, 7.9, bangalore); addEdge(4, 8, 8, bangalore);
    addEdge(8, 7, 21, bangalore); addEdge(7, 6, 40, bangalore); addEdge(6, 10, 45, bangalore);
    addEdge(6, 9, 63, bangalore); addEdge(9, 10, 63, bangalore);

    // Uttrakhand
    addEdge(0, 1, 128, uttrakhand); addEdge(0, 2, 147, uttrakhand); addEdge(0, 1, 147, uttrakhand);
    addEdge(1, 2, 26, uttrakhand); addEdge(1, 6, 55, uttrakhand); addEdge(2, 3, 4, uttrakhand);
    addEdge(2, 4, 63, uttrakhand); addEdge(2, 6, 33, uttrakhand); addEdge(2, 5, 15, uttrakhand);
    addEdge(5, 10, 87, uttrakhand); addEdge(5, 11, 275, uttrakhand); addEdge(5, 9, 265, uttrakhand);
    addEdge(4, 6, 44, uttrakhand); addEdge(6, 8, 287, uttrakhand); addEdge(4, 7, 87, uttrakhand);
    addEdge(3, 8, 366, uttrakhand); addEdge(3, 7, 224, uttrakhand); addEdge(10, 3, 147, uttrakhand);
    addEdge(7, 11, 132, uttrakhand);
}

// City and node mappings
void doMapping() {
    // Delhi
    vector<pair<string, int>> delhiMap = {
        {"khazoorikhas", 1}, {"bhajanpura", 0}, {"akshardham", 10}, {"mandoli", 7},
        {"indiagate", 2}, {"redfort", 8}, {"dilshadgarden", 6}, {"oldseemapuri", 5},
        {"cannaughtplace", 3}, {"janakpuri", 4}, {"chandnichowk", 11}, {"jantarmantar", 9}
    };
    for (auto &p : delhiMap) { dm[p.first] = p.second; dm1[p.second] = p.first; }

    // Bangalore
    vector<pair<string, int>> bangMap = {
        {"lalbaghbotanicalgarden", 0}, {"marutinagar", 1}, {"shivanagar", 2}, {"iskontemple", 3},
        {"bangalorepalace", 4}, {"nehrunagar", 5}, {"kurubarahalli", 6}, {"bannerghatabiologicalpark", 7},
        {"tipusultansummerpalace", 8}, {"nandihills", 9}, {"shivagangue", 10}, {"naityagram", 11}
    };
    for (auto &p : bangMap) { bangm[p.first] = p.second; bangm1[p.second] = p.first; }

    // Uttrakhand
    vector<pair<string, int>> ukMap = {
        {"haridwar", 0}, {"kashipur", 1}, {"jimcorbettnationalpark", 2}, {"kalagarhdam", 3},
        {"nainital", 4}, {"girjadevitemple", 5}, {"chardhammandir", 6}, {"binsar", 7},
        {"chamoli", 8}, {"joshimath", 9}, {"pangoot", 10}, {"mountabbott", 11}
    };
    for (auto &p : ukMap) { ukm[p.first] = p.second; ukm1[p.second] = p.first; }

    // City graph and mapping
    choice["delhi"] = delhi; choice["uttrakhand"] = uttrakhand; choice["bangalore"] = bangalore;
    cchoice["delhi"] = dm; cchoice["bangalore"] = bangm; cchoice["uttrakhand"] = ukm;
    cchoice1["delhi"] = dm1; cchoice1["bangalore"] = bangm1; cchoice1["uttrakhand"] = ukm1;
}

// Print all paths utility
void printAllPathsUtil(int u, int d, const vector<vector<Edge>> &city, vector<bool> &visited, string psf, unordered_map<int, string> &getcity, int &count, double distance) {
    visited[u] = true;
    if (u == d) {
        count++;
        cout << count << "  :-  " << psf << " " << distance << "\n\n";
        visited[u] = false;
        return;
    }
    for (const Edge &e : city[u]) {
        if (!visited[e.nbr])
            printAllPathsUtil(e.nbr, d, city, visited, psf + "->" + getcity[e.nbr], getcity, count, distance + e.wt);
    }
    visited[u] = false;
}

// Print all paths from s to d
void printAllPaths(int s, int d, vector<vector<Edge>> &city, unordered_map<int, string> &getcity) {
    vector<bool> visited(city.size(), false);
    string psf = getcity[s] + "->";
    int count = 0;
    printAllPathsUtil(s, d, city, visited, psf, getcity, count, 0);
}

// Find path through stops (recursive)
void findStopPath(int src, int des, vector<vector<Edge>> &city, int nmv, unordered_map<string, int> &getid, unordered_map<int, string> &getcity, int bitmsk, double curdistance, vector<bool> &visited, string psf, map<double, string> &m1) {
    visited[src] = true;
    if (src == des && bitmsk == (1 << nmv) - 1) {
        m1[curdistance] = psf;
        visited[src] = false;
        return;
    }
    for (const Edge &e : city[src]) {
        string city1 = getcity[e.nbr];
        int newbitmask = bitmsk;
        if (!visited[e.nbr]) {
            if (getid.count(city1)) newbitmask |= (1 << getid[city1]);
            findStopPath(e.nbr, des, city, nmv, getid, getcity, newbitmask, curdistance + e.wt, visited, psf + "->" + getcity[e.nbr], m1);
        }
    }
    visited[src] = false;
}

// Dijkstra's shortest path
void shortestPath(int src, int dsc, vector<vector<Edge>> &city, unordered_map<int, string> &getcity) {
    priority_queue<DijkstraPair, vector<DijkstraPair>, greater<DijkstraPair>> pq;
    pq.emplace(src, 0, getcity[src]);
    vector<bool> visited(city.size(), false);
    int count = 1;
    double cost1 = INT_MAX;
    while (!pq.empty()) {
        DijkstraPair d1 = pq.top(); pq.pop();
        if (d1.val == dsc && d1.cost <= cost1) {
            cout << "Path " << count << "-: " << d1.path << " - " << d1.cost << " KM\n\n";
            cost1 = d1.cost;
            count++;
            continue;
        }
        if (visited[d1.val]) continue;
        visited[d1.val] = true;
        for (const Edge &e : city[d1.val]) {
            if (!visited[e.nbr])
                pq.emplace(e.nbr, e.wt + d1.cost, d1.path + "->" + getcity[e.nbr]);
        }
    }
}

// Prim's algorithm for visiting all cities
void shortestPathCity(int src, vector<vector<Edge>> &city, unordered_map<int, string> &getcity) {
    priority_queue<PrimsPair, vector<PrimsPair>, greater<PrimsPair>> pq;
    pq.emplace(src, 0);
    vector<bool> visited(city.size(), false);
    double totalCost = 0;
    int visit = 0;
    cout << "\n";
    while (!pq.empty()) {
        PrimsPair d1 = pq.top(); pq.pop();
        if (visited[d1.val]) continue;
        totalCost += d1.lcost;
        visit++;
        cout << getcity[d1.val] << "{ " << d1.lcost << " }-> ";
        if (visit == city.size()) {
            cout << "\n\nTOTAL COST OF VISITING IS : " << totalCost << " KM \n";
            break;
        }
        visited[d1.val] = true;
        for (const Edge &e : city[d1.val]) {
            if (!visited[e.nbr])
                pq.emplace(e.nbr, e.wt);
        }
    }
}

// Print driver info at location
void getDriverInfo(int src, unordered_map<int, vector<Driver>> &d) {
    const vector<Driver> &drivers = d[src];
    int count = 0;
    for (const Driver &s : drivers) {
        cout << "\n" << ++count << "\n";
        cout << "Driver name - " << s.name << "\n";
        cout << "Driver car name - " << s.cname << "\n";
        cout << "Driver car no plate - " << s.pnumber << "\n";
        cout << "Driver Phone number - " << s.phonen << "\n";
        cout << "Driver charges for per km   " << s.rate << " per km ";
    }
}

// Print centered message
void printMessageCenter(const char *message) {
    int len = (78 - strlen(message)) / 2;
    cout << string(len, ' ');
    cout << BOLD << CYAN << message << RESET << endl;
    cout << "\nDate: " << __DATE__ << "\t\t\t\t\t     Time: " << __TIME__;
    cout << "\n\n\t\t       1. VEDANT SINGH    - B2 - 22103058";
}

void printMessageCenter2(const char *message) {
    int len = (78 - strlen(message)) / 2;
    cout << string(len, ' ');
    cout << BOLD << MAGENTA << message << RESET << endl;
}

// Loading page
void loadingPage() {
    cout << BOLD << GREEN << "\t\t\tPLEASE WAIT\n" << RESET;
    cout << BOLD << GREEN << "\t\t\tSYSTEM IS LOADING\n" << RESET;
    cout << "\n\nPress any key to start now.....";
    getch();
}

// Header message
void headMessage(const char *message) {
    system("cls");
    printSeparator('=');
    cout << BOLD << BLUE;
    cout << "\n############                                                   ############\n";
    cout << "############        CITY TOUR NAVIGATION OPTIMISATION          ############\n";
    cout << "############             SYSTEM (PROJECT IN C++)               ############\n";
    cout << "############                                                   ############\n";
    cout << "###########################################################################\n";
    cout << "\n---------------------------------------------------------------------------\n";
    printMessageCenter(message);
    cout << "\n----------------------------------------------------------------------------\n\n" << RESET;
}

// Welcome message
void welcomeMsg() {
    headMessage("CREATED BY :-");
    loadingPage();
    cout << "\n\n\n\n\n";
    cout << "\n\t    **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\t          =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\t          =                 WELCOME                   =";
    cout << "\n\t          =                   TO                      =";
    cout << "\n\t          =    CITY TOUR NAVIGATION OPTIMISATION      =";
    cout << "\n\t          =                 SYSTEM                    =";
    cout << "\n\t          =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
    cout << "\n\n\t    **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
    cout << "\n\n Enter any key to continue.....";
    getch();
}

int main() {
    cout << "       **********************HERE IS OUR PROJECT***************************       \n";
    cout << "       ***************CITY NAVIGATION OPTIMISATION SYSTEM******************       \n";
    welcomeMsg();
    makeGraphs();
    doMapping();
    makeDriverInfoDelhi();
    makeDriverInfoUK();
    makeDriverInfoBG();

    bool b2 = true;
    while (b2) {
        headMessage("CREATED BY :-");
        printMessageCenter2("STATES\n");
        cout << "HERE ARE THE MAPS OF THE CITIES THAT ARE AVAILABLE IN OUR DATA BASE\n\n";
        cout << "   1. DELHI\n";
        cout << "   2. BANGALORE\n";
        cout << "   3. UTTRAKHAND\n";
        cout << "\nChoose the city among about in which you live/want to travel : \n";
        string k;
        cin >> k;
        transform(k.begin(), k.end(), k.begin(), ::tolower);

        if (k != "delhi" && k != "uttrakhand" && k != "bangalore") {
            cout << "\nSorry for the inconvenience caused. We will soon add more city maps in our database\n";
            cout << "********************************THANK YOU*****************************************\n\n";
            return 0;
        }

        bool b1 = true;
        while (b1) {
            cout << "\n**********Here is the list of places that you can visit in " << k << "*********\n\n";
            int i = 1;
            for (auto &it : cchoice[k]) {
                string city = it.first;
                transform(city.begin(), city.end(), city.begin(), ::toupper);
                cout << "   " << i++ << "." << city << "\n";
            }

            cout << "\n\nEnter your location : \n";
            string src;
            cin >> src;
            transform(src.begin(), src.end(), src.begin(), ::tolower);
            cout << "\nNow we know which city you are residing or wanna explore. Now choose one of the options:\n";
            cout << "1. Want to travel from your location to some other location\n";
            cout << "2. Want to visit all the places of current city in our database\n";
            cout << "3. Want a transport guidance at your current location\n\n(Press 1/2/3) to proceed \n";
            int ch;
            cin >> ch;

            switch (ch) {
            case 1: {
                cout << "\nEnter your destination\n";
                string dsc;
                cin >> dsc;
                transform(dsc.begin(), dsc.end(), dsc.begin(), ::tolower);
                cout << "\nHere shows information about all the path from your location to the destination\n\n";
                printAllPaths(cchoice[k][src], cchoice[k][dsc], choice[k], cchoice1[k]);

                cout << "Do you want to see shortest path among these paths from " << src << " to " << dsc << " (Press 0/1) \n";
                int c;
                cin >> c;
                cout << "\n";
                if (c == 1) {
                    cout << "***********************HERE ARE THE SHORTEST PATHS********************\n\n";
                    shortestPath(cchoice[k][src], cchoice[k][dsc], choice[k], cchoice1[k]);
                }

                cout << "Do you want to enter stops in between your location -: " << src << " and destination :- " << dsc << " (Press 0/1)\n";
                cin >> c;
                cout << "\n";
                if (c == 1) {
                    unordered_map<string, int> smap;
                    cout << "Enter number of stops that you want between source and destination :\n";
                    int n;
                    cin >> n;
                    cout << "\nNow enter your stops that you want between your source and destination :\n";
                    for (int i = 0; i < n; i++) {
                        string s;
                        cin >> s;
                        smap[s] = i;
                    }
                    cout << "\nHere are the paths from source to destination including stops in increasing order of distance\n\n";
                    vector<bool> visited(12, false);
                    string psf = src + "-> ";
                    map<double, string> m1;
                    findStopPath(cchoice[k][src], cchoice[k][dsc], choice[k], n, smap, cchoice1[k], 0, 0, visited, psf, m1);
                    int w = 1;
                    if (m1.empty()) {
                        cout << "No Paths through all the entered locations is possible. Please enter any other locations! \n";
                    }
                    for (auto &it : m1) {
                        cout << "path " << w++ << " -: " << it.second << "   distance-: " << it.first << "\n\n";
                    }
                    cout << "\n";
                }
                break;
            }
            case 2:
                cout << "\nHere is the shortest path visiting all the places in the given city at minimum cost : \n";
                shortestPathCity(cchoice[k][src], choice[k], cchoice1[k]);
                break;
            case 3:
                cout << "          So You Need Transport Guidance. Don't Worry! We Have Driver Information in our Database\n";
                cout << "                Here Is The Information Regarding The Drivers Available At Your Location\n";
                getDriverInfo(cchoice[k][src], mapingdrivercity[k]);
                cout << "\nPlease Contact These Drivers\n";
                break;
            }

            cout << "\nDo you want to visit your city menu again (Press 0/1) \n";
            int t;
            cin >> t;
            if (t == 0) b1 = false;
        }

        cout << "\nDo you want to visit some other state/Exit from our data base (Press 0/1) \n";
        int t1;
        cin >> t1;
        if (t1 == 0) b2 = false;
    }
}
