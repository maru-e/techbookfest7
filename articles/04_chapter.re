

== Publicサブネットに踏み台サーバーを作成する

//image[160_Management_Console][EC2の作成][scale=0.8]{
//}

//image[161_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[162_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[163_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[164_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[165_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[166_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[167_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[168_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[169_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[170_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[171_cman][EC2の作成][scale=0.8]{
//}

グローバルIPアドレスの確認方法
https://www.cman.jp/network/support/go_access.cgi

//image[172_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[173_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[174_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[175_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[176_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[177_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[178_EC2_Management_Console][EC2の作成][scale=0.8]{
//}


== Protectedサブネットにアプリ用サーバーを作成する

//image[180_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[181_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[182_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[183_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[184_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[185_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[186_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[187_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[188_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[189_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[190_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

//image[191_EC2_Management_Console][EC2の作成][scale=0.8]{
//}

=== SSHでPublic EC2に接続する

踏み台サーバーのパブリックIPを確認しておく。
//image[191_EC2_Management_Console][パブリックIPの確認][scale=0.8]{
//}

== MACの場合

Finderを表示し、上にあるツールバーの「移動」＞「フォルダへ移動」＞「~/.ssh/」を入力。
このフォルダに最初にダウンロードしたキーペアを移動する。（最初に作成したパブリックサブネットのEC2）

ターミナルを開き、次のコマンドを実行する。
.sshフォルダに「config」というファイル名のファイルを作成して開く。

//list[ssh_config][configファイル]{
$ cd ~/.ssh
$ vi config
//}

キーボードで「i」を押して編集モードに切り替え、次のソースをコピペする。
<>の中は先ほど確認した踏み台サーバーのIPアドレスに修正する。

//list[ssh_config][configファイル]{
# start infra on aws

# start infra on aws

  Host bastion
  HostName 52.196.89.55
  User ec2-user
  IdentityFile ~/.ssh/bastion.pem
  Port 22
  ServerAliveInterval 300
  TCPKeepAlive yes
//}

キーボードで「esc」を押して、コマンドモードに切り替える。
その後、次のコマンドでファイルを上書き保存する。

//list[ssh_config][configファイル]{
:wq
//}

次のコマンドで、踏み台サーバーに接続する。

//list[ssh_config][configファイル]{
ssh public01
//}


//list[ssh_config][configファイル]{
The authenticity of host '52.196.89.55 (52.196.89.55)' can't be established.
ECDSA key fingerprint is SHA256:+xXt86U/2APwsGsb7Ff84mbV5aAc6q4JEhKuB5/xZqg.
Are you sure you want to continue connecting (yes/no)?
//}

yesを入力して「Enter」を押す。


怒られた。
キーペアのファイルのパーミッションが緩すぎるとのこと。

//list[ssh_config][configファイル]{
Permissions 0644 for '/Users/maki/.ssh/bastion.pem' are too open.
It is required that your private key files are NOT accessible by others.
This private key will be ignored.
Load key "/Users/maki/.ssh/bastion.pem": bad permissions
ec2-user@52.196.89.55: Permission denied (publickey,gssapi-keyex,gssapi-with-mic).
chmod 600 bastion.pem
//}

パーミッションを600にする。

//list[ssh_config][configファイル]{
$ chmod 600 bastion.pem
//}

パーミッションが600になっていることを確認する。
（読み方説明）

//list[ssh_config][configファイル]{
$ ls -l  bastion.pem
-rw-------@ 1 maki  staff  1692  9  1 18:26 bastion.pem
//}

ログインできた。

//list[ssh_config][configファイル]{
$ ssh public01

       __|  __|_  )
       _|  (     /   Amazon Linux 2 AMI
      ___|\___|___|

https://aws.amazon.com/amazon-linux-2/
4 package(s) needed for security, out of 12 available
Run "sudo yum update" to apply all updates.
//}


== Windowsの場合
#@# 書くつもり

==

== 踏み台サーバーにapサーバーへ接続するための鍵を配置する


=== 踏み台サーバーからapサーバーへの接続

== pythonのapインストール


= ドメインでアクセスできるようにしよう

= HTTPSで接続するようにしよう

== ALBの作成
== 証明書の作成

= 複数人でSSH接続したいとき
== EC2で踏み台サーバーを作成する
