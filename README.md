# KizunaKitProject

Developed with Unreal Engine 5

## 導入手順

1. Plugins/KizunaKitを各プロジェクトにコピーする
2. `/KizunaKit/Material/M_VirtualMonitorLayout` を PostProcessVolume の `レンダリング機能 > ポストプロセスマテリアル` に追加する

## キャリブレーション

入力装置の値の誤差を補正するためにキャリブレーションを行う必要があります。

1. `kizuna.Calibration 0` コマンドを実行し、5秒間入力装置に触れないでください。
2. `kizuna.Calibration 1` コマンドを実行し、入力装置をたくさん動かしてください。動かしたあともう一度同じコマンドを実行し、キャリブレーションを完了します。
