<?php
/////////////////
// sample3.php //
/////////////////
 
 
require 'vendor/autoload.php';
 
$app = new \Slim\App();
 
// ルートパターンを書き換えると，'/' 以外へのアクセスに対する
// 動作も指定することができる．
 
$app->get('/', function () {
  echo "Application Root.";
});
 
$app->get('/example1', function () {
  echo "Example1.";
});
 
$app->get('/next/example2', function () {
  echo "Example2.";
});
 
 
$app->run();
 
?>