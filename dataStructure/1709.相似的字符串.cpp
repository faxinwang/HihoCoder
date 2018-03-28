/*
ʱ������:10000ms
����ʱ��:1000ms
�ڴ�����:256MB
����
����������һ�ֹ��ϵļ��ܷ���������26��Ӣ����ĸ'A'-'Z'����ѭ���ƶ�Kλ���õ��µ������

����K=2����:

ABCDEFGHIJKLMNOPQRSTUVWXYZ
CDEFGHIJKLMNOPQRSTUVWXYZAB
����'C'���'A'��'D'���'B'����  

��������ֻ������д��ĸ���ַ���A��B�����A��B������ͬ������A����ͨ��ĳ��(ĳ��K)�������ܵõ�B��
���Ǿ���ΪA��B�����Ƶġ�

����"ABC"��"DEF"���ƣ�"HI"��"ZA"���ơ���Ȼ"����"��ϵ���д����ԺͶԳ��ԡ�    

����N���ַ��������㽫���Ƶ��ַ����۳�һ�࣬����������м�����ͬ�����

����
��һ�а���һ������N��  
����N��ÿ�а���һ���ַ���S��Sֻ������д��ĸ��  
����50%�����ݣ�1 �� N �� 100��N���ַ����ܳ��Ȳ�����10000��  
����100%�����ݣ�1 �� N �� 100000��N���ַ����ܳ��Ȳ�����1000000��

���
һ��������ʾ�𰸡�

��������
6  
ABC
DEF  
ZAB  
HIHO  
JKJQ  
NONU

�������
2

����˼·�� 
�������ַ�����ת����һ���ַ�Ϊ'A'������set��ȥ��, ���set��Ԫ�صĸ�������
��ͬ����ַ����ĸ����� 
*/
#include<iostream>
#include<cstdio>
#include<string>
#include<set>
using namespace std;


int main()
{
#ifdef WFX
freopen("in.txt","r",stdin);
#endif
    int N;
    string str;
    set<string> s;
    scanf("%d",&N);
    while(N--)
    {
        cin>>str;
        int offset = str[0] - 'A';
        for(int i=0,n=str.size(); i<n; ++i) str[i] = (str[i] -  offset + 26) % 26;
        s.insert(str);
    }
    cout<<s.size()<<endl;

    return 0;
}
