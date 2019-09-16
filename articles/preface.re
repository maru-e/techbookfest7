= はじめに
こんにちは。著者は情報系の知識ゼロでIT企業に入社しました。入社してからは情報系の資格をとったりしましたが、机上の勉強だけではいまいちピンと来ていませんでした。また、仕事ではオンプレミスかつ大規模なシステムだったため、何もないところから自分が構築を担当するようなことはなかったですし、知識的にも断片的で理解が浅いと感じていました。

そんな時、自分でクラウドのAWSを利用しながらイチからシステムを構築する機会がありました。オンプレミスとクラウドの違いは後ほど説明しますが、コスト的にも、技術的にも気軽にシステムを構築できるところがクラウドのよいところだと思います。実際に自分でネットワークやサーバーの設定をすることで、「知っている」から「自分で構築できる」と思えるようになりました。

本著では、私のように「なんとなく知っているけど自分でインフラを構築したことはない」という方が、AWSで実際に構築することにより「自分で構築できる」そして知識が「身につく」ことを実感していただけると幸いです。

== 本著は、こんな人に向けて書かれています

 * これからシステムについて勉強しようとしている人
 * AWSを触ってみたい人
 * 自分でインフラ構築したことがない人

== 本著を読み終わると、あなたはこのような状態になっています

 * グローバルIPアドレス、ドメイン、SSH、TLSなどのシステムを作る上で必要な基本的な仕組みについて説明でき、設定できる
 * VPC、サブネット、EC2インスタンス、セキュリティグループ、ロードバランサーなどのAWSサービスを使用できる
 * 次のようなアーキテクチャを自分で作成することができる

//image[000_architecture][作成するシステムアーキテクチャ][scale=0.9]{
//}

 * 次のようなHPを作成することができる

//image[000_Custom_Template][完成したHP][scale=0.7]{
//}

== 免責事項

本書に記載された内容は、情報の提供のみを目的としています。したがって、本書を用いた開発、製作、運用は、必ずご自身の責任と判断によって行ってください。また、技術的な仕組みを説明するにあたってはイメージのしやすさを優先し、説明が不足している部分があるかと思いますが、ご容赦ください。
これらの情報による開発、製作、運用の結果について、著者はいかなる責任も負いません。
なお、本書を用いた環境構築により発生したAWSの利用料金やその他の料金について、著者は負担致しません。
