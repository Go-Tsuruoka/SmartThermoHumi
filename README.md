# SmartThermoHumi
2022年(大学三年生)の時にArduinoで作ったスマート温湿度計

# 具体的な機能
- 部屋の温湿度の表示
- インテリアフレグランスの残量通知
  - 3段階
  - 一定量下回った場合通知機能がついている
- インテリアフレグランスのにおい強度を示す機能
  - 不快指数をもとに計算
- 温湿度，残量，におい強度はディスプレイに表示される．ボタンを押すことで表示を切り替えることが可能．
  
 # 詳細解説
 ## インテリアフレグランスのにおい強度について
 インテリアフレグランスとは，室内の芳香剤である．スティックが芳香剤となる液体を吸い上げ，気化することにより，室内の
 においがよくなる．インテリアフレグランスのにおい強度は温湿度に影響される．これを客観的に図るため，不快指数を用いた．
$$(不快指数) = 0.81\times(気温)+0.01\times(湿度)\times(0.99\times(湿度)-14.3)+46.3$$

この不快指数は以下のようになっている．
- 65~70が最も快適
- そのゾーンから離れるほど深いとなる．

このため，ゾーンからどれくらい離れているかに応じて5段階の値を設けた．

## 残量確認
残量の確認については，重力センサを用いた．重さに応じて，液体の残量を検知できるようにした．

## LEDの表示について
LEDは以下の3つを表示できる．
- 温湿度
- においの強さ
- 残量

これらは，スイッチを押すことで表示の切り替えを可能とした．
# 全体構造
ボード図，設計配置図，および実際の配置図は以下の通り．
![board](https://user-images.githubusercontent.com/64346532/234898427-90556d47-ef5a-491f-952a-b1d2aaf9766b.jpg)
![sensor_v2](https://user-images.githubusercontent.com/64346532/234898457-2495429c-5e95-4503-9949-a4a59783bdef.jpg)
![IMG_3981](https://user-images.githubusercontent.com/64346532/234898206-2b152e2b-0cba-4d73-a9bf-7cab7fea31b4.jpeg)

概要は以下の通り
- 実際の配置画像の左下がフレグランス



- 右下がディスプレイで，温湿度計を表示する．

## デモ動画

https://user-images.githubusercontent.com/64346532/236739798-5daa2ece-7120-4685-aecf-0bcf429789a1.mp4



