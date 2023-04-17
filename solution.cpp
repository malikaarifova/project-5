#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

enum Node_Type {SOURCE, SINK, DICE, WORD};
class Node{
    public:
    int id;
    Node_Type type;
    vector<bool> letters;
    vector<class Edge*> adjMatrix;
    bool visited;
    class Edge* backEdge; // previous edge
    Node(int id, Node_Type type){
        this->id = id;
        this->type = type;
        visited = 0;
        letters.resize(26, false);
    }
    ~Node(){};
    void setLetter(string letterSet){
        for(int i = 0; i < letterSet.size(); i++){
            letters[letterSet[i] - 65] = true;
        }
    }
    void addEdge(Edge* edge){
        adjMatrix.push_back(edge);
    }
    void setBackEdge(Edge* edge){
        cout << "yets \n";
        backEdge = edge;
        cout << "LLLLL\n";
    }

};

class Edge{
    public:
    Node* to;
    Node* from;
    Edge* reverse;
    bool reverseEdge;
    int original;
    int residual;
    Edge(class Node* to, class Node* from, bool reverse){
        
        if(reverse == false){
            this->to = to;
            this->from = from;
            reverseEdge = reverse;
            original = 1;
            residual = 0;
        Edge::setReverse(to, from);
        }else if(reverse == true){
            original = 0;
            residual = 1;
            this->to = from;
            this->from = to;
            reverseEdge = reverse;
        }
    }
    ~Edge(){};
    void setReverse(class Node* to, class Node* from){
        Edge* e = new Edge(from, to, true);
        reverse = e;
    }
    void swapOrigAndRes(){
        if(original == 1){
            original = 0;
            residual = 1;
        }else if(original == 0){
            residual = 0;
            original =1;
        }
    }
};
//need to find way to make edges so we can add them to adj matrix. sink->dice    
//dice-ifContainLetter->Word     
//word->sink
class Graph{
    public:
    vector<Node*> nodes;
    vector<int> spellingID;
    int min_nodes;
    string word;

    Graph(){
        Node* n = new Node(0, SOURCE);
        nodes.push_back(n);
    }
    ~Graph(){};


    void addDiceToGraph(string dice, int id){
        cout << "test1\n";
            Node* n = new Node(id, DICE);
            nodes.push_back(n);
        cout << "test2\n";

            nodes[id]->setLetter(dice);
            cout << "test3\n";
            Edge* sToD = new Edge(nodes[id], nodes[0], false);
        

            nodes[0]->addEdge(sToD);
            nodes[id]->setBackEdge(sToD);
    
    }


    void addWordToGraph(string word, int id){
        if(word == "sink"){
            Node* n = new Node(id, SINK);
            nodes.push_back(n);
        }else{
            int sinkID;
            int length = word.size();
            cout << "test1\n";
            vector<string> wordVec(length, "");
            cout << "test2\n";            
            for(int i = 0; i < length; i++){
                cout << "test3\n";
                wordVec[i] += word[i];
                cout << "test4\n";
                cout << wordVec[i] << "\n";
                Node* n = new Node(id+i, WORD);
                cout << "test5\n";

                nodes.push_back(n);
                cout << "test6\n";

                nodes[id+i]->setLetter(wordVec[i]);
                cout << "test7\n";

            }
            
        }
    }

    void connectDiceToLetter(Node* dice, Node* letter){
        for(int i = 0; i < 26; i++){
            if(dice->letters[i] == true && dice->letters[i] == letter->letters[i]){
                Edge* e = new Edge(letter, dice, false);
                dice->addEdge(e);
                letter[i].setBackEdge(e);
                cout << "connected dice: " << e->from->id << " to letter " << e->to->id << "\n";
            }
        }
    }

    void addSink(int startID){
        int sinkID = (min_nodes * 2) + 1;
        Node* s = new Node(sinkID, SINK);
        nodes.push_back(s);
        for(int i = startID; i <= min_nodes*2; i++){
            Edge* e = new Edge(s, nodes[i], false);
            nodes[i]->addEdge(e);
            s->setBackEdge(e);
            cout << "Connected word to sink ID: " << e->to->id << "\n";
        }

    }
    void setMinDice(int i){
        min_nodes = i;
    }

    bool bfs(){
        //psuedo code
        /*start at source, add node to frontier, set as visited
        add adj matrix to frontier, if not visited and edge.original = 1
        change edge and its reverse edge original and residual.
        set as visited
        */
        queue<Node*> q;
        vector<Node*> backTrack;

        q.push(nodes[0]);
        nodes[0]->visited = true;
        while(!q.empty()){
            Node* current = q.front();
            q.pop();
            for(int i = 0; i < current->adjMatrix.size(); i++){
                Edge* currentEdge = current->adjMatrix[i];
                Node* next = currentEdge->to;
                if(next->visited == true){
                    continue;
                }
                if(currentEdge->original == 1){
                    
                }
            }
            }





    }
    bool canSpell(){
        if(bfs()){
            return true;
        }else{
            return false;
        }
    }
    void deleteWordFromGraph();
    void printNodeOrder(string word);
};

int main(){
    string dice, word;
    int diceCount = 0;
    cout << "Dice count: ";
    Graph g;
    cin >> diceCount;
    cout << "Enter Dice: \n";
    for(int i = 0; i < diceCount; i++){
        cin >> dice;
        g.addDiceToGraph(dice, i+1);
    }
    g.setMinDice(diceCount);
    for(int i = 0; i <= diceCount; i++){
        cout<< "ID: " << g.nodes[i]->id << " ";
        for(int j =0; j < 26; j++){
            if(g.nodes[i]->letters[j] == true){
                cout << (char)(j +65);
            }
        }
        cout << " Linked to ";
        if(i == 0){
        for(int j = 0; j < g.nodes[0]->adjMatrix.size(); j++){
            cout << (g.nodes[0]->adjMatrix[j]->to->id) << ", ";
        }
        }
        if(i !=0){
            cout << "BACKEDGE: " << g.nodes[i]->backEdge->from->id;
    }
            cout << "\n";

    }




    
    cout << "enter Word: ";
    cin >> word;
    
    
        g.addWordToGraph(word, diceCount+1);
        
        cout << "massive w\n";

    
    for(int i = 0; i < word.size(); i++){
        cout<< "ID: " << g.nodes[i+diceCount]->id << " ";
        for(int j =0; j < 26; j++){
            if(g.nodes[i+diceCount]->letters[j] == true){
                cout << (char)(j +65);
            }
        }
        cout << " Linked to \n";
    }
    
    for(int i = 1; i <= diceCount; i++){
        for(int j = diceCount+1; j < diceCount + word.size()+1; j++)
        g.connectDiceToLetter(g.nodes[i], g.nodes[j]);
    }
    g.addSink(diceCount+1);
    for(int i = 0; i <= diceCount + word.size() + 1; i++){
        cout << "ID: " << g.nodes[i]->id << " ";
        for(int j =0; j < 26; j++){
            if(g.nodes[i]->letters[j] == true){
                cout << (char)(j +65);
            }
        }
        cout << " linked to ";
        for(int j = 0; j < g.nodes[i]->adjMatrix.size(); j++){
            cout << (g.nodes[i]->adjMatrix[j]->to->id) << ", ";
        }
        cout << "\n";
    }

    




}