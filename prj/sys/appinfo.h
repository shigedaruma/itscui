//
//  title: appinfo.h
//  description: アプリケーション情報
//  author: Shigeyuki Itoh
//  date: 20-05-03
//

#ifndef APPINFO_H
#define APPINFO_H

// アプリケーションの情報
struct AppInfo
{
    // アプリケーション名
    char const* appname;
    // バージョン情報
    struct Version
    {
        // メジャー番号
        int maj;

        // マイナー番号
        int min;

        // リビジョン番号
        int rev;

        // コンストラクタ
        Version(int v1, int v2, int r) : maj(v1), min(v2), rev(r) {}
    };

    // 有効引数の数
    int argnum;

    // 引数情報
    struct Args
    {
        // ノーテーション
        char const* note;

        // 説明
        char const* desc;

        // オプショナル（省略可能）
        bool optional;
    };
};


#endif
