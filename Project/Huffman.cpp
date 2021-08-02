#include <bits/stdc++.h> 
#include"trans.h"
#define MAX_TREE_HT 256 
using namespace std; 
  
map<char, string> codes; 
  

map<char, int> freq; 
  
struct Tree 
{ 
    char data;              
    int freq;          
    Tree *left, *right; 
  
    Tree() 
    { 
        left = right = nullptr;  
    }
    Tree(char data, int freq) 
    { 
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
    }  
}; 
// Ham so sanh neu co tan so cao hon thi sang ben trai(0) nho hon thi ben phai(1)
struct compare 
{ 
    bool operator()(Tree* l, Tree* r) 
    { 
        return (l->freq > r->freq); 
    } 
}; 
  
//In gia tri nhi phan
void printCodes(struct Tree* root, string str) 
{ 
    if (!root) 
        return; 
    if (root->data != '$') 
        cout << root->data << ": " << str << "\n"; 
    printCodes(root->left, str + "0"); 
    printCodes(root->right, str + "1"); 
} 
  
// Luu tru ky tu cung voi gia tri nhi phan
void storeCodes(struct Tree* root, string str) 
{ 
    if (root==NULL) 
        return; 
    if (root->data != '$') 
        codes[root->data]=str; 
    storeCodes(root->left, str + "0"); 
    storeCodes(root->right, str + "1"); 
} 
  
// Tao cay Heap hay cay huffman trai thi la 0 con phai la 1
priority_queue<Tree*, vector<Tree*>, compare> minHeap; // khai bao ngan xep
  
// Ham xay dung cay nhi phan va luu tru trong minHeap 
void HuffmanCodes(int size) 
{ 
    struct Tree *left, *right, *top; //Tao ngan xep
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++) //Khai bao bien lap interator v de tan so ky tu
        minHeap.push(new Tree(v->first, v->second)); // Tao kich thuoc cho size minHeap theo so ky tu co trong file
    while (minHeap.size() != 1) 
    { 
        left = minHeap.top(); //phan tu co do uu tien lon nhat voi do uu tien tu trai sang phai va tu duoi len
        minHeap.pop(); //Xoa ky tu cua minHeap cho toi khi = 1 hay noi cach khac la xoa cay da duyet
        right = minHeap.top(); 
        minHeap.pop(); 
        top = new Tree('$', left->freq + right->freq); 
        top->left = left; 
        top->right = right; 
        minHeap.push(top); //day gia tri top len 1
    } 
    storeCodes(minHeap.top(), ""); 
} 

//Tinh tan so
void calcFreq(string str, int n) 
{ 
    for (int i=0; i<str.size(); i++) 
        freq[str[i]]++; 
} 
   
 
Tree Htree;
  
void buildHuffman(struct Tree* root,char bit, string bitcode) 
{ 
    Tree* curr=root;
        for(int i=0;i<(bitcode.size()-1);i++)
        {
            if (bitcode[i]=='0') 
            {

                if ((curr->left)==nullptr)
                {
                    curr->left=new struct Tree;
                }
                curr=curr->left;
            }
            else 
            {
                if (curr->right==NULL) curr->right=new struct Tree;
                curr=curr->right;
            }
        }     
        curr->data=bit;
}

string decoding(struct Tree* root, string s) 
{ 
    string ans = ""; 
    struct Tree* curr = root; 
    for (int i=0;i<s.size();i++) 
    { 
        if (s[i] == '0') 
           curr = curr->left; 
        else
           curr = curr->right; 
  
        if (curr->left==NULL and curr->right==NULL) 
        { 
            ans += curr->data; 
            curr = root; 
        } 
    } 
    return ans+'\0'; 
} 

int main() 
{   
    int compress;
    char filename[20],oname[20];
    FILE *input;
    fstream f;
    int co=0;
do
{
    do
	{
        cout<<"Ten thu muc: "<<endl;
        scanf("%s",filename);
        input = fopen(filename, "r");
        if(input==NULL) cout << "khong ton tai file yeu cau" << endl;
    }while (input==NULL);
    cout<<"Ten thu muc output: "<<endl;
    scanf("%s",oname);
    f.open(oname, ios::out);
    printf("\nNen(1) hoac giai nen(2):");
    scanf("%d",&compress);
    string encodedString, decodedString; 
    if (compress==1)
    {
        char* tmp;
        fgets(tmp,1000000000, input);
        string str = string(tmp);
        trans a(str);
        str=a.transfer(str);         
        calcFreq(str, str.length()); 
        HuffmanCodes(str.length());  
        for (auto v=codes.begin(); v!=codes.end(); v++)
        { 
            cout << v->first <<' ' << v->second << endl; 
            f << v->first <<' ' << v->second << endl;
        } 
        for (auto i: str) 
            encodedString+=codes[i];
        cout << encodedString;
        f <<encodedString;
        f.close();
    }
    //cout<<"tiep tuc(0/1):";cin>>co;
    if (compress==2)
    {
        char bit[256];
        string bitcode[256];  
        char c[10000];
        int i=0;
       do
	    {
            fgets(c,100000000,input);
            if((((c[0]=='0')||(c[0]=='1')))and(c[1]!=' ')) break;
            bit[i]=c[0];
            for(int j = 2;j<strlen(c);j++) bitcode[i]=bitcode[i]+c[j];
            i++;
	    }while(1);
        for(int j = 0;j<strlen(c);j++) encodedString=encodedString+c[j];
        for(int j = 0;j<i;j++)
        {
            buildHuffman(&Htree,bit[j],bitcode[j]);
        }
        decodedString = decoding(&Htree, encodedString); 
        cout << "\nDu lieu da duoc giai nen:\n" << decodedString << endl;
        f <<decodedString;  
        f.close();  
    }
    cout<<"tiep tuc(0/1):";cin>>co;
}while(co==0); 
    return 0; 
}