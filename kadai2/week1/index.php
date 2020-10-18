<?php
require 'vendor/autoload.php';

$app = new \Slim\App();

$loader = new Twig_Loader_Filesystem('templates');
$twig = new Twig_Environment($loader);

$app->get('/tax', function ($request, $response, $args) use ($twig) {
    $data = [];
    $data['price'] = 100;
    $html = $twig->render('tax.html', $data);
    return $response->write($html);
});

//POST "/tax" 税金を計算
$app->post('/tax', function ($request, $response, $args) use ($twig) {
    $data = $request->getParsedBody();
    $data['rate'] = 0.10;

    if ($data['type'] == 'intax') {   //入力されたものが税込金額のとき
        $data['intax'] = $data['price'];
        $data['extax'] = floor($data['intax'] / (1 + $data['rate'])); //お金には小数が無い
        $data['tax'] = $data['intax'] - $data['extax'];
    } elseif ($data['type'] == 'extax') {  //入力されたものが税抜金額のとき
        $data['extax'] = $data['price'];
        $data['intax'] = floor($data['price'] * (1 + $data['rate'])); //お金には小数が無い
        $data['tax'] = $data['intax'] - $data['extax'];
    } else { //エラー
        echo "Error...";
    }

    $data['taxrate'] = $data['rate'] * 100;

    $html = $twig->render('tax.html', $data);
    return $response->write($html);
});

$app->run();
