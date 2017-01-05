[![](https://img.shields.io/badge/VisualStudio-2013%20Community-ff69b4.svg)](https://support.microsoft.com/ja-jp/kb/3021976)
[![](https://img.shields.io/badge/DirectXSDK-June%202010-yellow.svg)](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
[![](https://img.shields.io/badge/FBX%20SDK-2016.1-blue.svg)](http://usa.autodesk.com/adsk/servlet/pc/item?id=24535361&siteID=123112)
# KingdomCraft


![KingdomCraftイメージ画像](https://cloud.githubusercontent.com/assets/16873201/20256951/ffe0119c-aa89-11e6-80d6-514e860e5b2f.jpg)


ゲーム概要
---
プレイヤーは小国の王となり、国を発展させていく。  
王としてやるべきことは様々だが、基本的にはプレイヤーのやりたいように国を発展させていく

* #### プラットフォーム
  * Windows

* #### プレイ人数
  * 一人用


プロジェクトをビルドするための準備
---

KigdomCraftのプロジェクトをビルドするには必要なツールとsdkを用意する必要があります。

* 必要なツール
  * Visual Studio 2013  


* 必要なsdk  
  * Microsoft DirectX SDK (June 2010)  [こちら](https://www.microsoft.com/en-us/download/details.aspx?id=6812)  
    Microsoft DirectX SDkはダウンロードしたexeに従えば簡単にインストールできます。

  * Autodesk Fbxsdk(2016.1)  [こちら](http://usa.autodesk.com/adsk/servlet/pc/item?id=24535361&siteID=123112)  
    FbxsdkはVisualStudioの環境によってダウンロードするファイルが変わりますのでVisualStudio2013のバージョンをダウンロードしてくだい。  
    こちらもダウンロードしたexeに従えばインストールできます。

    sdkをダウンロードしたら以下の環境変数を登録してください  
    * FBXSDK_INCLUDE_DIR  
      fbxsdkのインクルードディレクトリ  
      例 : C:\Program Files\Autodesk\FBX\FBX SDK\2016.1\include

    * FBXSDK_LIB_DIR  
      fbxsdkのライブラリディレクトリ  
      例 : C:\Program Files\Autodesk\FBX\FBX SDK\2016.1\lib\vs2013\x86
