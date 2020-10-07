// title: itsut.h
//
// author: Shigeyuki Itoh
// date: 20-05-12
//

// overview: 単体テストユーティリティ
// description:
//  単体テストのコードで利用されることを前提としている
//  テストする側なので何にも依存しない

#if UNIT_TESTING

#ifndef ITS_UNIT_TEST_UTILITY_H
#define ITS_UNIT_TEST_UTILITY_H

#include <functional>
#include <cstdio>
#include <cstring>

namespace its
{

namespace ut
{

// ユニットテストのログを出力するユニットテスト
class Logger
{
private:
    static int const kIndentDepth = 1024;

    // ログインデント
    int m_indent;

    // コールスタックバッファの長さ
    int m_length;

    // コールスタック
    std::unique_ptr<char const*[]> m_cstack;

    // シングルトンインスタンス
    Logger* s_instance = nullptr;

    Logger() : m_indent(0), m_length(kIndentDepth), m_cstack(new char const*[kIndentDepth])
    {
    }

public:
    Logger* Instance()
    {
        if(s_instance == nullptr)
        {
            s_instance = new Logger();
        }
        return s_instance;
    }

    // Enter 処理
    void Enter(char const* func)
    {
        // 次スタックを積んだらあふれる場合：バッファを増やす
        if(m_indent >= m_length)
        {
            int len = m_length;
            m_length += kIndentDepth;
            char const*[] tmp = m_cstack.release();
            m_cstack.reset(new char const*[m_length]);
            memcpy(m_cstack.get(), tmp, sizeof(char const*) * len);
            memset(&m_cstack[m_indent], nullptr, m_length - m_indent);
        }

        
    }

    // インデント付きで
};

// テスト失敗例外
//
//  使用例
//      try
//      {
//          : // test code
//          :
//          // in case of exception
//          throw FailureException(__func__, <cause>, <action to be executed>
//      }
//      catch(FailureException& e)
//      {
//          return e();    // action is excuted here
//      }
//
class FailureException
{
public:
    // デフォルト終了コード
    static int const kDefaultExitCode = -1;

private:
    // 失敗した関数名
    char const* m_at;

    // 原因
    char const* m_cause;

public:

    // コンストラクタ
    FailureException(char const* a, char const* c) : m_at(a), m_cause(c)
    {

                                            #if UNIT_TEST_TEST
                                            printf("\n");
                                            printf("ut:%s::ctor\n", __func__);
                                            printf("ut:\tm_at:%s\n", m_at);
                                            printf("ut:\tm_cause:%s\n", m_cause);
                                            #endif

    }

    // 関数オペレータ
    //  キャッチしたほうが呼び出すことを想定している
    int operator ()() const
    {
        fprintf(stderr, "Unit test failure\n\tat:%s()\n\tcause:%s\n", m_at, m_cause);
        return kDefaultExitCode;
    }

    // 発生位置
    char const* At() const { return m_at; }

    // 発生原因
    char const* Cause() const { return m_cause; }
};

// 比較処理
//  vl: 左辺値
//  vr: 右辺値
//  nl: 左辺値変数名
//  nr: 右辺値変数名
//  from: 呼出元関数名
//  fmt: 型
void compare(auto vl, auto vr, char const* nl, char const* nr, char const* from, char const* fmt, char const* cmp, std::function<bool()> judge)
{
                                            #if UNIT_TEST_TEST
                                            printf("ut:%s\n", __func__);
                                            printf("ut:\tnl:\"%s\", nr:\"%s\"\n", nl, nr);
                                            printf("ut:\tfrom:%s\n", from);
                                            printf("ut:\tfmt:%s\n", fmt);
                                            printf("ut:\tcmp:%s\n", cmp);
                                            #endif
    // キャプション
    char const* tmpl = "%%s(): test{ %%s (%s) %%s (%s) %%s } ";
    char format[strlen(fmt) * 2 + strlen(tmpl) + 1];
                                            #if UNIT_TEST_TEST
                                            printf("ut:\tsprintf(format, \"%s\", fmt:\"%s\", fmt:\"%s\");\n", tmpl, fmt, fmt);
                                            #endif
    sprintf(format, tmpl, fmt, fmt);
                                            #if UNIT_TEST_TEST
                                            printf("ut:\tformat[%llu] =\"%s\"\n", sizeof(format), format);
                                            #endif
    printf(format, from, nl, vl, cmp, vr, nr);

    // 型比較
    if(typeid(vl) != typeid(vr)) throw FailureException(from, "type miss match");

    // パスしなかったら例外スロー
    if(judge() == false) throw FailureException(from, "comparison failed");

    // 合格
    printf("--> passed\n");
}

} // namespace ut

} // namaespace its

#if 0
// NULL チェックマクロ
//  v が nullptr だったら FailureException を投げる
#define ITS_UT_NUL(v) if(v == nullptr) throw its::ut::FailureException(__func__, #v " is null")

// 比較マクロ
//  l: 左辺値
//  c: 比較演算子
//  r: 右辺値
//  f: フォーマット
#define ITS_UT_CMP(l, c, r, f, j)  its::ut::compare(l, r, #l, #r, __func__, f, #c, j)

// 文字列比較マクロ
//  l: 左辺値
//  c: 比較演算子
//  r: 右辺値
//  f: フォーマット
#define ITS_UT_STR(l, c, r) ITS_UT_NUL(l); ITS_UT_NUL(r); ITS_UT_CMP(l, c, r, "%s", ([&l, &r] () -> bool { return strcmp(l, r) c 0; }))

// 数値比較マクロ
//  l: 左辺値
//  c: 比較演算子
//  r: 右辺値
//  f: フォーマット
#define ITS_UT_VAL(l, c, r, f) ITS_UT_CMP(l, c, r, f, ([&l, &r] () -> bool { return l c r; }))




// EQual
#define ITS_UT_EQc(l, r) ITS_UT_VAL(l, ==, r, "%c")
#define ITS_UT_EQi(l, r) ITS_UT_VAL(l, ==, r, "%d")
#define ITS_UT_EQu(l, r) ITS_UT_VAL(l, ==, r, "%u")
#define ITS_UT_EQx(l, r) ITS_UT_VAL(l, ==, r, "%x")
#define ITS_UT_EQf(l, r) ITS_UT_VAL(l, ==, r, "%f")
#define ITS_UT_EQd(l, r) ITS_UT_VAL(l, ==, r, "%lf")
#define ITS_UT_EQs(l, r) ITS_UT_STR(l, ==, r)

// NotEqual
#define ITS_UT_NEc(l, r) ITS_UT_VAL(l, !=, r, "%c")
#define ITS_UT_NEi(l, r) ITS_UT_VAL(l, !=, r, "%d")
#define ITS_UT_NEu(l, r) ITS_UT_VAL(l, !=, r, "%u")
#define ITS_UT_NEx(l, r) ITS_UT_VAL(l, !=, r, "%x")
#define ITS_UT_NEf(l, r) ITS_UT_VAL(l, !=, r, "%f")
#define ITS_UT_NEd(l, r) ITS_UT_VAL(l, !=, r, "%lf")
#define ITS_UT_NEs(l, r) ITS_UT_STR(l, !=, r)

// LessEqual
#define ITS_UT_LEc(l, r) ITS_UT_VAL(l, <=, r, "%c")
#define ITS_UT_LEi(l, r) ITS_UT_VAL(l, <=, r, "%d")
#define ITS_UT_LEu(l, r) ITS_UT_VAL(l, <=, r, "%u")
#define ITS_UT_LEx(l, r) ITS_UT_VAL(l, <=, r, "%x")
#define ITS_UT_LEf(l, r) ITS_UT_VAL(l, <=, r, "%f")
#define ITS_UT_LEd(l, r) ITS_UT_VAL(l, <=, r, "%lf")

// GreaterEqual
#define ITS_UT_GEc(l, r) ITS_UT_VAL(l, >=, r, "%c")
#define ITS_UT_GEi(l, r) ITS_UT_VAL(l, >=, r, "%d")
#define ITS_UT_GEu(l, r) ITS_UT_VAL(l, >=, r, "%u")
#define ITS_UT_GEx(l, r) ITS_UT_VAL(l, >=, r, "%x")
#define ITS_UT_GEf(l, r) ITS_UT_VAL(l, >=, r, "%f")
#define ITS_UT_GEd(l, r) ITS_UT_VAL(l, >=, r, "%lf")

// LessThan
#define ITS_UT_LTc(l, r) ITS_UT_VAL(l, <, r, "%c")
#define ITS_UT_LTi(l, r) ITS_UT_VAL(l, <, r, "%d")
#define ITS_UT_LTu(l, r) ITS_UT_VAL(l, <, r, "%u")
#define ITS_UT_LTx(l, r) ITS_UT_VAL(l, <, r, "%x")
#define ITS_UT_LTf(l, r) ITS_UT_VAL(l, <, r, "%f")
#define ITS_UT_LTd(l, r) ITS_UT_VAL(l, <, r, "%lf")

// GreaterThan
#define ITS_UT_GTc(l, r) ITS_UT_VAL(l, >, r, "%c")
#define ITS_UT_GTi(l, r) ITS_UT_VAL(l, >, r, "%d")
#define ITS_UT_GTu(l, r) ITS_UT_VAL(l, >, r, "%u")
#define ITS_UT_GTx(l, r) ITS_UT_VAL(l, >, r, "%x")
#define ITS_UT_GTf(l, r) ITS_UT_VAL(l, >, r, "%f")
#define ITS_UT_GTd(l, r) ITS_UT_VAL(l, >, r, "%lf")

#endif

#endif  // ITS_UNIT_TEST_UTILITY_H

#define ITS_UT_COMPARE  its::ut::compare

#else

#define ITS_UT_COMPARE

#endif  // UNIT_TESTING

