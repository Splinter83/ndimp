#ifndef  _TYPE_LIST_H_
#define  _TYPE_LIST_H_

struct NullType
{
};


template <typename H, typename T> struct TypeList
{
  typedef H head;
  typedef T tail;
};

#define TYPELIST_1(t1)                      														TypeList<t1,NullType>
#define TYPELIST_2(t1,t2)                   														TypeList<t1,TYPELIST_1(t2) >
#define TYPELIST_3(t1,t2,t3)                														TypeList<t1,TYPELIST_2(t2,t3) >
#define TYPELIST_4(t1,t2,t3,t4)             														TypeList<t1,TYPELIST_3(t2,t3,t4) >
#define TYPELIST_5(t1,t2,t3,t4,t5)          														TypeList<t1,TYPELIST_4(t2,t3,t4,t5) >
#define TYPELIST_6(t1,t2,t3,t4,t5,t6)       														TypeList<t1,TYPELIST_5(t2,t3,t4,t5,t6) >
#define TYPELIST_7(t1,t2,t3,t4,t5,t6,t7)    														TypeList<t1,TYPELIST_6(t2,t3,t4,t5,t6,t7) >
#define TYPELIST_8(t1,t2,t3,t4,t5,t6,t7,t8) 														TypeList<t1,TYPELIST_7(t2,t3,t4,t5,t6,t7,t8) >
#define TYPELIST_9(t1,t2,t3,t4,t5,t6,t7,t8,t9) 														TypeList<t1,TYPELIST_8(t2,t3,t4,t5,t6,t7,t8,t9) >
#define TYPELIST_10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10) 												TypeList<t1,TYPELIST_9(t2,t3,t4,t5,t6,t7,t8,t9,t10) >
#define TYPELIST_11(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11) 											TypeList<t1,TYPELIST_10(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11) >
#define TYPELIST_12(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12) 										TypeList<t1,TYPELIST_11(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12) >
#define TYPELIST_13(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13) 									TypeList<t1,TYPELIST_12(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13) >
#define TYPELIST_14(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14) 								TypeList<t1,TYPELIST_13(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14) >
#define TYPELIST_15(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15) 							TypeList<t1,TYPELIST_14(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15) >
#define TYPELIST_16(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16) 						TypeList<t1,TYPELIST_15(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16) >
#define TYPELIST_17(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17) 					TypeList<t1,TYPELIST_16(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17) >
#define TYPELIST_18(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18) 				TypeList<t1,TYPELIST_17(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18) >
#define TYPELIST_19(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19) 			TypeList<t1,TYPELIST_18(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19) >
#define TYPELIST_20(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20) 		TypeList<t1,TYPELIST_19(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20) >
#define TYPELIST_21(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21) 	TypeList<t1,TYPELIST_20(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21) >
#define TYPELIST_22(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22) TypeList<t1,TYPELIST_21(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22) >
#define TYPELIST_23(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23) TypeList<t1,TYPELIST_22(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23) >
#define TYPELIST_24(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24) TypeList<t1,TYPELIST_23(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24) >
#define TYPELIST_25(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24,t25) TypeList<t1,TYPELIST_24(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24,t25) >
#define TYPELIST_26(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24,t25,t26) TypeList<t1,TYPELIST_25(t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24,t25,t26) >


template <bool b,class Type1, class Type2> struct SelectType;

template <class Type1, class Type2> struct SelectType<true,Type1, Type2>
{
  typedef Type1 Result;
};

template <class Type1, class Type2> struct SelectType<false,Type1, Type2>
{
  typedef Type2 Result;
};

template <typename T, typename R> struct IsSameType
{
  public:
    enum {Result = 0};
};

template <typename T> struct IsSameType<T,T>
{
  public:
    enum {Result = 1};
};


template <bool b> struct CompileTimeAssertion
{
  private:
    struct TrueClass
    {
      static void AssertionCheck(){};
    };

    struct FalseClass
    {
    };


    typedef typename SelectType<b,TrueClass,FalseClass>::Result AssertionClass;

  public:
    static void Assert()
    {
      AssertionClass::AssertionCheck();
    }
};

#define ASSERT_SIZEOF_LT(a) CompileTimeAssertion< (sizeof(*this)<=(a) ) >::Assert();


template <class TL, int index, typename DefaultType> struct TypeAt;

template <int index> struct TypeAt<NullType,index,NullType>
{
  typedef NullType Result;
};

template <class Head, class Tail, int index, typename DefaultType>
   struct TypeAt<TypeList<Head,Tail> ,index,DefaultType>
{
  typedef typename SelectType<
                       (index==0),
                       Head,
                       typename SelectType<
                         (index>0),
                         typename TypeAt<Tail, index-1, DefaultType >::Result,
                         DefaultType
                       >::Result
                    >::Result     Result;

};

#endif

