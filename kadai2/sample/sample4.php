<?php
/////////////////
// sample4.php //
/////////////////
 
 
require 'vendor/autoload.php';
 
// Slim Application のインスタンス生成．
$app = new \Slim\App();
 
// 以下では，$app->get のルートを / に設定することで
// http;//localhost に GETメソッドでアクセスがきたら，
// 以下の文字列を出力するように設定している．
 
$app->get('/', function () {
     echo "<!DOCTYPE html>
      <html lang=\"ja\">
        <head>
          <meta charset=\"utf-8\">
          <title>sample</title>
        </head>
        <body>
          <h1>Sample html</h1>
          hello world<br>
          <form action=\"index.php\" method=\"post\">
        </body>
      </html>";
});
 
 
$app->run();
?>