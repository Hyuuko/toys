/*
 * һ������ֱ��ĳ���
 * ʹ�����Լ�ʵ�ֵ�mystring
 * ���˳���ӡ�������
 * 1. ����map�Ǹ�����������������Ի����ڲ���key��������Ҫд�Ƚ�������������Ҫ�бȽ�
 * 2. Ȼ��Ƚ�������Ĳ�����Ҫ��const����������Ҳһ��Ҫ��const��Ա�������������ִ���error C2678 ������< û���ҵ�����const���͵���������������
 * .............�ȵ�
 * ʵ��map���������������������ᰡ
 */

#include "Wordmap.h"
#include "mystring.h"
using namespace std;

int main() {
    ifstream map_f, input_f;
    map_f.open("map_f.txt");
    input_f.open("input_f.txt");

	Wordmap demo(map_f);
    demo.output(input_f);

    return 0;
}