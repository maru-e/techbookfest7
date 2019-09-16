= アプリサーバーにログインしよう

== SSHでapサーバーに接続する

apサーバーはインターネットから直接接続できません。
そのため、踏み台サーバーにログインして、踏み台サーバーからapサーバーにログインする必要があります。

また、SSH接続するためには接続元に秘密鍵が必要でしたよね。
まずは、踏み台サーバーにapサーバーの秘密鍵を配置しましょう。

またターミナルから操作します。

1行目：「/Users/<ユーザー名>/.ssh」フォルダに移動します。

2行目：「/Users/<ユーザー名>/.ssh」フォルダにある「ap.pem」ファイルを踏み台サーバーの「/home/ec2-user/.ssh」フォルダにアップロードします。
※<ユーザー名>は自分のPCのものに変更してください。

//list[scp][scp転送]{
$ cd ~/.ssh
$ scp -P 22 /Users/<ユーザー名>/.ssh/ap.pem bastion:/home/ec2-user/.ssh/
ap.pem                                  100% 1692    32.5KB/s   00:00
//}

次に、踏み台サーバーにログインしましょう。

//list[login][踏み台サーバーにログイン]{
$ ssh bastion
Last login: Sun Sep  1 14:08:50 2019 from kd106181066054.au-net.ne.jp

       __|  __|_  )
       _|  (     /   Amazon Linux 2 AMI
      ___|\___|___|

https://aws.amazon.com/amazon-linux-2/
4 package(s) needed for security, out of 12 available
Run "sudo yum update" to apply all updates.
//}

「ap.pem」ファイルが踏み台サーバーの「/home/ec2-user/.ssh」フォルダにアップロードされたことを確認します。

1行目：「/home/ec2-user/.ssh」フォルダに移動します。
2行目：ファイルの一覧を表示します。

//list[ls][ファイルの確認]{
$ cd ./ssh
$ ls -l
合計 8
-rw-r--r-- 1 ec2-user ec2-user 1692  9月  5 05:15 ap.pem
-rw------- 1 ec2-user ec2-user  400  9月  1 09:29 authorized_keys
//}

「ap.pem」ファイルがありましたね。
ちなみに、「authorized_keys」ファイルが踏み台サーバーの公開鍵です。

次に、SSH接続するためのconfigファイルを作成しましょう。

ブラウザでマネジメントコンソールを開き、EC2ダッシュボードからインスタンスを選択し、apサーバーのプライベートIPを確認します。

//image[312_EC2_Management_Console][EC2の作成][scale=0.9]{
//}

ターミナルに戻ってconfigファイルを作成します。

//list[config][configファイルの作成]{
$ vi config
//}

次のテキストをコピーして、ターミナルに貼り付けます。
HostNameにはapサーバーのプライベートIPを入力します。

//list[vi][configファイルの作成]{
# start infra on aws

  Host ap
  HostName <apサーバーのプライベートIP>
  User ec2-user
  IdentityFile ~/.ssh/ap.pem
  Port 22
//}

キーボードの「esc」を押して、コマンドモードに切り替え、
次のコマンドを入力し、「Enter」を押します。

//list[wq][configファイルの保存]{
:wq
//}

秘密鍵ファイルのパーミッションを修正しましょう。

//list[chmod][秘密鍵のパーミッション変更]{
$ chmod 600 ap.pem
//}

また、はじめてssh接続するサーバーのため本当に接続してもよいですか？と聞かれるので
「yes」と入力して「Enter」を押します。

//list[ssh接続][apサーバーへのログイン]{
$ ssh ap
The authenticity of host '10.0.1.96 (10.0.1.96)' can't be established.
ECDSA key fingerprint is SHA256:wisYYzzENGK+muE4X9dbA8ryFTYB0GwtOy2JTVJaDa4.
ECDSA key fingerprint is MD5:0b:9e:0a:b5:99:61:19:b6:5d:78:29:08:cc:14:7b:92.
Are you sure you want to continue connecting (yes/no)? yes
Warning: Permanently added '10.0.1.96' (ECDSA) to the list of known hosts.

       __|  __|_  )
       _|  (     /   Amazon Linux 2 AMI
      ___|\___|___|

https://aws.amazon.com/amazon-linux-2/
16 package(s) needed for security, out of 24 available
Run "sudo yum update" to apply all updates.
//}

ログインできましたね。
