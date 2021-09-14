#include <stdio.h>
#include <time.h>

//实现LOG日志打印
//第二行：打印文件名，函数名，行号
//第三行：大（TEST）里的参数
#define LOG(frm,args...){\
        printf("[%s:%s:%d] ",__FILE__,__func__,__LINE__);\
        printf(frm,##args);\
        printf("\n");\
}


//实现EXPECT系列封装
//func_flag=0，测试出错时置为0，提示错误不打印其他测试正确之类的信息
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

//实现color系列封装
//颜色的输出格式 "\033[0;a;bm接内容"
#define COLOR(msg,code) "\033[0;"#code "m" msg  "\033[0m" 
#define RED(msg)    COLOR(msg,31)
#define GREEN(msg)  COLOR(msg,32)
#define YELLOW(msg) COLOR(msg,33)
#define BLUE(msg)   COLOR(msg,34) 

//实现TEST的封装

#define FUNC_NAME(a,b) wonderful_##a##_##b


//__attrinute__((constructor)) 用于注册函数，先于主函数执行。
#define TEST(a,b)  \
  void FUNC_NAME(a,b)();\
  __attribute__((constructor))\
  void reg_##wonderful_##a##_##b(){\
  add_test_function( FUNC_NAME(a,b),#a "." #b);\
  return ;\
}\
void FUNC_NAME(a,b)()


//存储测试用例
//void (*func)();测试用例函数地址
// const char *func_name; 函数名
struct Funcdate
{
  void (*func)();
  const char *func_name; 

}func_arr[100];

//存储测试用例的个数
int func_arr_cnt=0; 
//测试用例正确与错误标志  1-正确 0-错误
int func_flag;

//存储测试用例，第一个参数-函数地址 第二参数-函数名
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


//实现RUN_ALL_TEST的封装
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

