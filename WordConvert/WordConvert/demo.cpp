/*
 * 一个单词直译的程序
 * 使用了自己实现的mystring
 * 踩了超多坑。。。。
 * 1. 由于map是个有序关联容器，所以会在内部给key排序，所以要写比较运算符，排序就要有比较
 * 2. 然后比较运算符的参数还要是const，函数好像也一定要是const成员函数，否则会出现错误：error C2678 二进制< 没有找到接受const类型的左操作数的运算符
 * 3.
 * 4.
 * .............等等
 * 实现map。。。。。。。。。不会啊
 */

#include "Wordmap.h"
#include "mystring.h"
using namespace std;

typedef float vec3_t[3];

float VectorLength(const vec3_t v);

int main() {
    /*
    ifstream map_file("map_f.txt"), input_file("input_f.txt");

    Wordmap demo(map_file);
    demo.output(input_file);
	*/

    char c('dksf');
    char c1 = 1684763494;
    cout << c << endl;
    cout << c1;

    /*
    cout << sizeof(bool) << endl;
    cout << sizeof(int) << endl;
    cout << sizeof(char) << endl;
    cout << sizeof(char *) << endl;
    cout << sizeof(int *) << endl;
    cout << sizeof(void *) << endl;

    mystring s1("abc");
    mystring s2("cd");
    cout << s1 + s2;
	*/
    return 0;
}