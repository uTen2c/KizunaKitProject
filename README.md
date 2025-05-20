# KizunaKitProject

Developed with Unreal Engine 5

## 導入手順

1. Plugins/KizunaKitを各プロジェクトにコピーする
2. `/KizunaKit/Material/M_VirtualMonitorLayout` を PostProcessVolume の `レンダリング機能 > ポストプロセスマテリアル`
   に追加する

## 画面設定

1. `kizuna.WindowPos <x> <y>` コマンドでウィンドウ位置を調整できます。
    1. 例の筐体の場合は `kizuna.WindowPos -2160 0` でいい感じになります。
2. `kizuna.WindowSize <width> <height>` コマンドでウィンドウサイズを調整できます。
    1. 例の筐体の場合は `kizuna.WindowSize 3240 1920` でいい感じになります。
3. `kizuna.MonitorLayout <monitor 0> <monitor 1> <monitor 2>` コマンドでモニターレイアウトを調整できます。
    1. 例の筐体の場合は `kizuna.MonitorLayout 1 0 2` でいい感じになります。
4. `kizuna.Preset` コマンドで例の筐体にいい感じに合う設定に調整します。

## キャリブレーション

入力装置の値の誤差を補正するためにキャリブレーションを行う必要があります。

1. `kizuna.Calibration 0` コマンドを実行し、5秒間入力装置に触れないでください。
2. `kizuna.Calibration 1` コマンドを実行し、入力装置をたくさん動かしてください。動かしたあともう一度同じコマンドを実行し、キャリブレーションを完了します。
