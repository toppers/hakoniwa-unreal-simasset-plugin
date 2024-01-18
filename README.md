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
2. [箱庭のインストール](https://github.com/toppers/hakoniwa-core-cpp-client/tree/main/examples#サンプルプログラムを実行するための準備)
  * リンク先の手順の `hakoniwa-core-cpp-client` は不要です。
  * 本リポジトリーをクローンすると、直下に  `hakoniwa-core-cpp-client` が配置されていますので、そちらからインストールを進めてください。
3. Unreal Engine箱庭プラグインを利用した開発環境の起動

## Unreal Engine箱庭プラグインを利用した開発環境の起動

### Unreal Engine エディタの起動

まず、下図の`起動` ボタンを押して、起動してください。

<img width="1199" alt="スクリーンショット 2024-01-19 6 40 31" src="https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/93e094c8-3073-470d-927e-bb8698dffecd">

成功すると、プロジェクトブラウザが起動します。

<img width="1191" alt="スクリーンショット 2024-01-19 6 44 13" src="https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/ec7780bd-6565-4231-bfbe-fc3bc61b560a">

画面右下にある `開く` ボタンを押して、クローンしたリポジトリの場所を参照します（下図）。 

<img width="795" alt="スクリーンショット 2024-01-19 6 42 50" src="https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/a5bdaf32-f2a1-42d1-8cac-4e84404c4f60">

`hakoniwa_plugin` を選択して、`hakoniwa_plugin.uproject ` を `Open` してください。

<img width="792" alt="スクリーンショット 2024-01-19 6 46 24" src="https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/77a9e99c-0801-45bc-9163-c6a0dc686dff">

成功すると、Unreal Engineエディタが起動します。

![スクリーンショット 2024-01-19 6 48 06](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/8fa67343-78f4-4b1c-b05c-da1b8de2ec4f)

起動直後は、レベルが選択されていませんので、メニューの `ファイル` -> `レベルを開く` を選択し、下図の `Hakoniwa` をクリックしてください。


![スクリーンショット 2024-01-19 6 48 56](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/8548ba7f-9613-4635-93cd-25133ee1d0da)

成功すると、試作中のレベルが表示されます。

![スクリーンショット 2024-01-19 6 50 50](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/a6cb4436-54a7-46ed-9170-212c0756f690)

エディタの画面右下に、コンパイルボタンがありますので、クリックしてコンパイルします。

![スクリーンショット 2024-01-19 6 51 32](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/2f6e84a3-a88e-473a-af61-99e3d0efd8ac)

成功すると、キキっという音と共に、コンパイル成功メッセージが出力されます。

![スクリーンショット 2024-01-19 6 52 21](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/8ddae2b8-0455-43d9-96b0-f4f98da1aa14)


# シミュレーション手順

シミュレーションを実行するには、最初に箱庭コンダクタを起動しておく必要があります。

Unreal Engine 側のシミュレーションボタンは、下図のようになっていることを確認してください。

![スクリーンショット 2024-01-19 7 08 56](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/50323f61-70f9-472f-87dc-cad493ef0a08)

なっていない場合は、右にあるボタンをクリックして、`シミュレート`を選択すると切り替わります。

![スクリーンショット 2024-01-19 7 09 37](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/7b62cd65-728a-4ed7-a017-4d9aad6a8263)

この状態で、シミュレーション開始ボタンをクリックします。

成功すると、以下のメッセージが出力されます。

```
LogTemp: Loaded HakoAsset
LogTemp: InitializeAsset() Enter
LogTemp: hako_asset_register() success.
LogTemp: InitializeAsset() Exit
PIE: サーバーにログインしました
```

次に、箱庭コマンドで、箱庭としてのシミュレーションを開始します。

```
hako-cmd start
```

成功すると、以下のメッセージが出力されます。

```
PIE: PIE合計開始時間 0.163 秒。
LogTemp: my_on_initialize() success.
LogTemp: Warning: my_on_manual_timing_control() enter
```

また、Unreal Engineエディタは下図のようになり、シミュレーションが始まります。

![スクリーンショット 2024-01-19 7 13 06](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/4d82d1cc-a499-4be6-a740-b641efc94c87)

シミュレーションを停止するには、上手の赤いボタンをクリックし、箱庭コンダクタを停止してください。

なお、Unreal Engineの出力メッセージとしては、以下のものが出力されます。

```
LogTemp: Warning: EndPlay
LogTemp: Warning: FinalizeAsset() Enter
LogTemp: Warning: HakoAssetTask: Stop() start.
LogTemp: Warning: my_on_manual_timing_control() exit
LogTemp: hako_asset_start() success.
LogTemp: Warning: HakoAssetTask: Stop() exit.
LogTemp: HakoAssetModule FinalizeAsset() Exit
```

# 内部設計情報

箱庭プラグインは、以下の３つのクラスで構成されています。

* HakoActorRoot
* HakoAssetModule
* HakoAssetTask

# HakoActorRoot

[HakoActorRoot](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/blob/main/hakoniwa_plugin/Source/hakoniwa_plugin/HakoActorRoot.h) の役割は、Unreal Engineと箱庭を繋げるための入り口になります。

具体的には、Unreal Engineからのシミュレーションイベントを以下の関数で受け取ります。

* BeginPlay()
  * シミュレーション開始イベントを補足して、箱庭のシミュレーションを開始させます。
* TickComponent()
  * シミュレーション実行中の定期イベントを補足して、箱庭のシミュレーションを実行させます。
  * この際、箱庭のシミュレーション時間の同期を行います。
  * シミュレーション時間の同期で、箱庭時間が遅い場合は、シミュレーションの処理は行わないようにします。
  * なお、Unreal Engineでは、Unityのような FixedUpdate()イベント（物理エンジンと連動したコールバック関数）が存在しないため、フレームレートでの駆動としています。
* EndPlay()
  * シミュレーションの停止イベントを補足して、箱庭のシミュレーションを停止させます。

# HakoAssetModule

# HakoAssetTask

![スクリーンショット 2024-01-19 7 28 44](https://github.com/toppers/hakoniwa-unreal-simasset-plugin/assets/164193/c7a050fe-69e4-4234-a74a-b486b969e3c7)


# その他

