#include<bits/stdc++.h>
using namespace std;

class trans
{
    string data;
    string tran;
    string VietnameseSigns[134] =
    {
        "á","à","ạ","ả","ã","â","ấ","ầ","ậ","ẩ","ẫ","ă","ắ","ằ","ặ","ẳ","ẵ",
        "Á","À","Ạ","Ả","Ã","Â","Ấ","Ầ","Ậ","Ẩ","Ẫ","Ă","Ắ","Ằ","Ặ","Ẳ","Ẵ",
        "é","è","ẹ","ẻ","ẽ","ê","ế","ề","ệ","ể","ễ",
        "É","È","Ẹ","Ẻ","Ẽ","Ê","Ế","Ề","Ệ","Ể","Ễ",
        "ó","ò","ọ","ỏ","õ","ô","ố","ồ","ộ","ổ","ỗ","ơ","ớ","ờ","ợ","ở","ỡ",
        "Ó","Ò","Ọ","Ỏ","Õ","Ô","Ố","Ồ","Ộ","Ổ","Ỗ","Ơ","Ớ","Ờ","Ợ","Ở","Ỡ",
        "ú","ù","ụ","ủ","ũ","ư","ứ","ừ","ự","ử","ữ",
        "Ú","Ù","Ụ","Ủ","Ũ","Ư","Ứ","Ừ","Ự","Ử","Ữ",
        "í","ì","ị","ỉ","ĩ",
        "Í","Ì","Ị","Ỉ","Ĩ",
        "đ",
        "Đ",    
        "ý","ỳ","ỵ","ỷ","ỹ",    
        "Ý","Ỳ","Ỵ","Ỷ","Ỹ" 
    };
    string VietnameseUnsigns[134] =     
    {
        "as","af","aj","ar","ax","aa","aas","aaf","aaj","aar","aax","aw","aws","awf","awj","awr","awx",
         "As","Af","Aj","Ar","Ax","AA","AAs","AAf","AAj","AAr","AAx","Aw","Aws","Awf","Awj","Awr","Awx",
         "es","ef","ej","er","ex","ee","ees","eef","eej","eer","eex",
         "Es","Ef","Ej","Er","Ex","EE","EEs","EEf","EEj","EEr","EEx",
         "os","of","oj","or","ox","oo","oos","oof","ooj","oor","oox","ow","ows","owf","owj","owr","owx",
         "Os","Of","Oj","Or","Ox","OO","OOS","OOf","OOj","OOr","OOx","Ow","Ows","Owf","Owj","Owr","Owx",
         "us","uf","uj","ur","ux","W","uws","uwf","uwj","uwr","uwx",
         "Us","Uf","Uj","Ur","Ux","Uw","Uws","Uwf","Uwj","Uwr","Uwx",
         "is","if","ij","ir","ix",
         "Is","If","Ij","Ir","Ix",
         "dd",
         "DD",    
         "ys","yf","yj","yr","yx",    
         "Ys","Yf","Yj","Yr","Yx" 
    };
public:
    trans(string);
    ~trans();
    string transfer(const string&);
    string inverse(const string &);
    friend ostream &operator<<(ostream &,const trans &);
};
trans::trans(string t):data(t)
{}
trans::~trans()
{
    delete[] VietnameseSigns;
    delete[] VietnameseUnsigns;
}
string trans::transfer(const string &t)
{
    string tmp=t;
    for (int i = 0; i < 134; i++)
    {
        size_t pos = 0;
        while ((pos = t.find(VietnameseSigns[i], pos)) != std::string::npos) 
        {
            tmp.replace(pos,  VietnameseSigns[i].length(),  VietnameseUnsigns[i]);
            pos += VietnameseUnsigns[i].length();
        }
    }
    return tmp;
}
string trans::inverse(const string &t)
{
    string tmp=t;
    for (int i = 0; i < 134; i++)
    {
        size_t pos = 0;
        while ((pos = t.find(VietnameseUnsigns[i], pos)) != std::string::npos) 
        {
            tmp.replace(pos, VietnameseUnsigns[i].length(), VietnameseSigns[i]);
            pos += VietnameseSigns[i].length();
        }
    }
    return tmp;
}