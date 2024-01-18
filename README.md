このリポジトリは、Unreal Engine5 で開発したゲームを箱庭と連携して実行できるようにするためのプラグイン機能開発リポジトリです。

# アジェンダ

- [動作環境](#動作環境)
- [アーキテクチャ](#アーキテクチャ)
- [インストール手順](#インストール手順)
- [シミュレーション手順](#シミュレーション手順)
- [内部設計情報](#内部設計情報)

# 動作環境

サポート状況は以下のとおりです。

- [X] MacOS(AppleSilicon)
- [ ] MacOS(Intel)
- [ ] Windows
- [ ] Ubuntu

# アーキテクチャ

アーキテクチャ構成は下図のとおりです。

![スクリーンショット 2024-01-19 6 17 41](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/dd56c3bf-f3a0-455f-9627-882409a2b65b)

Unreal Engineで作成されたゲームアプリケーションを `箱庭プラグイン` に接続することで、箱庭シミュレーション環境上で連携動作できるようになります。

本リポジトリの開発範囲は、`Unreal Engine 箱庭プラグイン` です。

その他の箱庭モジュールについては、以下を参照ください。

* [箱庭コア機能](https://github.com/toppers/hakoniwa-core-cpp-client)
* 箱庭コンダクタ
* [箱庭コマンド](https://github.com/toppers/hakoniwa-conductor)

# インストール手順

# シミュレーション手順

# 内部設計情報

# その他

