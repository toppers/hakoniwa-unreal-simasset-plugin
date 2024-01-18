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

ここでは、Unreal Engine箱庭プラグインを利用するために必要なインストール手順を説明します。

以下の手順でインストールしてください。

1. [UE5のインストール](https://docs.unrealengine.com/5.3/ja/installing-unreal-engine/)
2. 箱庭のインストール
3. 箱庭プラグインのインストール

## 箱庭のインストール

まず、本リポジトリーをクローンします。

```
git clone --recursive https://github.com/toppers/hakoniwa-unreal-simasset-plugin.git
```

ディレクトリ移動：

```
cd hakoniwa-unreal-simasset-plugin/hakoniwa-core-cpp-client 
```

**ビルド:**

```
bash build.bash
```

**インストール:**

```
bash install.bash
```

インストール時に、/usr/local/lib/hakoniwa と /usr/local/bin/hakoniwa へのアクセス許可が必要になることがあります。この許可を与えると、箱庭のライブラリやコマンドがこれらのディレクトリに配置されます。


**環境変数の設定:**

インストールが成功した後、これらのパスを環境変数に設定してください。

Ubuntuの場合:

~/.bashrc ファイルに以下の行を追加してください。

```sh
export LD_LIBRARY_PATH=/usr/local/lib/hakoniwa:$LD_LIBRARY_PATH
export PATH=/usr/local/bin/hakoniwa:$PATH
```

変更を反映させるために、次のコマンドを実行します。

```sh
source ~/.bashrc
```

macOSの場合：

使用しているシェルに応じて ~/.bash_profile または ~/.zshrc に以下の行を追加します。

```sh
export DYLD_LIBRARY_PATH=/usr/local/lib/hakoniwa:$DYLD_LIBRARY_PATH
export PATH=/usr/local/bin/hakoniwa:$PATH
```

変更を反映させるために、次のコマンドを実行します。

```sh
source ~/.bash_profile  # Bashの場合
source ~/.zshrc         # Zshの場合
```

# シミュレーション手順

# 内部設計情報

# その他

