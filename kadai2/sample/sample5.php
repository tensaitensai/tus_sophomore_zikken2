<?php
/////////////////
// sample5.php //
/////////////////
 
require 'vendor/autoload.php';
 
// Slim Application のインスタンス生成．
$app = new \Slim\App();
 
 
$app->get('/', function () {
// ブラウザのアドレスバーに http://localhsot/sample5.php と
// 入力すると，特別な設定をしなければ，通常は GET メソッドで
// HTTP リクエストが送信される．
// したがって，以下がウェブページの初期画面になる．
  echo "
      <!DOCTYPE html>
      <html lang=\"ja\">
        <head>
          <meta charset=\"utf-8\">
          <title>sample</title>
        </head>
        <body>
          <h1>Hello!</h1>
          <form action=\"sample5.php\" method=\"post\">
        Name: <input type=\"text\" name=\"myname\" /><br>
        <input type=\"submit\" value=\"send\" />
          </form>
        </body>
      </html>";
});
 
 
$app->post('/', function ($request, $response, $args) {
// 今回のサンプルでは，post メソッドでユーザが入力した情報を送信する．
// 送信ボタンを押した後は，この関数内で作成したページが表示される．
 
  // HTTP リクエストで送られる情報を連想配列 data に読み込む．
  $data = $request->getParsedBody();
 
  // どんな内容が読み込まれたのか，連想配列 $data の中身を確認する．
  var_dump($data);
 
  // 以下は，ウェブページ本体
  echo "
      <!DOCTYPE html>
      <html lang=\"ja\">
        <head>
          <meta charset=\"utf-8\">
          <title>sample</title>
        </head>
        <body>
          <h1>Hello ";
  echo $data['myname']; // 読み込んだ情報を表示する．
  echo "!</h1>
          <form action=\"sample5.php\" method=\"post\">
            Name: <input type=\"text\" name=\"myname\" /><br>
            <input type=\"submit\" value=\"send\" />
          </form>
        </body>
      </html>";
});
 
 
$app->run();
?>