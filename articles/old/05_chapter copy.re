= ロードバランサーを作成しよう

== ロードバランサーの作成

ロードバランサーは、EC2ダッシュボードから操作していきます。
左側のメニューで「ロードバランサー」を選択しましょう。

//image[201_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

「ロードバランサーの作成」をクリックします。

//image[202_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

一番左の「Application Load Balancer」の「作成」をクリックします。

//image[203_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

ロードバランサーの名前には「start-infra-on-aws」と入力します。

//image[204_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

VPCは「start-infra-on-aws」を選択します。
ロードバランサーは、２つ以上のアベイラビリティーゾーン（AZ）の使用を前提としていますので、
public-subnet01とpublic-subnet02の２つを選択します。

「次の手順」をクリックします。

//image[205_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

httpsを使用するように警告が出ますが、今はそのままで構いません。

「次の手順」をクリックします。

//image[206_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

セキュリティグループの設定は、セキュリティグループ名と説明に「alb」と入力します。
許可する通信として、タイプ「http」、プロトコル「TCP」ポート「80」、ソースには、踏み台サーバーのセキュリティグループと同じく、「自分のPCが使用しているグローバルIP/32」を入力しましょう。

//image[207_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

ルーティングの設定は、「新しいターゲットグループ」を選択し、名前に「ap」と入力します。

他はデフォルト設定のまま、「次の手順」をクリックします。

//image[208_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

ターゲットの登録は、インスタンスの一覧からapのインスタンスを選択し、「登録済みに追加」をクリックします。

//image[209_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

登録済みターゲットに、apインスタンスが登録されました。

「次の手順」をクリックします。

//image[210_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

設定内容を確認したら、「作成」をクリックします。

//image[211_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

ロードバランサーが作成できました。

//image[212_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

== apセキュリティグループの設定

ロードバランサーを作成しただけでは、ロードバランサーからapインスタンスに接続できません。
apインスタンス側で、ロードバランサーからのアクセスを許可する必要があります。

そのままEC2ダッシュボードの左のメニューから「セキュリティグループ」を選択し、apのセキュリティグループを選択します。

次に、インバウンドタブを表示し、「編集」をクリックしましょう。

//image[216_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

「ルールの追加」をクリックし、
タイプ「HTTP」、プロトコル「TCP」、ポート「80」、ソースにはalbのセキュリティグループを選択します。

「保存」をクリックします。

//image[217_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

インバウンドに、albのセキュリティグループが追加されました。

これで、ロードバランサーからapインスタンスへのアクセスが可能になりました。

//image[218_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

== ターゲットの状態確認

左のメニューで、「ターゲットグループ」を選択しましょう。

//image[213_EC2_Management_Console][ALBの作成][scale=0.9]{
//}

ターゲットタブを表示し、登録済みターゲットを見てみると、ステータスが「unhealthy」になっていますね。

これは、ロードバランサーがapインスタンスにヘルスチェックをしてもapインスタンス上で何もレスポンスを返すサーバーが動いていないためです。
これからいよいよサーバーを起動していきます。

//image[214_EC2_Management_Console][ALBの作成][scale=0.9]{
//}
