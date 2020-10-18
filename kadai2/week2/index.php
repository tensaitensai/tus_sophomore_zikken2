<?php
require 'vendor/autoload.php';

// データベース接続
try {
    $pdo = new PDO('sqlite:vending.db');
} catch (PDOException $e) {
    die("データベース接続失敗" . $e->getMessage());
}
// テーブル作成
$pdo->exec("create table if not exists items (
    id    integer primary key autoincrement,
    name  varchar,
    price integer,
    num   integer)");

// SLIM framework の準備
$app = new \Slim\App();

// twig の準備
$loader = new Twig_Loader_Filesystem('templates');
$twig = new Twig_Environment($loader);

//----------------------------------
// ルーティング
//----------------------------------
$app->get('/vending', function ($request, $response, $args) use ($twig, $pdo) {
    $data = [];
    $data['pay'] = 0;

    $stmt = $pdo->prepare("SELECT * FROM items");
    $stmt->execute();
    $data['items'] = $stmt->fetchALL();

    $html = $twig->render('machine.html', $data);
    return $response->write($html);
});

$app->post('/vending', function ($request, $response, $args) use ($twig, $pdo) {
    $data = $request->getParsedBody();

    $stmt = $pdo->prepare("SELECT * FROM items");
    $stmt->execute();
    $data['items'] = $stmt->fetchALL();

    $data['sum'] = 0; //購入する商品の合計金額
    $data['count'] = 0; //エラーの数を数える


    foreach ($data['items'] as $item) { //items内のitemそれぞれに対して実行
        if ($data['buyitem'][$item['id']] > $item['num']) { //在庫が足りない場合
            $data['result'] = 'Error';
            $data['errorlog'][$data['count']] = sprintf("%sの在庫が足りません", $item['name']);
            $data['count']++;
        }
        if ($data['buyitem'][$item['id']] < 0) { //購入する個数が負の値の場合
            $data['result'] = 'Error';
            $data['errorlog'][$data['count']] = sprintf("%sの購入する個数は正の値でお願いします", $item['name']);
            $data['count']++;
        }

        $data['sum'] += $item['price'] * $data['buyitem'][$item['id']];
    }
    if ($data['pay'] < 0) { //投入金額が負の値の場合
        $data['result'] = 'Error';
        $data['errorlog'][$data['count']] = sprintf("投入金額は正の値でお願いします");
        $data['count']++;
    }

    $data['change'] = $data['pay'] - $data['sum']; //お釣りを計算

    if ($data['change'] < 0) { //お金が足りていない場合
        $data['result'] = 'Error';
        $data['errorlog'][$data['count']] = sprintf("投入金額が足りません");
        $data['count']++;
    }

    if ($data['count'] == 0) { //エラーが1つもない場合はsqlのデータベースをupdateする
        $data['result'] = 'Finish';
        foreach ($data['buyitem'] as $key => $num) {
            $sql = "UPDATE items SET num = num - :buy WHERE id = :idkey";
            $stmt = $pdo->prepare($sql);
            $params = array(':buy' => $num, ':idkey' => $key);
            $stmt->execute($params);
        }

        $stmt = $pdo->prepare("SELECT * FROM items");
        $stmt->execute();
        $data['items'] = $stmt->fetchALL();
    }

    $html = $twig->render('machine.html', $data);
    return $response->write($html);
});


$app->get('/insert/{name}/{num}', function ($request, $response, $args) use ($twig, $pdo) {
    $stmt = $pdo->prepare("insert into items (name, price, num) values (?,?,?)");
    $stmt->execute([$args['name'], 0, $args['num']]);

    return $response->write('新商品' . $args['name'] . 'を' . $args['num'] . '個追加しました');
});

$app->run();
