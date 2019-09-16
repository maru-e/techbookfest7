= HPを立ち上げよう

== pythonでHTTPサーバーを起動しよう

ap EC2インスタンスにログインしていますね。
Amazon Linux 2　のマシンイメージを使用している場合、pythonというプログラミング言語が最初から使えるようになっています。

pythonは楽にHTTPサーバーを起動できるコマンドがあるため、今回はpythonを使ってみましょう。

ターミナルで、次のコマンドを打ってpythonが入っていることを確認します。

//listnum[python][pythonが入っていることを確認]{
$ python -V
Python 2.7.14
//}

公開用の「/var/www/html」ディレクトリを作成し（1行目）、

「/var/www/html」ディレクトリに移動します。（2行目）

//listnum[mkdir][公開ディレクトリの作成とディレクトリ移動]{
 $ sudo mkdir -p /var/www/html
 $ cd /var/www/html
//}

では早速ですが、pythonでHTTPサーバーをポート80で立ち上げてみましょう。
サーバーを起動するディレクトリが公開ディレクトリ（ブラウザからアクセスできるディレクトリ）になります。

//listnum[Httpserver][HTTPサーバーをポート80で立ち上げる]{
$ sudo python -m SimpleHTTPServer 80
Serving HTTP on 0.0.0.0 port 80 ...
//}

ターミナルをそのまま放っておくと、次のようなログが30秒間隔くらいで出てきますね。
これは、ロードバランサーからのヘルスチェックにHTTPサーバーが200で応答しているからです。@<fn>{http_status_code}
//footnote[http_status_code][200というのは、HTTPステータスコードでOKという意味です。ステータスコードには100番台から500番台まで多くの種類があり、番号ごとに意味が決まっています。]

また、一番左のIPアドレスがロードバランサーのIPアドレスで、2種類あるのは、ロードバランサーが実は2台あるからです。@<fn>{alb_health_check}
//footnote[alb_health_check][ロードバランサーを作成する時に、アベイラビリティゾーンを2つ選択しましたよね。1つのアベイラビリティーゾーンが地震などで使えなくなっても、もう片方のアベイラビリティゾーンにあるロードバランサーが稼働してくれます。このように、1台使えなくなっても大丈夫なように複数台準備することを「冗長化」と呼びます。]

//listnum[alb_health_check][ヘルスチェックに応答している]{
10.0.0.39 - - [16/Sep/2019 04:42:04] "GET / HTTP/1.1" 200 -
10.0.2.198 - - [16/Sep/2019 04:42:29] "GET / HTTP/1.1" 200 -
//}

ブラウザからAWSマネジメントコンソールを開き、EC2ダッシュボードを表示します。

左のメニューで「ターゲットグループ」を選択し、ターゲットタブを表示します。
ターゲットグループがhealthyになっていることを確認しましょう。

これは、EC2インスタンスの80ポートでHTTPサーバーが起動し、ロードバランサーからのヘルスチェックに200で応答しているからです。

//image[313_EC2_Management_Console][ターゲットグループがhealthyになっている][scale=0.9]{
//}

今度はEC2ダッシュボード左のメニューでロードバランサーを選択します。
作成したロードバランサーを選択し、説明タブのDNS名をコピーしましょう。

//image[314_1_EC2_Management_Console][ロードバランサーのDNS名をコピー][scale=0.9]{
//}

ブラウザを開いて、次のURLにアクセスしてみましょう。

@<href>{http://<ロードバランサーのDNS名>}

//image[314_Directory_listing_for][白い画面が表示された][scale=0.9]{
//}

何も置いてないので、「Directory_listing_for / 」と書かれた白い画面が表示されました。

pythonでサーバーを起動していたターミナルに戻って、
キーボードで「Control」+「c」を押下し、サーバーを停止します。

「/var/www/html」ディレクトリ配下に、「index.html」ファイルを作成しましょう。
次のコマンドを実行します。

//listnum[mk_index.html][index.html ファイルを作成]{
$ sudo vi index.html
//}

キーボードで「i」を押して編集モードに変更し、次のテキストを記入します。

//listnum[vi_index.html][index.html ファイルを編集]{
hello world !
//}

キーボードで「esc」を押下し、コマンドモードに切り替えます。
次のコマンドを実行し、ファイルを上書き保存しましょう。

//listnum[wq_index.html][index.html ファイルを保存]{
:wq
//}

ファイルが保存できたら、次のコマンドを実行してもう一度HTTPサーバを立ち上げましょう。

//listnum[SimpleHTTPServer][HTTPサーバを起動]{
$ sudo python -m SimpleHTTPServer 80
Serving HTTP on 0.0.0.0 port 80 ...
//}

ブラウザを開いて、また先ほどの画面を表示します。
更新されない場合は、ブラウザの更新ボタンを押して画面を更新しましょう。

@<href>{http://<ロードバランサーのDNS名>}

//image[315_hello_world][hello world !が表示された][scale=0.9]{
//}

hello world !が表示できましたね。

次に、HTTPサーバーをバックグラウンドで動かしましょう。
今はターミナルでHTTPサーバーを起動すると、コマンドが入力できない状態で止まってしまい、少し不便です。
そこで、HTTPサーバーを起動している間もターミナルがコマンド実行できる状態にしましょう。

キーボードで「Control」+「c」を押下し、サーバーを停止します。

次のコマンドでHTTPサーバーを起動します。
なお、起動時には5桁の数字（プロセスID）が表示されます。

//listnum[nohup][HTTPサーバーをバックグラウンドで起動]{
$ sudo nohup python -m SimpleHTTPServer 80 &
[1] <プロセスIDが出力される>
nohup: 入力を無視し、出力を `nohup.out' に追記します
//}

Enterを押すと、またコマンドが入力できるようになります。
HTTPサーバーを停止する場合、次のコマンドを実行します。

//listnum[kill][HTTPサーバーを停止]{
$ sudo kill <起動に表示されたプロセスID>
[1]+  終了                  sudo nohup python -m SimpleHTTPServer 80
//}

HTTPサーバーは停止しておきましょう。

== サンプルのテンプレートファイルを使おう

今のままだと、hello world しか表示されないため、少し物寂しいですよね。
そこで、無料で使えるテンプレートを使用して、HPぽくしてみましょう。

次のサイトにアクセスします

@<href>{https://aperitif.io/}

//image[320_The_recipe_for_successful_web_templates][無料で使えるテンプレート作成サイト][scale=0.9]{
//}

好きなようにヘッダーやコンテンツを選び、「Generate」をクリックします。

//image[321_Aperitif_-_Builder][好きなコンテンツを選んで「Generate」をクリック][scale=0.9]{
//}



ダウンロードしたzipファイルを解凍し、中に入っている「template.html」をクリックして表示してみましょう。
いい感じでしたか？

//image[322_file][テンプレートファイルをダウンロード][scale=0.9]{
//}

//image[323_Custom_Template][template.htmlを確認][scale=0.9]{
//}

もし修正したければ、またサイトに戻ってGenerateしなおしてください。

いい感じのテンプレートファイルができたら、ダウンロードしたフォルダごとEC2インスタンスにアップロードします。



新しいターミナルを開きましょう。
次のコマンドで、自分のPCからap EC2インスタンスの「/home/ec2-user/」フォルダにテンプレートフォルダをアップロードします。

「/Users/<ユーザー名>/Downloads/」は、自分がテンプレートをダウンロードしたフォルダの場所に合わせて修正してください。

//listnum[scp_ap][テンプレートフォルダをアップロード]{
$ scp -P 22 -r /Users/<ユーザー名>/Downloads/file ap:/home/ec2-user/
template.html                                 100% 9511   132.6KB/s   00:00
style.min.css                                 100%   19KB 274.6KB/s   00:00
modules.css                                   100%   28KB 596.6KB/s   00:00
index.js                                      100% 9662   313.9KB/s   00:00
//}

アップロードできたら、ap EC2インスタンスにログインします。

//listnum[login_ap][EC2インスタンスにログイン]{
$ ssh ap
Last login: Thu Sep  5 07:47:43 2019 from kd106181068205.au-net.ne.jp

       __|  __|_  )
       _|  (     /   Amazon Linux 2 AMI
      ___|\___|___|

https://aws.amazon.com/amazon-linux-2/
4 package(s) needed for security, out of 12 available
Run "sudo yum update" to apply all updates.
//}


次のコマンドを実行し、テンプレートフォルダがアップロードされているか確認しましょう。

//listnum[ls][テンプレートフォルダがアップロードされているか確認]{
$ ls -l
合計 0
drwx------ 3 ec2-user ec2-user 41  9月  5 09:36 file
//}

アップロードされていましたね。
テンプレートを公開ディレクトリ「/var/www/html/」に移動します。

//listnum[mv][テンプレートを移動]{
$ sudo mv file /var/www/html/
//}

HTTPサーバーが表示する画面を先ほど作成した「hello world!」から、テンプレートに変更しましょう。

まず、公開ディレクトリに移動します。（1行目）

先ほど作成した「hello world!」と記入したindex.htmlを削除します。（2行目）

fileディレクトリに移動します。（3行目）

テンプレートのファイル名をtemplate.htmlからindex.htmlに変更します。（4行目）

fileディレクトリ配下でサーバーを起動します。（5行目）

//listnum[start_Webserver][index.htmlをテンプレートに変更]{
$ cd /var/www/html/
$ sudo rm index.html
$ cd file
$ mv template.html index.html
$ sudo nohup python -m SimpleHTTPServer 80 &
//}


ブラウザで次のURLにアクセスし、ブラウザの画面を更新しましょう。

http://<ロードバランサーのDNS名>

今度はhello world !　ではなく
テンプレートで作成したホームページが表示されましたね。

テンプレート用のhtmlファイルの中身を修正すれば、自分のサイト用に修正することができますが、
今回はインフラ中心で進めるため、サイトの中身のことはスルーします。
