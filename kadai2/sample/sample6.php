<?php
/////////////////
// sample6.php //
/////////////////
 
 
require 'vendor/autoload.php';
 
// Slim Application のインスタンス生成
$app = new \Slim\App();
 
$app->get('/', function ($request,$response,$args){
 
  // twig の準備
  $loader = new Twig_Loader_Filesystem('templates');
  $twig = new Twig_Environment($loader);
 
  // twig に渡す情報を格納するための配列を用意
  $data=[];
 
  $data['title'] = "Twig sample";
  $data['message'] = "Hello world for Twig!";
 
  $html = $twig->render('sample_twig.html', $data);
  return $response->write($html);
});
 
$app->run();
 
?>
