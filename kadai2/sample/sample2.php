<?php
/////////////////
// sample2.php //
/////////////////
 
require 'vendor/autoload.php';
 
// Slim Application のインスタンス生成．
$app = new \Slim\App();
 
// 以下では，$app->get のルートを / に設定することで
// http;//localhost/sample2.php に GETメソッドでアクセスがきたら，
// 以下の文字列を出力するように設定している．
 
$app->get('/', function () {
  echo "Hello! <br>";
});
 
 
$app->run();
 
?>