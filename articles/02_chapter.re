
= AWSを使い始める

== アカウントを作る

=== アカウント作成に必要なもの

 * メールアドレス
 * クレジットカード

AWSには１年無料のサービスがありますので、基本的にはお金がかかりません。
ただし、無料サービス対象外のサービスも使用しますので、毎月数ドル費用が発生します。
これについては、後ほどご紹介する請求アラートの設定をしておきましょう。

=== アカウントの作成手順
公式サイトに分かりやすく説明されておりますので、こちらの手順にしたがってアカウントを作成します。

@<href>{https://aws.amazon.com/jp/register-flow/}


無料のベーシックプランを選びましょう。また、アカウントのパスワードは忘れないようにメモしておきましょう。

== AWS マネジメントコンソールへのログイン
アカウントが作成できたら、マネジメントコンソールにログインしましょう。

@<href>{https://console.aws.amazon.com/console/home}

//image[005_awsLogin][AWS マネジメントコンソールログイン画面][scale=0.9]{
//}

ログインすると、AWS マネジメントコンソールのホーム画面が表示されます。

右上のアカウント名の右側を見ると、「オハイオ」という文字があります。
クリックしてみましょう。

世界の都市名がずらっと出てきました。

これをリージョンと呼びます。地理的に離れた領域のことで、世界に20箇所（2018年12月現在）あります。
各リージョンにAWSのデータセンターがあり、AWSのサーバーが稼働しています。
どこでも好きなリージョンを選んでAWSのサービスを利用することができますが、日本で使うシステムをオハイオなどの距離的に遠いリージョンで作成すると、サーバーまでの距離が長くなるため遅延（レイテンシ）が発生しますので、基本的には東京リージョンを選択します。

ただし、東京リージョンではまだ使えないサービスを使いたい場合や、
レスポンスが多少遅くても問題ないシステムであれば、コスト節約のために
海外のリージョンを利用することもあります。

今回は「東京リージョン」を利用しましょう。

//image[007_changeRegion][リージョンの変更][scale=0.3]{
//}

今のURL@<fn>{マネジメントコンソールURL}をお気に入りに登録しておくと、次回からは東京リージョンを選択した状態でログインできます。

//footnote[マネジメントコンソールURL][https://ap-northeast-1.console.aws.amazon.com/console/home?region=ap-northeast-1#]

== MFAの設定

=== MFA（多要素認証）とは？
MFA（Multi-Factor Authentication）とは日本語で「多要素認証」のことです。
多要素認証とは、あなたのアカウントに不正ログインされないように次の要素のうち２つ以上を組み合わせて認証することです。

 * 知識情報（あなたが知っているもの）
 ** パスワード、秘密の質問
 * 所持情報（あなたが持っているもの）
 ** ICカード、スマートフォン
 * 生体情報（あなた自身）
 ** 指紋、静脈

今のままでは、ユーザー名とパスワードだけでAWSのコンソールにログインできてしまうため、
多要素認証にはなっておらず、ちょっと心配です。

AWSでは所持情報を使った多要素認証の設定ができます。
多要素認証専用のデバイスを使用することもできますが、スマートフォンのアプリを使うのが一番楽なので、これから設定していきましょう。

=== MFAを設定する

MFAの設定は、「IAM」というサービスで設定します。
AWSマネジメントコンソールにログイン後、「IAM」を検索しましょう。

//image[010_awsHome_MFA][MFAを選択][scale=0.9]{
//}

IAMのダッシュボードで「ルートアカウントの MFA を有効化」をクリックして開き、「MFAの管理」をクリックします。

//image[011_AM_Management_Console][「MFAの管理」をクリック][scale=0.9]{
//}

すると、こんな画面が表示されます。

//image[012_IAM_Management_Console-1][MFA設定時の確認画面][scale=0.9]{
//}

今ログインしているユーザーはルートアカウントだから最強の権限を持っているのだけど、
必要な権限だけもったユーザーを作った方がいいんじゃない？という確認です。

あなたが今ログインに使っているのは一番最初に作成したルートアカウントですが、他にもユーザーを作成することができます。

ルートアカウントは何でもできてしまうので、使うときにも慎重に扱わなければなりません。
このため、AWSではルートアカウントは極力使わず、適切な権限をつけたIAMユーザー@<fn>{IAMユーザー}を作成して使うことを推奨しています。
//footnote[IAMユーザー][ルートアカウント以外をIAMユーザーと言い、ユーザーごとに割り当てる権限を変えることによって、Aさんは新しいサーバーを作ることができるけどBさんにはできない、とユーザーごとにできることを制限することができます。]


今はそのままルートアカウントで操作しますので、「Continue to Security Credentials」をクリックしましょう。

//image[012_IAM_Management_Console-2][「Continue to Security Credentials」をクリック][scale=0.9]{
//}

MFAデバイスは「仮想MFAデバイス」を選択し、「続行」をクリックします。

//image[013_IAM_Management_Console][「仮想MFAデバイス」を選択][scale=0.9]{
//}

仮想デバイスの設定画面が出てきますので、手順に従い、設定していきましょう。

スマートフォンにGoogleの認証アプリ「Google Authenticator」をインストールしてください。

//image[009_Google_Authenticator_on_the_App_Store][Google Authenticator　アプリ][scale=0.5]{
//}

仮想デバイスの設定画面の「QRコードの表示」をクリックします。

//image[014_IAM_Management_Console][「QRコードの表示」をクリック][scale=0.9]{
//}

QRコードが表示されるので、スマートフォンにインストールしたGoogle Authenticatorアプリを起動し、
右上の「＋」ボタンを押して「バーコードをスキャン」を選択します。

すると、カメラが起動するので先ほど表示したQRコードを読み取ります。

//image[015_Google_Authenticator_on_the_App_Store][Google AuthenticatorアプリでQRコードをスキャン][scale=0.5]{
//}

Google Authenticatorアプリに数字が表示されるので、MFAコード１に入力し、番号が変わるのを待ちます。
番号が変わったら、MFAコード２に入力して「MFAの割り当て」をクリックします。

もし入力が終わる前に番号が変わってしまったら、MFAコード1から入力し直しましょう。
連続して表示された数字をMFAコード1とMFAコード2に入力する必要があります。

//image[016_IAM_Management_Console][QRコードを読み取り、MFAコードを入力する][scale=0.9]{
//}

設定が完了しました。

//image[017_IAM_Management_Console][設定が完了][scale=0.9]{
//}

一度、AWSマネジメントコンソールからログアウトして、ログインし直してみましょう。

ログアウトは、一番上のアカウント名をクリックするとメニューが出てくるので
「サインアウト」をクリックします。@<fn>{ログインとサインイン}

//footnote[ログインとサインイン][本著では、分かりやすさのためにログイン・ログアウトを使用していますがAWSではサインイン・サインアウトが使われています。意味はログイン・ログアウトとと同じです。]


//image[018_IAM_Management_Console][ログアウトする][scale=0.3]{
//}

再度ログインしようとするとMFAを求められるので、Google Authenticatorアプリで表示されている数字を入力してログインしましょう。

あなたのスマートフォンを使用した多要素認証の設定が完了しましたね。

== 請求アラートの設定

クラウドでは、サービスを使った分だけ請求されます。
勉強のために色々つくったまま放置していると、いつの間にか何十万円の請求が・・などとならないように、請求アラートを設定しましょう。

ログイン後のアカウント名をクリックし、メニューを表示します。

「マイアカウント請求ダッシュボード」をクリックします。

//image[019_0_Billing_Management_Console][マイ請求ダッシュボードをクリック][scale=0.3]{
//}

請求情報とコスト管理ダッシュボードを表示したら、左の「Billingの設定」をクリックします。

//image[019_1_Billing_Management_Console][Billingの設定をクリック][scale=0.9]{
//}

設定画面で、次のすべてにチェックを入れます。

 * 電子メールで PDF 版請求書を受け取る
 * 無料利用枠の使用のアラートの受信
 　（アカウント登録時のメールアドレス以外のメールアドレスで受け取りたい場合は、メールアドレスを入力）
 * 請求アラートを受け取る

「設定の保存」をクリックして保存したら、「請求アラートを受け取る」の項目説明にある「請求アラートを管理する」リンクをクリックします。

//image[019_2_Billing_Management_Console][「請求アラートを管理する」リンクをクリック][scale=0.9]{
//}

CloudWatchのダッシュボードが表示されましたね。
CloudWatchはAWSのサービスで、システムの状態やログを監視したり、アラームが設定できたりします。

今回は、AWSからの請求金額が想定以上の金額になった時に、メールで通知してくれるようなアラームを作成していきましょう。

左側のメニューで「請求」をクリックします。

//image[019_3_CloudWatch_Management_Console][請求をクリック][scale=0.9]{
//}

「アラームの作成」をクリックします。

//image[019_4_CloudWatch_Management_Console][アラームの作成をクリック][scale=0.9]{
//}

「メトリクスの選択」をクリックします。

//image[019_5_1_CloudWatch_Management_Console][メトリクスの選択をクリック][scale=0.9]{
//}

いくつかのメトリクスが表示されますが、「請求」を選択します。

//image[019_5_2_CloudWatch_Management_Console][請求をクリック][scale=0.9]{
//}

「概算合計請求額」を選択します。

//image[019_5_3_CloudWatch_Management_Console][概算合計請求額をクリック][scale=0.9]{
//}

「USD」を選択して「メトリクスの選択」をクリックします。

//image[019_5_4_CloudWatch_Management_Console][メトリクスの選択をクリック][scale=0.9]{
//}

「メトリクスと条件の指定画面」が表示されます。下の方を見るとしきい値@<fn>{しきい値}の設定ができます。
本著の内容のみAWSを使用するのであれば、2ドルで十分ですので「2」と入力します。
//footnote[しきい値][境目となる値で、限界値のようなものです。]

「次へ」をクリックします。

//image[019_5_CloudWatch_Management_Console][しきい値の設定][scale=0.9]{
//}

アクションの設定では、設定したしきい値（2ドル）よりも請求金額が大きくなった時に、メールで通知するための設定をします。

「新しいトピックの作成」を選択し、トピック名に「aws-alarm」、自分のメールアドレスを入力し、「トピックの作成」をクリックします。
メールは自分が気づきやすいメールアドレスを設定しましょう。

設定したら、「次へ」をクリックします。

//image[019_6_CloudWatch_Management_Console][トピックの作成][scale=0.9]{
//}

説明の追加画面で、アラーム名に「aws-alarm」、説明に「start-infra-on-aws」と入力したら「次へ」をクリックします。

//image[019_8_CloudWatch_Management_Console][アラームの説明追加][scale=0.9]{
//}

プレビューと作成画面で内容を確認したら、「アラームの作成」をクリックします。

//image[019_9_CloudWatch_Management_Console][アラームの作成][scale=0.9]{
//}

アラーム画面で、「一部サブスクリプションが確認待ちの状態です」というバーが出ています。
設定したメールアドレスにメールがちゃんと届くのか確認してね、という意味です。

横にある、「SNSのサブスクリプションを表示」をクリックします。

//image[019_a_CloudWatch_Management_Console][SNSのサブスクリプションを表][scale=0.9]{
//}

保留中の確認となっているサブスクリプションを選択し、「リクエストの確認」をクリックします。

//image[019_b_Simple_Notification_Service][リクエストの確認][scale=0.9]{
//}

設定したメールアドレスにAWSからのメールが届いていますので、確認しましょう。
メール本文の「Confirm subscription」リンクをクリックします。

//image[019_d_Subscription_Confirmation][「Confirm subscription」リンクをクリック][scale=0.9]{
//}

Subscription confirmed!と書かれた画面が表示されましたね。
これで確認は完了です。画面は閉じてしまってOKです。

//image[019_e_confirmation][サブスクリプションの確認][scale=0.9]{
//}

サブスクリプションのステータスが「確認済み」になりました。

//image[019_f_Simple_Notification_Service][サブスクリプションの確認完了][scale=0.9]{
//}

== IAMユーザーの作成

先ほど説明したように、ルートアカウントを使って作業を続けるのはあまりよくありません。
ここで、作業用にIAMユーザーを作成しましょう。

これもAWSのサービス「IAM」で作業します。

IAMのダッシュボードを開き、左のメニューで「ユーザー」を選択し、「ユーザーを追加」をクリックします。

//image[020_IAM_Management_Console][ユーザーを追加」をクリック][scale=0.9]{
//}

ユーザー詳細の設定画面で、ユーザー名を入力し、「AWSマネジメントコンソールへのアクセス」をチェックします。コンソールのパスワードは、「カスタムパスワード」を選択して自分のパスワードを設定しましょう。「パスワードのリセットが必要」のチェックは外します。

「次のステップ」をクリックします。

//image[022_IAM_Management_Console][ユーザーの詳細設定][scale=0.9]{
//}

「既存のポリシーを直接アタッチ」を選択します。@<fn>{権限の管理}

//footnote[権限の管理][アタッチとは「つける」という意味です。もし複数のユーザーでAWSを使用する場合は、グループを作成してユーザーをグループに追加します。そして、グループにポリシーをつけます。こうすることで、グループごとに権限を管理することができ、いちいちユーザー一人ずつのポリシーを管理する必要が無くなります。]

たくさんのポリシーが出てきましたね。行の左にある▶︎を少し広げて見ると、サービスごとに何ができるかの一覧が出てきます。
本来であれば必要最低限のポリシーを１つずつ選択してアタッチしていくのですが、今回は制限のあまりない「AdministratorAccess」を選択しましょう。

「次のステップ」をクリックします。

//image[023_IAM_Management_Console][ポリシーの設定][scale=0.9]{
//}

タグは、自分の好きなキーと値を設定でき、名前や使用目的などを分かりやすくするために使用します。

今回は設定を省略し、そのまま「次のステップ」をクリックします。

//image[024_IAM_Management_Console][タグの設定][scale=0.9]{
//}

作成する内容を確認し、「ユーザーの作成」をクリックします。

//image[025_IAM_Management_Console][確認][scale=0.9]{
//}

ユーザーの作成が完了しました。

//image[027_IAM_Management_Console][IAMユーザー作成完了][scale=0.9]{
//}

それでは、IAMユーザーにもMFAを設定しましょう。

IAMの左のメニューから「ユーザー」を選択し、作成したユーザーのユーザー名をクリックします。

//image[028_IAM_Management_Console][IAMユーザーのMFA設定][scale=0.9]{
//}

概要画面で「認証情報」タブを選択し、「MFAデバイスの割り当て」の右側にある「管理」をクリックします。

//image[029_IAM_Management_Console][IAMユーザーのMFA設定][scale=0.9]{
//}

ルートアカウントに設定した時と同様に@<img>{013_IAM_Management_Console} 画面が表示されたと思うので、
同じ手順で設定しましょう。

== アカウントIDにエイリアスを設定する

IAMユーザーでマネジメントコンソールにログイン後、アカウント名の隣に数字が表示されています。
これは、アカウントIDといって会社や組織のようなものです。このアカウントIDごとに、ユーザーやシステムの管理を行います。

マネジメントコンソールにログインする時にも必要になるのですが、この数字では覚えづらいですよね。
そこで、この数字に分かりやすい別名（エイリアスと言います）をつけることができます。

//image[030_AWSHome][アカウントIDが表示されている][scale=0.9]{
//}

また「IAM」から設定しますので、AWSのサービスからIAMを選択しましょう。

IAMの左のメニューで「ダッシュボード」を選択し、
IAMユーザーのサインインリンクの右側にある「カスタマイズ」をクリックします。

//image[031_IAM_Management_Console][ダッシュボード][scale=0.9]{
//}

アカウントの別名を入力する画面が表示されますので、
自分が分かりやすい名前を入力しましょう。（すでに他の人に使われている名前は使用できません。）

「はい、作成する」をクリックします。

//image[032_IAM_Management_Console][アカウントの別名を入力][scale=0.9]{
//}

IAMユーザーのサインインリンクが設定した別名に変更できました。

//image[033_IAM_Management_Console][変更完了][scale=0.9]{
//}

これで、マネジメントコンソールのログイン画面で
アカウントにエイリアスを入力してログインできるようになります。

//image[034_Amazon_Web_Services_Sign-In][マネジメントコンソールのログイン画面][scale=0.3]{
//}
