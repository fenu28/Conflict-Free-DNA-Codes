#include<bits/stdc++.h>
using namespace std;

// Function to convert a binary sequence to decimal
int binaryToDecimal(string s)
{
    int n = s.length();
    int res = 0;
    for(int i =0;i<s.length();i++)
    {
        int val = s[i]-'0';
        res = res + val*pow(2,s.length()-i-1);
    }
    return res;
}

//Funtion to get DNA complement of input DNA string
string getDNAComplement(string s)
{
    string res = "";
    for(int i = 0;i<s.length();i++)
    {
        if(s[i]=='A')
            res = res+'T';
        else if(s[i]=='G')
            res = res+'C';
        else if(s[i]=='C')
            res = res+'G';
        else if(s[i]=='T')
            res = res+'A';
    }
    return res;
}

// Function to convert decimal number to binary
string decToBinary(int n,int& maxLength)
{
    cout<<n<<endl;
    string res = "";
    int temp = n;
    while(temp!=0)
    {
        res = res+to_string(temp%2);
        temp = temp/2;
    }
    reverse(res.begin(),res.end());
    maxLength = max(maxLength,(int)res.length());
    return res;
}

int main()
{
    int n;
    cout<<"Enter number of integers to encode and decode"<<endl;
    cin>>n;
    int arr[n];
    string binary[n];
    int maxLength = 0;
    cout<<"Input integers: ";
    for(int i = 0;i<n;i++)
    {
        cin>>arr[i];
        binary[i] = decToBinary(arr[i],maxLength);
    }
    cout<<endl;

    // Create binary sequences from input integers
    for(int j=0;j<n;j++)
    {
        string s = binary[j];
        if(s.length()<maxLength)
        {
            int diff = maxLength - s.length();
            reverse(s.begin(),s.end());
            for(int i = 0;i<diff;i++)
            {
                s = s+'0';
            }
            reverse(s.begin(),s.end());
            binary[j] = s;
        }
    }

    string x,y;
    cout<<"Input and x any y inital DNA strings"<<endl;
    cin>>x>>y;
    string xc = getDNAComplement(x);
    string yc = getDNAComplement(y);

    // Mapping for encoding binary sequence to DNA
    map<pair<int,string>,string> encode;
    encode[make_pair(0,x)] = y;
    encode[make_pair(1,x)] = yc;
    encode[make_pair(0,xc)] = yc;
    encode[make_pair(1,xc)] = y;
    encode[make_pair(0,y)] = xc;
    encode[make_pair(1,y)] = x;
    encode[make_pair(0,yc)] = x;
    encode[make_pair(1,yc)] = xc;

    // Generating DNA strings from binary sequences
    string DNAcodes[n];
    for(int i = 0;i<n;i++)
    {
        string s = binary[i];
        //cout<<s<<endl;
        string sDNA = "";
        if(s[0]=='0')
            sDNA = sDNA + x;
        else
            sDNA = sDNA + y;
        for(int j = 1;j<s.length();j++)
        {
            string prev_block="";
            for(int z = x.length();z>0;z--)
            {
                prev_block = prev_block + sDNA[sDNA.length()-z];
            }
            if(s[j]=='0')
                sDNA = sDNA + encode[{0,prev_block}];
            else
                sDNA = sDNA + encode[{1,prev_block}];
        }
        DNAcodes[i] = sDNA;
    }
    for(int i = 0;i<n;i++)
        cout<<"Encoding of "<<arr[i]<<": "<<DNAcodes[i]<<endl;

    // Mapping for decoding DNA string to binary sequence
    map<pair<string,string>,int> decode;
    decode[make_pair(x,yc)] = 0;
    decode[make_pair(x,y)] = 1;
    decode[make_pair(xc,y)] = 0;
    decode[make_pair(xc,yc)] = 1;
    decode[make_pair(yc,x)] = 1;
    decode[make_pair(yc,xc)] = 0;
    decode[make_pair(y,x)] = 0;
    decode[make_pair(y,xc)] = 1;

    // Generaing binary sequences from DNA sequences
    string decodedBinary[n];
    for(int i = 0;i<n;i++)
    {
        string encodedDNA = DNAcodes[i];
        string binary = "";
        string first_block = "";
        first_block = first_block+encodedDNA[0];
        first_block = first_block+encodedDNA[1];
        if(first_block == x)
            binary = binary+'0';
        else
            binary = binary+'1';
        int ind = 0;
        for(int j = 2;j<encodedDNA.length();j+=x.length())
        {
            string curr_block = "";
            curr_block = curr_block + encodedDNA[j];
            curr_block = curr_block + encodedDNA[j+1];
            string prev_block = "";
            prev_block = prev_block + encodedDNA[ind];
            prev_block = prev_block + encodedDNA[ind+1];
            ind = j;
            binary = binary + to_string(decode[{curr_block,prev_block}]);
        }
        decodedBinary[i] = binary;
    }

    // Conversion of decoded binary sequence to integers
    int decimal[n];
    for(int i = 0;i<n;i++)
    {
        decimal[i] = binaryToDecimal(decodedBinary[i]);
    }
    for(int i = 0;i<n;i++)
        cout<<"Decoding of "<<DNAcodes[i]<<" = "<<decimal[i]<<endl;
    return 0;
}