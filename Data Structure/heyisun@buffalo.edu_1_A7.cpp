#include "A7.hpp"
#include<algorithm>
#include<vector>
#include<map>
//#include<iostream>


class Node{
public:
	bool wordEnd;
	std::map<char,Node*> mmp;
	unsigned int countWords;
	
	Node(){
		wordEnd=false;
		Node* next= nullptr;
        countWords=0;
	}

	~Node(){

	}
	

};

Node* buildTree(const std::vector<std::string>& seqs){
		Node* root= new Node();
		Node* curr;
		for(int i=0;i<seqs.size();i++)
		{
            curr=root;
			std::string tmp=seqs[i];
			
			for(int j=0;j<tmp.size();j++){
				if(curr->mmp[tmp[j]]==0)
					curr->mmp[tmp[j]]=new Node();
				if(tmp.size()==j+1)
					curr->mmp[tmp[j]]->wordEnd=true;
				curr=curr->mmp[tmp[j]];
				
			}

		}
        curr=nullptr;
		return root;
}


unsigned int countOccurrences(const std::string& seq, const std::string& text){
    int m=seq.length();
    int n=text.length();
    int j=0;

    for(int i=0;i<n-m+1;i++){
        std::string cutStr=text.substr(i,m);
        if(cutStr==seq)
            j++;
    }
    return j;
}


void searchTree(Node* root,const std::string& text,int j){
    Node* curr=root;
    for(int i=j;i<text.size();i++){
        if(curr->mmp[text[i]]==nullptr) {
            return;
        }
        else {
            curr = curr->mmp[text[i]];
            if (curr->wordEnd == true) {
                curr->countWords+=1;
            }



        }
    }
    curr=nullptr;
}

std::vector<unsigned int> recordCount(Node* root,const std::vector<std::string>& seqs){
    std::vector<unsigned int> result;
    Node* curr;
    for(int i=0;i<seqs.size();i++)
    {
        curr=root;
        std::string tmp=seqs[i];


        for(int j=0;j<tmp.size();j++){
            curr=curr->mmp[tmp[j]];
        }
        unsigned int aaaa=curr->countWords;
        result.push_back(aaaa);

    }

    curr=nullptr;
    return result;

}



void deconTree(Node* pp){
    char m;
    Node* curr=pp;
    for(m='a';m<='z';m++){
        if(curr->mmp[m]!=nullptr)
        {
            deconTree(curr->mmp[m]);
        }
    }
    curr= nullptr;
    delete pp;

}

std::string jinWei(std::string a){
    //std::cout<<a<<std::endl;

    a[3]++;
    for(int i=3;i>=0;i--){
        if(a[i]>122){
            a[i]=a[i]-26;
            if(i!=0)
                a[i-1]++;
        }
    }
    //std::cout<<a<<std::endl;
    return a;
}
std::vector<unsigned int> countOccurrences(const std::string& text){
    std::vector<unsigned int> aa;
    std::map<std::string,unsigned int> tmp;
    if(text.size()>=4)
    {
    for(int i=0;i<text.size()-3;i++)
    {
        std::string cutStr=text.substr(i,4);
        tmp[cutStr]++;
    }}
	std::string j="aaaa";
    for(;j!="zzzz";j=jinWei(j)){
        aa.push_back(tmp[j]);
    }
	aa.push_back(tmp[j]);
	tmp.clear();
    return aa;
}

std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text){
    int i;
    std::vector<unsigned int> result;
    Node* mmTree=buildTree(seqs);
    for(i=0;i<text.size();i++){
        searchTree(mmTree, text, i);
    }
    result=recordCount(mmTree,seqs);
    deconTree(mmTree);
    return result;

}

std::vector<unsigned int> countOccurrences(const std::vector<std::string>& seqs, const std::string& text, bool bonus){
    std::vector<std::string> seqss;
    std::string ss;
    for(int i=0;i<seqs.size();i++){
        for(int j=0;j<seqs.size();j++){
            ss=seqs[i]+seqs[j];
            seqss.push_back(ss);
        }
    }

    return countOccurrences(seqss,text);

}
// Put your function definitions here.
