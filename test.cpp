#include <iostream>
#include "src/json_lite.h"

using namespace std;
using namespace json_lite;

void test(string);
string get_filename(string);

int main(int argc, char** argv)
{
    // supposed to be passed 
    try
    {
        test("tests\\pass1.json");
        test("tests\\pass2.json");
        test("tests\\pass3.json");
    }
    catch (const char* errmsg)
    {
        cout << errmsg << endl;
    }
    
    // supposed to be failed 
    char temp[10];
    for (int i = 1; i <= 33; i++)
    {
        memset(temp, 0, 10);
        sprintf(temp, "tests\\fail%d.json", i);
        try
        {
            test(temp);
        }
        catch (const char* errmsg)
        {
            cout << errmsg << endl;
        }
    }

    system("pause");
    return 0;
}

void test(string input)
{
    cout << "parsing " << input << " :" << endl;
    string output = "output\\";
    json_parser parser(input);
    json_value *doc = parser.run();
    if (doc)
    {
        doc->output(output + get_filename(input));
        delete doc;
        cout << "successful~\n" << endl;
        return;
    }
    cout << endl;
}

string get_filename(string path)
{
    string::size_type pos = path.rfind('\\');
    return string(path, pos + 1, string::npos);
}