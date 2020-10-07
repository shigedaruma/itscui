//
//  typeid.name の型名記号を解析して型名に変換するクラス
//
//  20-05-16
//  Shigeyuki Itoh
//




#ifndef ITS_TYPE_NAME_PARSER
#define ITS_TYPE_NAME_PARSER

#include "itstypes.h"

namespace its
{

// 型名を文字列で取得する
//
//  char const* name = TypeName(変数);
//  ※ printf の %s の引数にする場合 char const* へのキャストが必要
class TypeName
{
private:
    std::unique_ptr<char[]> m_string;

    // 型名のパース
    //  val: 値
    //  lambda: ヒットするたびに呼び出されるラムダ式
    void parse(auto val, std::function<void(char const* str)> lambda)
    {
        // 型変換リスト
        //  [0] が Key
        //  [2] が Value
        static char const* types[] =
        {
            "c:char",
            "s:short",
            "i:int",
            "l:long",
            "x:long long",
            "h:unsigned char",
            "t:unsigned short",
            "j:unsinged int",
            "m:unsigned long",
            "y:unsigned long long",
            "f:float",
            "d:double"
        };

        // 修飾子変換リスト
        //  [0] が Key
        //  [2] が Value
        static char const* decors[] =
        {
            "K: const",
            "P:*"
        };

        // 型名キーワードを取得
        char const* type = typeid(val).name();
        
        // 型名キーワードの先頭位置（最初は 0）
        size_t tail = strlen(type) - 1;
        bool known = false;

        // 一致するものを探す
        for(char const* t : types)
        {
            if(t[0] == type[tail])
            {
                lambda(&t[2]);
                // 見つかったフラグ
                known = true;
                break;
            }
        }
        // 不明の型の場合
        if(known == false)
        {
            // [] で囲ってとりあえず表示
            //  見つけ次第リストを増やす
            char unknown[] = "[.]";
            unknown[1] = type[tail];
            lambda(unknown);
        }

        // 型名キーワードが 1 文字じゃない場合
        if(tail > 0)
        {
            // 修飾子の追記
            for(size_t i = 0; i < tail; i++)
            {
                // 一致するものを探す
                for(char const* d : decors)
                {
                    if(d[0] == type[tail - i])
                    {
                        lambda(&d[2]);
                        break;
                    }
                }
            }
        }
    }

public:
    // コンストラクタ
    //  val :対象の変数
    //  fmt :つけたい装飾
    //      :printf フォーマット
    //      :%s を一つだけ含む
    TypeName(auto val, char const* fmt = nullptr) : m_string()
    {
        size_t len = 1;
        parse(val, [&] (char const* str) { len += strlen(str); });
        std::unique_ptr<char[]> name(new char[len]);
        name[0] = '\0';
        parse(val, [&] (char const* str) { strcat(name.get(), str); });

        if(fmt == nullptr)  { fmt = "%s"; }
        m_string.reset(new char[strlen(fmt) + len]);
        sprintf(m_string.get(), fmt, name.get());
    }

    // char const による参照
    operator char const* () { return m_string.get(); }
};

} // namespace its

#endif // ITS_TYPE_NAME_PARSER
