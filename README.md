# UE4HoloPlay

## [HoloPlay](https://lookingglassfactory.com/software)
- HoloPlayService はインストールしておく (Install HoloPlayService)
- UE4プラグインをダウンロードしておく (Download UE4 plugin)

## プロジェクトの作成 (Create project)
- UE4 新規プロジェクトを作成 (Create new UE4 project)
- プロジェクトフォルダに Plugins フォルダを作り、ダウンロードしたプラグインをコピーする (Create Plugins folder in project folder, and copy downloaded plugin)
- .uproject 右クリックから Visual Studio のソリューションを生成 (Right click .uproject and generate visual studio solution)

## デバイスの準備 (Prepare Device)
- USB-C, HDMI を PC に接続 (Connect USB-C and HDMI to PC)
- スタート - 設定 - システム - ディスプレイ - マルチディスプレイ - 画面表示を拡張する - Looking Glass の画面を選択 - 拡大縮小とレイアウトを 100% にする (Start - Settings - System - Dsiplay - MultiDisplay - Extend these displays - Select Looking Glass Display - Scale and Layout - 100%)

## 再生 (Play)
- HoloPlayCapture アクタをシーンへ追加する (Open project and add HoloPlayCapture actor to the scene)
- PlayInHoloPlayWindow で再生 (Play with PlayInHoloPlayWindow)