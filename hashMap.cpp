/*****************************************************************************
*  @file     hashMap.cpp                                                     *
*  @brief    Get the 100 urls that appear most frequently in all files       *
*                                                                            *
*  @author   Wenqi Xu                                                        *
*  @email    wenqixu320@gmail.com                                            *
*  @version  1.0.                                                            *
*                                                                            *
*****************************************************************************/

#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;

/** 
 * @brief Url and Url repeat count 
 */
struct mp{
        string url;
        int count;
}temp_mp;

//
/** 
 * @brief Reload compare function in make_heap()
 * @param two strcut mp include Url and Url repeat count
 *
 * @return 
 *      Repeat more URL
 *     
 */
bool cmp(mp x,mp y) 
{
    try
    {
        if(x.count < 0 || y.count <0)
        {
            throw -1;
        } 
    }
    catch(int)
    {
        cout << "Illegal input " << "x.count=" <<x.count <<" "<<"y.count="<<y.count;
    }  
    return x.count >  y.count;
} 

/** 
 * @brief Get 100 most frequently appearing URL files in a file
 * @param str   file name
 *
 * @return 
 *      top 100 most frequently appearing URL files in a  file
 *     
 */
vector<mp> top100(string str)
{
    //Input file
    ifstream input;
    string input_file = str + ".txt";


    input.open(input_file.data());
    if(input==NULL)
    { 
       cout<<"Cannot open file.";
    } 
           
    /**
    * @brief url_map_count
    *
    * Use map to record how often each URL occurs 
    * 
    */
    map<string,int> url_map_count;
    map<string, int>::iterator iter;
    string eachline;
    try
    {
        while (getline(input, eachline))
        {
    	   url_map_count[eachline]++;	
        }
        input.close();
    }
    catch(const exception& e)
    {
        input.close();
        cerr << e.what() << endl;
    }

    /**
    *  @brief  Create heap
    *
    **/
    vector<mp> v(101);
    make_heap(v.begin(),v.end(),cmp);
    
    /**
    *  @brief  Use max heap filtering
    *
    **/
    iter = url_map_count.begin();
    while(iter!=url_map_count.end())
    {
    	temp_mp.url = iter->first;
    	temp_mp.count = iter->second;
        v.push_back(temp_mp);
    	push_heap(v.begin(),v.end(),cmp);
    	iter++;
    }

    /**
    *  @brief  sort heap
    *
    **/
    sort_heap(v.begin(),v.end(),cmp);
    return v;
}

/** 
 * @brief Integer conversion to String
 * @param int format
 *
 * @return 
 *     string format
 *     
 */
string getstring ( const int n )
{
	stringstream newstr;
	newstr<<n;
	return newstr.str();
}
/**
 * @brief Check if the input is number
 * @param string
 *
 * @return
 *     Bool
 *
 */
bool isnum(string s)  
{  
        stringstream sin(s);  
        double t;  
        char p;  
        if(!(sin >> t))  
               return false;  
        if(sin >> p)  
                return false;  
        else  
                return true;  
} 
 
int main(int argc, char **argv)
{
    vector<mp> t(101);
    if(isnum(argv[1])==false)
    {
	cout << "Wrong input,except number"<<endl;
	return 0;
    }
    int number =100;
    number = atoi(argv[1]);
    if(number <= 0)
    {
	cout << "Wrong input,except an positive integer"<<endl;
	return 0;
    } 
    make_heap(t.begin(),t.end(),cmp);
    for(int i=0;i<number;i++)
    {   
        /**
        *  @brief  Get a Top100 for each small file and use heap to get final Top100
        *
        **/
        vector<mp> b = top100(getstring(i));
        cout<<"Now Reading File "<<i<<endl;
        for(int j =0;j<100;j++)
        {
	    //cout << b[j].url<<" "<<b[j].count<<endl;
            t.push_back(b[j]);
            push_heap(t.begin(),t.end(),cmp);
        }
    }
    
    /**
    *Sort elements in a heap
    *
    **/
    sort_heap(t.begin(),t.end(),cmp);

    /**
    *  @brief  Output the final Top100
    *
    **/
    for(int i=0;i<100;i++)
    {
        cout<<i<<" "<<t[i].url<<" "<<t[i].count<<endl;
    }

    return 0;
}
