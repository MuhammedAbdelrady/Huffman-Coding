#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>


using namespace std;
struct Node {   //tree node create
    char ch;
    int freq;
    Node *right , *left;
};
// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right){
	Node* node = new Node();
	node->ch = ch;    //الرمز
	node->freq = freq;  //التكرار
	node->left = left;  //النص الشمال
	node->right = right; //النص اليمين
	return node;
}
//comparison object to be used in heap
struct comp{
    bool operator()(Node* l , Node*r){
        return l->freq > r->freq;       		// highest priority item has lowest frequency

    }
};
//////////////////////////////////////////////////////////
//traverse huffman tree and store huffman code in a map
void encode (Node* root , string str , unordered_map<char,string>&huffmanCode){
    if(root==nullptr){ //first value is equal to null so it will be the root
        return;
    }
    if(!root->left && !root->right){
        huffmanCode[root->ch]=str;
    }
    encode(root->left,str+"0",huffmanCode);
    encode(root->right,str+"1",huffmanCode);
}
////////////////////////////////////////////////////////////
// traverse the Huffman Tree and decode the encoded string
void decode(Node* root, int &index, string str){
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right){
		cout << root->ch;
		return;
	}
	index++;
	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}
//////////////////////////////////////////////////
//here we have an tree to store frequency for each character
void buildhuffmantree (string text){
    unordered_map<char , int> freq ; //store freq in unordered map
    for (char ch : text){
        freq[ch]++;
    }
    ////////////////////////////
    //create priorty queue which it is a standard templete to store element من الكبير للصغير
    priority_queue<Node* , vector<Node*>,comp> huffmantree; //make another map to store high priority
    ////////////////////////////
    for (auto pair : freq){
        huffmantree.push(getNode(pair.first,pair.second,nullptr,nullptr));
    }
    while (huffmantree.size() != 1 ){
        //remove the smallest two freq node
        Node *left = huffmantree.top(); huffmantree.pop();
        Node *right = huffmantree.top(); huffmantree.pop();
        //add both to create a new node
        int sum = left->freq + right->freq;
        //return the result to the priority queue
        huffmantree.push(getNode('\0',sum,left,right));
    }
    Node* root = huffmantree.top(); //pointer on the root of huffman tree
    unordered_map<char,string> huffmanCode;
    encode(root,""/*nullptr*/,huffmanCode); //call encode function
    //print the huffman code
    cout<<"Huffman Code Is :\n"<<'\n';
    for ( auto pair: huffmanCode){
        cout<<pair.first<<" "<<pair.second<<'\n';
    }
    cout<<"Original String Is : \n"<<text<<'\n';

    //print encoded string
    string str ="";
    for (char ch:text){
        str+=huffmanCode[ch];
    }


    cout<<"Encoded String is : "<< str <<'\n';
    //traverse the tree again but know decode the encoded string
    int index=-1;
    cout<<"Decoded String is : ";
    while (index < (int)str.size()-2){
        decode(root,index,str);
    }
}

int main()
{   /*string mohamed="";

    ifstream Read ("huffman.txt" , ios::in);
    if (Read.is_open()){
        while(getline(Read.mohamed)){
            cout<<endl;
        }
        Read.close();
    }
    else{
        cout<<"Not Found File";
    }
    vector <std::string> names;
    string input;
    int j;
    while (file>>input){ // return the txt file
        names.push_back(input);
    }*/
    /*for(string name : names){
        cout<<name<<endl;
    }*/
    int arr[100];
    char str[100]="";
    cout<<"Enter Text:";
    gets(str);
    int sum=0;
    for (int i=65 ; i<=90 ; i++){
        int sum =0 ;
        for (int j=0 ; j<sizeof(str) ; j++){
                if((int)str[j]==i){
                    sum=sum+1;
                }
        }
        if(sum>0){
            cout<<(char)i<<"--comes--"<<sum<<"--times--"<<endl;
        }
    }
    buildhuffmantree(str);
    return 0;
}
