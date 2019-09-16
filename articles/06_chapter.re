= SSHでEC2インスタンスにログインしよう

== SSHとは

SSHとは「Secure Shell」の略で、ネットワークに接続されたサーバーなどの機器をネットワークごしに安全に操作するための手段です。
通信は暗号化され、不正にサーバーにログインすることができないような仕組みになっています。ログイン方法については次の2種類があります。

=== パスワード認証方式

接続先にユーザー名とパスワードを設定して、ログイン時にパスワードで認証する方法です。
パスワードが分かれば誰でもログインできてしまうため、安全性は公開鍵認証方式よりも劣ります。

=== 公開鍵認証方式

AWSのEC2インスタンスはデフォルトでこちらの方式のみ有効になっています。
接続のための詳細なフローの説明は省略しますが、公開鍵認証方式はよく南京錠にたとえられます。

公開鍵と秘密鍵のペアを作成し、秘密鍵を接続元に、公開鍵を接続先に配置します。
こうすることで、秘密鍵を使ってサーバーにログインできるようになります。

//image[299_SSH][公開鍵認証方式][scale=0.6]{
//}

EC2インスタンスを作成した時に、キーペアを作成して「ap.pem」ファイルをダウンロードしましたよね。
実は、ダウンロードした「ap.pem」ファイルが秘密鍵です。
公開鍵は、AWSがインスタンス作成時にインスタンスに配置してくれています。

== SSH接続する

apのEC2インスタンスのパブリックIPを確認しておきましょう。
//image[300_EC2_Management_Console][パブリックIPの確認][scale=0.9]{
//}

お使いのPCがMACなのかWindowsなのかによってSSHの方法が異なります。自分が使用しているPCの手順を確認してください。

=== MACの場合

Finderを表示し、ツールバーの「移動」から「フォルダへ移動」を選択し、「~/.ssh/」を入力します。
このフォルダに、EC2インスタンスを作成した際にダウンロードした「ap.pem」を移動します。

アプリケーションから、ターミナルを開きます。

//image[301_terminal][ターミナル.appを開く][scale=0.9]{
//}

ターミナルでコマンドを実行するには、＄の後ろにコマンドを入力し、Enterを押してコマンドを実行します。

//image[302_terminal][ターミナルでコマンドを実行する][scale=0.9]{
//}

実行するコマンドは「$」から書きますので、実際に実行する時には「$」の後ろから入力してください。
先頭に「$」がついていない場合、それはコマンドの実行結果です。

早速、次のコマンドを実行しましょう。

「/Users/<ユーザー名>/.ssh」フォルダに移動し（1行目）@<fn>{home_dir}
//footnote[home_dir][「~」は「/Users/<ユーザー名>」フォルダのことです。ホームディレクトリとも呼ばれます。]

 viコマンドで「config」というファイル名のファイルを作成して開きます。（2行目）

//listnum[mk_config][configファイルの作成]{
$ cd ~/.ssh
$ vi config
//}


次のテキストをコピーします。<ap EC2インスタンスのパブリックIPアドレス>の中は先ほど確認したap EC2インスタンスのパブリックIPアドレスに修正しましょう。

//list[dscr_vi_config][configファイルの編集]{
3行目：接続先の名前
4行目：接続先のIPアドレス
5行目：ログインユーザー（デフォルトで存在するec2-userを使用します）
6行目：秘密鍵の場所
7行目：接続ポート番号（SSHは22と決まっています）
//}

ターミナルに戻り、貼り付けます。
貼り付けられない場合、キーボードで「i」を押して編集モードに切り替えてから貼り付けましょう。

//listnum[vi_config][configファイルの編集]{
# start infra on aws

  Host ap
  HostName <ap EC2インスタンスのパブリックIPアドレス>
  User ec2-user
  IdentityFile ~/.ssh/ap.pem
  Port 22
//}

//image[303_terminal][ターミナルでコマンドを実行する][scale=0.6]{
//}

貼り付けられたら、キーボードで「esc」を押して、コマンドモードに切り替えます。

次のコマンドでファイルを上書き保存します。

//listnum[wq_config][configファイルの保存]{
:wq
//}

//image[304_terminal][ターミナルでコマンドを実行する][scale=0.6]{
//}

ファイルが閉じたら、次のコマンドでap EC2インスタンスにログインしてみましょう。

//listnum[ssh_ap][EC2インスタンスにログイン]{
$ ssh ap
//}

こんなメッセージが表示されました。
初回のssh接続時には、接続してもよいのか確認されます。

yesを入力して「Enter」を押しましょう。

//listnum[ssh_configure][確認メッセージが表示される]{
The authenticity of host '52.196.89.55 (52.196.89.55)' can't be established.
ECDSA key fingerprint is SHA256:+xXt86U/2APwsGsb7Ff84mbV5aAc6q4JEhKuB5/xZqg.
Are you sure you want to continue connecting (yes/no)? yes
//}

今度は別のメッセージが出ました。

キーペアのファイルのパーミッションがオープンすぎる、というメッセージです。

//listnum[warn_key][警告が表示される]{
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@		 WARNING: UNPROTECTED PRIVATE KEY FILE!		  @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Permissions 0644 for '/Users/xxx/.ssh/ap.pem' are too open.
It is required that your private key files are NOT accessible by others.
This private key will be ignored.
Load key "/Users/xxx/.ssh/ap.pem": bad permissions
ec2-user@52.196.89.55: Permission denied (publickey,gssapi-keyex,gssapi-with-mic).
//}

普段はあまり意識することがないかもしれませんが、ファイルやディレクトリにはパーミッションと呼ばれる、
アクセス権限が設定されいます。

パーミッションは、次の単位でそれぞれの権限を設定します。

 * 自分（ログインしているユーザー）
 * グループメンバ（自分と同じグループの人）
 * 他人（他のグループの人）

権限は、次の3つがあります。

 * 読み取り権限（読んでOK？）
 * 書き込み権限（書いてOK？）
 * 実行権限（動かしてOK？）

また、権限は記号と数字の2パターンで表すことができます。

//table[table1][パーミッション]{
権限	記号	数字
--------------------------------------------
読むことができる（Readable）	r	4
書くことができる（Writable)	w	2
実行することができる（eXecutable）	x	1
なにもできない	-	0
//}

次のコマンドを打ってみましょう。

//listnum[ls_ap_1][ファイルの情報を表示する]{
$ ls -l ap.pem
//}

こんな結果が表示されました。

//listnum[ls_ap_2][ファイルの情報が表示された]{
-rw-r--r--@ 1 hogeuser  staff  1692  9  1 18:26 ap.pem
//}

「-rw-r--r--」の部分がパーミッションです。

左から2文字目から3文字ずつ、自分（rw-）、グループメンバ（r--）、他人（r--）の順番でパーミッションが表されています。

これは自分は読み書き可能、グループメンバーと他人も読み取りは可能というパーミッションです。

数字だと、3文字ずつ数字に直して足し算し、644と表します。

それでは、パーミッションを自分は読み書き可能、グループメンバと他人は何もできないようにパーミッションを変更しましょう。

//listnum[chmod][パーミッションの変更]{
$ chmod 600 ap.pem
//}

パーミッションが、自分（rw-）、グループメンバ（---）、他人（---）になっていることを確認します。

//listnum[ls_ap_3][パーミッションの確認]{
$ ls -l  ap.pem
-rw-------@ 1 hoge  staff  1692  9  1 18:26 ap.pem
//}

パーミッションが変更できましたね。

それでは、もう一度ap EC2インスタンスにログインしましょう。

//listnum[ssh_ap_2][ap EC2インスタンスにログイン]{
$ ssh ap

	   __|  __|_  )
	   _|  (	 /   Amazon Linux 2 AMI
	  ___|\___|___|

https://aws.amazon.com/amazon-linux-2/
4 package(s) needed for security, out of 12 available
Run "sudo yum update" to apply all updates.
//}

無事にログインできましたね。

サーバーからログアウトする場合は次のコマンドです。

//listnum[exit_server][サーバーからログアウトする場合]{
$ exit
//}


=== Windowsの場合

Windows PCの場合は、SSH接続するためにTera Termというアプリをダウンロードします。

次のサイトにアクセスし、「teraterm-x.xxx.exe」をクリックします。
（広告のボタンが目立ちますが、間違ってクリックしないようにしましょう。）

@<href>{https://ja.osdn.net/projects/ttssh2/releases/}


//image[305_0_Tera_Term][teratermのダウンロード][scale=0.6]{
//}

ダウンロードしたexeファイルをダブルクリックします。

//image[305_1_Tera_Term][exeファイルをダブルクリック][scale=0.6]{
//}

インストール言語は「日本語」のままで「OK」をクリックします。

//image[305_2_Tera_Term][「OK」をクリック][scale=0.6]{
//}

「同意する」を選択し、「次へ」をクリックします。

//image[305_3_Tera_Term][「次へ」をクリック][scale=0.6]{
//}

コンポーネントもそのままで「次へ」をクリックします。

//image[305_4_Tera_Term][「次へ」をクリック][scale=0.6]{
//}

ユーザーインターフェースの言語も「日本語」のまま「次へ」をクリックします。

//image[305_5_Tera_Term][「次へ」をクリック][scale=0.6]{
//}

追加タスクもそのままで「次へ」をクリックします。

//image[305_6_Tera_Term][「次へ」をクリック][scale=0.6]{
//}

「インストール」をクリックします。

//image[305_7_Tera_Term][「インストール」をクリック][scale=0.6]{
//}

インストールが完了するのを待ちます。
もし、「LogMeTT」のインストール画面が表示されたらついでにインストールするか、そちらは「Cancel」で閉じても問題ありません。

//image[305_8_Tera_Term][インストール中][scale=0.6]{
//}

セットアップが完了しました。

//image[305_9_Tera_Term][セットアップが完了][scale=0.6]{
//}

デスクトップにTera Termのアイコンができていますので、ダブルクリックしましょう。

//image[305_10_Tera_Term][Tera Termのアイコンをダブルクリック][scale=0.6]{
//}

ホストにap EC2インスタンスのパブリックIPを入力し、TCPポートは「22」サービスは「SSH」を選択し「OK」をクリックしましょう。

//image[305_11_Tera_Term][EC2インスタンスに接続][scale=0.6]{
//}

はじめて接続するサーバーには警告が表示されますので、「続行」をクリックします。

//image[305_12_Tera_Term][「続行」をクリック][scale=0.6]{
//}

ユーザー名に「ec2-user」と入力、鍵を使う方を選択し、秘密鍵にダウンロードした「ap.pem」を選択しましょう。

「OK」をクリックします。

//image[305_13_Tera_Term][「OK」をクリック][scale=0.6]{
//}

無事にログインできましたね。

//image[305_14_Tera_Term][ログインできた][scale=0.6]{
//}

サーバーからログアウトする場合は次のコマンドです。

//listnum[exit][サーバーからログアウトする場合]{
$ exit
//}