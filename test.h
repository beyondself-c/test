#include <stdio.h>
#include <time.h>

//ʵ��LOG��־��ӡ
//�ڶ��У���ӡ�ļ��������������к�
//�����У���TEST����Ĳ���
#define LOG(frm,args...){\
        printf("[%s:%s:%d] ",__FILE__,__func__,__LINE__);\
        printf(frm,##args);\
        printf("\n");\
}


//ʵ��EXPECTϵ�з�װ
//func_flag=0�����Գ���ʱ��Ϊ0����ʾ���󲻴�ӡ����������ȷ֮�����Ϣ
#define EXPECT(a,comp,b){\
        __typeof(a)__a=(a),__b=(b);\
        if(!((a)comp(b)))\
        {\
          printf(RED("%s:%d:Failure\n"),__FILE__,__LINE__);\
          printf(" Expected:((%s)%s(%s)),actual:%d vs %d\n",\
                   #a,#comp,#b,__a,__b);\
          func_flag=0;\
        } \
}

#define EXPECT_EQ(a,b) EXPECT(a,==,b)          //==
#define EXPECT_NE(a,b) EXPECT(a,!=,b)          //!=
#define EXPECT_LT(a,b) EXPECT(a, <,b)          //<
#define EXPECT_LE(a,b) EXPECT(a,<=,b)          //<=
#define EXPECT_GT(a,b) EXPECT(a, >,b)          //>
#define EXPECT_GE(a,b) EXPECT(a,>=,b)          //>=

//ʵ��colorϵ�з�װ
//��ɫ�������ʽ "\033[0;a;bm������"
#define COLOR(msg,code) "\033[0;"#code "m" msg  "\033[0m" 
#define RED(msg)    COLOR(msg,31)
#define GREEN(msg)  COLOR(msg,32)
#define YELLOW(msg) COLOR(msg,33)
#define BLUE(msg)   COLOR(msg,34) 

//ʵ��TEST�ķ�װ

#define FUNC_NAME(a,b) wonderful_##a##_##b


//__attrinute__((constructor)) ����ע�ắ��������������ִ�С�
#define TEST(a,b)  \
  void FUNC_NAME(a,b)();\
  __attribute__((constructor))\
  void reg_##wonderful_##a##_##b(){\
  add_test_function( FUNC_NAME(a,b),#a "." #b);\
  return ;\
}\
void FUNC_NAME(a,b)()


//�洢��������
//void (*func)();��������������ַ
// const char *func_name; ������
struct Funcdate
{
  void (*func)();
  const char *func_name; 

}func_arr[100];

//�洢���������ĸ���
int func_arr_cnt=0; 
//����������ȷ������־  1-��ȷ 0-����
int func_flag;

//�洢������������һ������-������ַ �ڶ�����-������
void add_test_function( void (*func)(),const char *func_name)
{
  func_arr[func_arr_cnt].func=func;
  func_arr[func_arr_cnt].func_name=func_name;
  func_arr_cnt+=1;
  return ;
}

const char *RUN=     GREEN("[   RUN  ]");
const char *OK=      GREEN("[    OK  ]");
const char *FAILED=  RED  ("[FAILED  ]");


//ʵ��RUN_ALL_TEST�ķ�װ
int  RUN_ALL_TESTS()
{
  for(int i=0;i<func_arr_cnt;i++)
  {
    printf("%s  %s\n",RUN,func_arr[i].func_name);
    func_flag=1;
    long long b=clock();
    func_arr[i].func();
    long long e=clock();
    if(func_flag)  printf("%s",OK);
    else           printf("%s  ",FAILED);

    printf("%s "YELLOW( "(%lld ms)" )" \n",\
          func_arr[i].func_name,(e-b)*1000 /CLOCKS_PER_SEC);
  }
}

